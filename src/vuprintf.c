/* Copyright (c) 2006-2011
 *     Chris Liechti <cliechti@gmx.net>
 *     Peter A. Bigot <pabigot@users.sourceforge.net>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 * - Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 *
 * Implement a reentrant vuprintf. This function is called by all the different
 * (v)(u)(s)printf functions from the mspgcc libc.
 *
 */
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <embtextf/vuprintf.h>

/**
 * Internal state tracking.
 * Saves memory and parameters when compacted in a bit field.
 */
typedef struct {
#if EMBTEXTF_VUPRINTF_ENABLE_LONG - 0
  unsigned int is_long:1;            /**< emit as long */
#endif /* EMBTEXTF_VUPRINTF_ENABLE_LONG */
#if EMBTEXTF_VUPRINTF_ENABLE_LONGLONG - 0
  unsigned int is_longlong:1;        /**< emit as long long */
#endif /* EMBTEXTF_VUPRINTF_ENABLE_LONGLONG */
  unsigned int is_signed:1;          /**< process a signed number */
  unsigned int is_alternate_form:1;  /**< alternate output */
  unsigned int left_align:1;         /**< if != 0 pad on right side, else on left side */
  unsigned int emit_octal_prefix:1;  /**< emit a prefix 0 */
  unsigned int emit_hex_prefix:1;    /**< emit a prefix 0x */
  unsigned int fill_zero:1;          /**< pad left with zero instead of space */
  unsigned int uppercase:1;          /**< print hex digits in upper case */
  unsigned int zero_pad_precision:1; /**< add precision zeros before text */
  unsigned int truncate_precision:1; /**< limit text to precision characters */
  char sign_char;                    /**< character to emit as sign (NUL no emit) */
  uint8_t precision;                 /**< value related to format precision specifier */
} flags_t;

/** Maximum number of characters in any (numeric) prefix.  That would
 * be "0x". */
#define MAX_PREFIX_CHARS 2

/** Size of the largest integer type, in octets.  We know short <= int
 * <= long <= long long. */
#if EMBTEXTF_VUPRINTF_ENABLE_LONGLONG - 0
#define SIZEOF_LARGEINT sizeof(long long int)
#elif EMBTEXTF_VUPRINTF_ENABLE_LONG - 0
#define SIZEOF_LARGEINT sizeof(long int)
#else /* EMBTEXTF_VUPRINTF_ENABLE_LONG */
#define SIZEOF_LARGEINT sizeof(int)
#endif /* EMBTEXTF_VUPRINTF_ENABLE_* */

/** If intptr_t is enabled, its size.  We have no idea where it lies
 * relative to other integral types. */
#if EMBTEXTF_VUPRINTF_ENABLE_INTPTR - 0
#define SIZEOF_INTPTR sizeof(intptr_t)
#else /* EMBTEXTF_VUPRINTF_ENABLE_INTPTR */
#define SIZEOF_INTPTR 0
#endif /* EMBTEXTF_VUPRINTF_ENABLE_INTPTR */

/** Maximum number of characters for formatted numbers, including sign
 * and EOS but excluding prefix.  The longest representation will be
 * in octal, so assume one char for every three bits in the
 * representation. */
#define MAX_FORMAT_LENGTH ((((CHAR_BIT * ((SIZEOF_LARGEINT > SIZEOF_INTPTR) ? SIZEOF_LARGEINT : SIZEOF_INTPTR)) + 2) / 3) + 1 + 1)

/**
 * Helper function to generate anything that precedes leading zeros.
 *
 * @param prefix_buffer [in] pointer to where characters should be written
 * @param flags         [in] flags that specify how the field is aligned
 * @return the number of characters that were written
 */
static int
build_numeric_prefix (char *prefix_buffer, flags_t flags)
{
  char *p = prefix_buffer;
  if (flags.emit_hex_prefix) {
    *p++ = '0';
    *p++ = (flags.uppercase ? 'X' : 'x');
  } else if (flags.emit_octal_prefix) {
    *p++ = '0';
  } else if (flags.sign_char) {
    *p++ = flags.sign_char;
  }
  return p - prefix_buffer;
}

/**
 * Helper function to print strings and fill to the defined width, with the
 * given fill character.
 *
 * @param emit_char    [in] function used to write characters
 * @param char_p        [in] the string that is written
 * @param width         [in] field width. 0 is without limitation of width.
 * @param flags         [in] flags that specify how the field is aligned
 * @return the number of characters that were written
 */
static int
print_field (vuprintf_emitchar_fn write_char, const char *char_p, unsigned int width,
             flags_t flags)
{
  int character_count = 0;
  char prefix_buffer[MAX_PREFIX_CHARS];
  int prefix_idx = 0;
  unsigned int truncate_precision;
  int prefix_len = build_numeric_prefix(prefix_buffer, flags);

  /* Set the number of characters of precision we should output.  If
   * truncation by precision is not specified, use -1 as an
   * approximation of "infinity". */
  truncate_precision = flags.precision;
  if (!flags.truncate_precision) {
    truncate_precision = (unsigned int)-1;
  }

  /*  if right aligned, pad */
  if (!flags.left_align) {
    char leading_fill = ' ';
    unsigned int len = strlen(char_p);

    /*  Account for the prefix we'll write */
    if (prefix_len <= width) {
      width -= prefix_len;
    } else {
      width = 0;
    }

    /*  Account for leading zeros required by a numeric precision specifier */
    if (flags.zero_pad_precision) {
      if (flags.precision <= width) {
        width -= flags.precision;
      } else {
        width = 0;
      }
    }

    /*  Account for short writes of strings due to precision specifier */
    if (truncate_precision < len) {
      len = truncate_precision;
    }

    /*  emit numeric prefix prior to padded zeros */
    if (flags.fill_zero) {
      leading_fill = '0';
      character_count += prefix_len;
      while (prefix_idx < prefix_len) {
        write_char(prefix_buffer[prefix_idx++]);
      }
    }

    while (len < width) {
      write_char(leading_fill);
      character_count++;
      len++;
    }
  }

  /*  emit any unemitted prefix */
  while (prefix_idx < prefix_len) {
    character_count++;
    write_char(prefix_buffer[prefix_idx++]);
  }

  /*  emit zeros to meet precision requirements */
  if (flags.zero_pad_precision) {
    while (flags.precision--) {
      write_char('0');
      character_count++;
    }
  }

  /*  output the buffer contents up to the maximum length */
  while (*char_p && truncate_precision--) {
    write_char(*char_p);
    char_p++;
    character_count++;
  }
  /*  if left aligned, pad */
  while (character_count < width) {
    write_char(' ');
    character_count++;
  }
  /*  return how many characters have been output */
  return character_count;
}


/**
 * Reentrant formatted print.
 *
 * Supported '%' format characters:
 * - 's'  const char *  null terminated string as text or "(null)"
 * - 'x'  int/long      hexadecimal '0xnn'
 * - 'X'  int/long      hexadecimal '0XNN'
 * - 'u'  int/long      unsigned decimal
 * - 'd'  int/long      signed decimal
 * - 'i'  int/long      signed decimal
 * - 'p'  pointer       pointer value is printed as "0xnnnn"
 * - 'c'  char          single character
 * - 'o'  int/long      octal numbers
 *
 * Supported flags:
 * - '#'  use alternate form.
 * - 'l'  use long instead of int for numbers (IF CONFIGURED)
 * - 'll' use long long for numbers (IF CONFIGURED)
 * - '-'  align left
 * - ' '  prefix non-negative numbers with single space
 * - '+'  prefix non-negative numbers with plus
 * - '0'  pad with '0' instead of ' '
 * - '*'  fetch width from the argument list (unsigned int)
 *
 * The field width (e.g. "%10s") can also be specified.
 *
 * Unsupported are:
 * - Precision (e.g. "%.2s")
 * - float numbers (format char: e E f F g G a A)
 * - write-back character count ("%n")
 *
 * @param write_char    [in] function used to write characters
 * @param format        [in] format string
 * @param args          [in] variable argument list
 * @return the number of characters that were written
 */
int
vuprintf (vuprintf_emitchar_fn write_char, const char *format, va_list args)
{
  int character_count = 0;
  enum
  { DIRECT, FORMATING } mode = DIRECT;
  unsigned int wp_value = 0;
  unsigned int width = 0;
  flags_t flags;
  const char* specifier = format;
  char *char_p;
  char character;
  int radix;
  char have_wp_value = 0;
  char have_precision = 0;
  char is_zero = 0;
  char is_negative = 0;
  union {
    int i;
#if EMBTEXTF_VUPRINTF_ENABLE_INTPTR - 0
    intptr_t ptr;
#endif /* EMBTEXTF_VUPRINTF_ENABLE_INTPTR */
#if EMBTEXTF_VUPRINTF_ENABLE_LONG - 0
    long int li;
#endif /* EMBTEXTF_VUPRINTF_ENABLE_LONG */
#if EMBTEXTF_VUPRINTF_ENABLE_LONGLONG - 0
    long long int lli;
#endif /* EMBTEXTF_VUPRINTF_ENABLE_LONGLONG */
  } number;
  char buffer[MAX_FORMAT_LENGTH];       /*  used to print numbers */

  while ((character = *format++)) {
    /*  test and save character */
    if (mode == DIRECT) {
      /*  output characters from the format string directly, except the */
      /*  '%' sign which changes the mode */
      if (character == '%') {
        width = wp_value = 0;
        memset(&flags, 0, sizeof(flags));
        have_wp_value = have_precision = is_zero = is_negative = 0;
        specifier = format - 1;
        mode = FORMATING;
      } else {
write_character:
        write_char(character);
        character_count++;
        mode = DIRECT;
      }
    } else {
      /* FORMATING */
      /*  process format characters */
      switch (character) {
          /*  output '%' itself */
        case '%':
          goto write_character; /*  character is already the % */

          /*  alternate form flag */
        case '#':
          flags.is_alternate_form = 1;
          break;

          /*  interpret next number as long integer */
        case 'l':
#if EMBTEXTF_VUPRINTF_ENABLE_LONGLONG - 0
          if (flags.is_long) {
            flags.is_long = 0;
            flags.is_longlong = 1;
          } else {
#endif /* EMBTEXTF_VUPRINTF_ENABLE_LONGLONG */
#if EMBTEXTF_VUPRINTF_ENABLE_LONG - 0
            if (flags.is_long) {
              goto bad_format;
            }
            flags.is_long = 1;
#else /* EMBTEXTF_VUPRINTF_ENABLE_LONG */
            goto bad_format;
#endif /* EMBTEXTF_VUPRINTF_ENABLE_LONG */
#if EMBTEXTF_VUPRINTF_ENABLE_LONGLONG - 0
          }
#endif /* EMBTEXTF_VUPRINTF_ENABLE_LONGLONG */
          break;

          /*  left align instead of right align */
        case '-':
          flags.left_align = 1;
          break;

          /*  emit a + before a positive number */
        case '+':
          flags.sign_char = '+';
          break;

          /*  emit a space before a positive number */
        case ' ':
          /*  + overrides space as a flag character */
          if ('+' != flags.sign_char) {
            flags.sign_char = ' ';
          }
          break;

        case '.':
          /*  explicit precision is present */
          if (have_wp_value) {
            width = wp_value;
            wp_value = 0;
            have_wp_value = 0;
          }
          have_precision = 1;
          break;
          /*  fetch length from argument list instead of the format */
          /*  string itself */
        case '*': {
          int val = va_arg(args, int);

          if (val >= 0) {
            wp_value = val;
          } else if (have_precision) {
            wp_value = 0;
          } else {
            flags.left_align = 1;
            wp_value = -val;
          }
          have_wp_value = 1;
          break;
        }

        /*  format field width. zero needs special treatment */
        /*  as when it occurs as first number it is the */
        /*  flag to pad with zeroes instead of spaces */
        case '0':
          /*  a leading zero means filling with zeros */
          /*  it must be a leading zero if 'width' is zero */
          /*  otherwise it is in a number as in "10" */
          if (wp_value == 0 && !have_precision) {
            flags.fill_zero = !flags.left_align;
            break;
          }
          /*@fallthrough@ */
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
          wp_value *= 10;
          wp_value += character - '0';
          have_wp_value = 1;
          break;

          /*  placeholder for one character */
        case 'c':
          character = va_arg(args, int);
          if (! have_precision && ! have_wp_value) {
            goto write_character;
          }
          char_p = buffer;
          buffer[0] = character;
          buffer[1] = 0;
          goto emit_string;

          /*  placeholder for arbitrary length null terminated */
          /*  string */
        case 's':
          char_p = va_arg(args, char *);
emit_string:
          /* Note: Zero-padding on strings is undefined; it
           * is legitimate to zero-pad */
          if (have_precision) {
            flags.truncate_precision = 1;
            flags.precision = wp_value;
          } else if (have_wp_value) {
            width = wp_value;
          }
          character_count += print_field(write_char,
                                         (char_p != NULL) ? char_p : "(null)",
                                         width, flags);
          mode = DIRECT;
          break;

#if EMBTEXTF_VUPRINTF_ENABLE_INTPTR - 0
          /*  placeholder for an address */
          /*  addresses are automatically in alternate form and */
          /*  hexadecimal. */
        case 'p':
          number.ptr = (intptr_t) va_arg(args, void *);
          number.ptr &= UINTPTR_MAX;
          radix = 16;
          flags.is_alternate_form = (0 != number.ptr);
          goto emit_number;
#endif /* EMBTEXTF_VUPRINTF_ENABLE_INTPTR */

          /*  placeholder for hexadecimal output */
        case 'X':
          flags.uppercase = 1;
          /*@fallthrough@ */
        case 'x':
          radix = 16;
          goto fetch_number;

          /*  placeholder for octal output */
        case 'o':
          radix = 8;
          goto fetch_number;

          /*  placeholder for signed numbers */
        case 'd':
        case 'i':
          flags.is_signed = 1;
          /*@fallthrough@ */
          /*  placeholder for unsigned numbers */
        case 'u':
          radix = 10;
          /*  label for number outputs including argument fetching */
fetch_number:
#if EMBTEXTF_VUPRINTF_ENABLE_LONGLONG - 0
          if (flags.is_longlong) {
            number.lli = va_arg(args, long long int);
            is_zero = (number.lli == 0);
            is_negative = (number.lli < 0);
          } else
#endif /* EMBTEXTF_VUPRINTF_ENABLE_LONGLONG */
#if EMBTEXTF_VUPRINTF_ENABLE_LONG - 0
            if (flags.is_long) {
              number.li = va_arg(args, long int);
              is_zero = (number.li == 0);
              is_negative = (number.li < 0);
            } else
#endif /* EMBTEXTF_VUPRINTF_ENABLE_LONG */
            {
              number.i = va_arg(args, int);
              is_zero = (number.i == 0);
              is_negative = (number.i < 0);
            }
          /*  label for number outputs excluding argument fetching */
          /*  'number' already contains the value */
          goto emit_number;
emit_number:
          /*  only non-zero numbers get hex/octal alternate form */
          if (flags.is_alternate_form && !is_zero) {
            if (radix == 16) {
              flags.emit_hex_prefix = 1;
            } else if (radix == 8) {
              flags.emit_octal_prefix = 1;
            }
          }
          if (flags.is_signed && is_negative) {
            /*  save sign for radix 10 conversion */
            flags.sign_char = '-';
#if EMBTEXTF_VUPRINTF_ENABLE_LONGLONG - 0
            if (flags.is_longlong) {
              number.lli = -number.lli;
            } else
#endif /* EMBTEXTF_VUPRINTF_ENABLE_LONGLONG */
#if EMBTEXTF_VUPRINTF_ENABLE_LONG - 0
              if (flags.is_long) {
                number.li = -number.li;
              } else
#endif /* EMBTEXTF_VUPRINTF_ENABLE_LONG */
                number.i = -number.i;
          }

          /*  go to the end of the buffer and null terminate */
          char_p = &buffer[sizeof(buffer) - 1];
          *char_p-- = '\0';

          /*  divide and save digits, fill from the lowest */
          /*  significant digit */
#define CONVERT_LOOP(_unsigned, _number)                                \
          do                                                            \
            {                                                           \
              int digit = (_unsigned) _number % radix;                  \
              if (digit < 10)                                           \
                *char_p-- = digit + '0';                                \
              else                                                      \
                *char_p-- = digit + (flags.uppercase ? ('A' - 10) : ('a' - 10)); \
              _number = ((_unsigned) _number) / radix;                  \
            }                                                           \
          while ((_unsigned) _number > 0)

#if EMBTEXTF_VUPRINTF_ENABLE_LONGLONG - 0
          if (flags.is_longlong) {
            CONVERT_LOOP(unsigned long long int, number.lli);
          } else
#endif /* EMBTEXTF_VUPRINTF_ENABLE_LONGLONG */
#if EMBTEXTF_VUPRINTF_ENABLE_LONG - 0
            if (flags.is_long) {
              CONVERT_LOOP(unsigned long int, number.li);
            } else
#endif /* EMBTEXTF_VUPRINTF_ENABLE_LONG */
              CONVERT_LOOP(unsigned int, number.i);

#undef CONVERT_LOOP

          /*  only decimal numbers get signs */
          if (radix != 10) {
            flags.sign_char = 0;
          }

          /*  write padded result */
          if (have_precision) {
            int number_width = buffer + sizeof(buffer) - char_p - 2;
            if (number_width < wp_value) {
              flags.zero_pad_precision = 1;
              flags.precision = wp_value - number_width;
            }
          } else if (have_wp_value) {
            width = wp_value;
          }
          character_count += print_field(write_char, 1 + char_p, width, flags);
          mode = DIRECT;
          break;

        default:
bad_format:
          while (specifier < format) {
            write_char(*specifier++);
            ++character_count;
          }
          mode = DIRECT;
          break;
      }
    }
  }
  return character_count;
}
