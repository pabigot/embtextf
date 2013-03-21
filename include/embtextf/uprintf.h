/* Copyright (c) 2012-2013, Peter A. Bigot
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of the software nor the names of its contributors may be
 *   used to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/** @file
 * @brief Declarations for core functions supporting @c printf(3c) and related capabilities
 *
 * This header declares configuration options and supporting material
 * for a @c printf(3c) variant that emits formatted data through a
 * per-character callback, such as @c putchar(3).  It can be used as
 * the basis for routines that produce formatted output on LCDs, into
 * character buffers, or over other communications links that can
 * provide character-oriented interface.
 *
 * @section uprintf_format vuprintf formatting capabilities
 *
 * The formatting capabilities of embtextf_vuprintf() are intended to
 * be compatible with the standard C library format string
 * interpretation, with only a few restrictions, including:
 *
 * @li Floating point values are not supported.
 * @li Wide characters are not supported.
 *
 * Within those limitations, all standard format flags are supported:
 *
 * Flag character  | Conditional on                             | Comments
 * :-------------- | :--------------                            | :-------------
 * @c #            | #EMBTEXTF_VUPRINTF_ENABLE_ALTERNATE_FORM   | Emit prefix for octal and hex values
 * @c 0            |                                            | Zero pad output
 * @c -            |                                            | Left justify
 * (space)         |                                            | Leave blank before positive number
 * @c +            |                                            | Always emit sign before converted value
 *
 * Field width and (optionally) precision are supported for integer and string conversions:
 *
 * Example         | Conditional on                             | Comments
 * :-------------- | :--------------                            | :-------------
 * @c %4d          |                                            | width, pad output to 4 characters
 * @c %*d          |                                            | width, pad output to width passed as argument
 * @c %.3d         | #EMBTEXTF_VUPRINTF_ENABLE_PRECISION        | precision, minimum 3 number of digits in conversion
 * @c %.*d         | #EMBTEXTF_VUPRINTF_ENABLE_PRECISION        | precision, minimum number of digits in conversion passed as argument
 *
 * Some length modifiers are supported for integer conversion:
 *
 * Example         | Conditional on                             | Comments
 * :-------------- | :--------------                            | :-------------
 * @c %%d          |                                            | expect input type @c int
 * @c %%ld         | #EMBTEXTF_VUPRINTF_ENABLE_LONG             | expect input type @c long
 * @c %%lld        | #EMBTEXTF_VUPRINTF_ENABLE_LONGLONG         | expect input type @c long @c long
 *
 * Many conversion specifiers, excluding floating point, are supported:
 *
 * Example         | Conditional on                             | Comments
 * :-------------- | :--------------                            | :-------------
 * @c d @c i       |                                            | Signed decimal
 * @c o            | #EMBTEXTF_VUPRINTF_ENABLE_OCTAL            | Octal
 * @c u            |                                            | Unsigned decimal
 * @c x @c X       |                                            | Hexadecimal (lower or upper case alphabetics)
 * @c s            |                                            | Null-terminated text input
 * @c c            |                                            | Character value of @c int
 * @c p            | #EMBTEXTF_VUPRINTF_ENABLE_INTPTR           | Pointer output
 *
 * When format specifiers are not recognized by the infrastructure the
 * unrecognized characters are emitted as output.
 *
 * @homepage http://github.com/pabigot/embtextf
 * @copyright Copyright 2013, Peter A. Bigot.  Licensed under <a href="http://www.opensource.org/licenses/BSD-3-Clause">BSD-3-Clause</a>
 * @note embtextf_vuprintf() contains material copyright 2006-2011, Chris Liechti.
 */

#ifndef EMBTEXTF_VUPRINTF_H
#define EMBTEXTF_VUPRINTF_H

#include <stdarg.h>

/** Type of function required by embtextf_vuprintf() for emitting characters.
 * @c putchar(3) is the template. */
typedef int (* embtextf_putchar_fn) (int);

#ifndef EMBTEXTF_VUPRINTF_ENABLE_DEFAULT
/** Set to a preprocessor true value when the default for vuprintf
 * features is to enable them.  Set to a preprocessor false value when
 * the default for vuprintf features is to disable them. */
#define EMBTEXTF_VUPRINTF_ENABLE_DEFAULT 1
#endif /* EMBTEXTF_VUPRINTF_ENABLE_DEFAULT */

#ifndef EMBTEXTF_VUPRINTF_ENABLE_INTPTR
/** Set to a preprocessor true value to allow the @c %p conversion
 * specification to support printing pointer values.  If false, the
 * conversion specification will be passed through as text. */
#define EMBTEXTF_VUPRINTF_ENABLE_INTPTR EMBTEXTF_VUPRINTF_ENABLE_DEFAULT
#endif /* EMBTEXTF_VUPRINTF_ENABLE_INTPTR */

#ifndef EMBTEXTF_VUPRINTF_ENABLE_LONG
/** Set to a preprocessor true value to allow the @c l length modifier
 * to be recognized supporting long integer parameters.  If false, the
 * @c l length modifier will be unrecognized and its containing
 * conversion specification passed through as text. */
#define EMBTEXTF_VUPRINTF_ENABLE_LONG EMBTEXTF_VUPRINTF_ENABLE_DEFAULT
#endif /* EMBTEXTF_VUPRINTF_ENABLE_LONG */

#ifndef EMBTEXTF_VUPRINTF_ENABLE_LONGLONG
/** Set to a preprocessor true value to allow two @c l length
 * modifiers to be recognized for a <c>long long</c> integer
 * parameter.  If false, the second @c l length modifier will be
 * unrecognized and its containing conversion specification passed
 * through as text.
 *
 * @note Use of this option requires use of
 * #EMBTEXTF_VUPRINTF_ENABLE_LONG. */
#define EMBTEXTF_VUPRINTF_ENABLE_LONGLONG EMBTEXTF_VUPRINTF_ENABLE_DEFAULT
#endif /* EMBTEXTF_VUPRINTF_ENABLE_LONGLONG */

#ifndef EMBTEXTF_VUPRINTF_ENABLE_PRECISION
/** Set to a preprocessor true value to allow precision to be
 * recognized in conversion specifications.  If false, a precision
 * specification will be unrecognized and its containing conversion
 * specification passed through as text. */
#define EMBTEXTF_VUPRINTF_ENABLE_PRECISION EMBTEXTF_VUPRINTF_ENABLE_DEFAULT
#endif /* EMBTEXTF_VUPRINTF_ENABLE_PRECISION */

#ifndef EMBTEXTF_VUPRINTF_ENABLE_OCTAL
/** Set to a preprocessor true value to allow the @c %o conversion
 * specifier to be recognized.  If false, an octal conversion
 * specifier will be unrecognized and passed through as text. */
#define EMBTEXTF_VUPRINTF_ENABLE_OCTAL EMBTEXTF_VUPRINTF_ENABLE_DEFAULT
#endif /* EMBTEXTF_VUPRINTF_ENABLE_OCTAL */

#ifndef EMBTEXTF_VUPRINTF_ENABLE_ALTERNATE_FORM
/** Set to a preprocessor true value to allow the @c # alternate form
 * flag to be recognized for @c x and @c o conversions.  If false, the
 * alternate form flag will be unrecognized and its containing
 * conversion specification passed through as text. */
#define EMBTEXTF_VUPRINTF_ENABLE_ALTERNATE_FORM EMBTEXTF_VUPRINTF_ENABLE_DEFAULT
#endif /* EMBTEXTF_VUPRINTF_ENABLE_ALTERNATE_FORM */

/** Format text collected by a variadic function.
 *
 * @param emit_char the function used to emit formatted characters.
 * The interface supports using @c putchar for this.
 *
 * @param fmt a standard C format string
 *
 * @param args aggregated arguments as collected using the @c stdarg.h
 * macros.
 *
 * @return the number of characters passed to the @a emit_char
 * function while generating the formatted string.
 *
 * @see @ref uprintf_format
 */
int embtextf_vuprintf (embtextf_putchar_fn write_char, const char *format, va_list args);

/** Variadic print-via-callback function
 *
 * This uses the standard va_arg facility to extract arguments and
 * delegate the formatting to embtextf_vuprintf().
 *
 * @param emit_char as with embtextf_vuprintf()
 *
 * @param fmt as with embtextf_vuprintf()
 *
 * @return as with embtextf_vuprintf */
int
#if __GNUC__
__attribute__((format (printf, 2, 3)))
#endif /* __GNUC__ */
embtextf_uprintf (embtextf_putchar_fn emit_char, const char *fmt, ...);

#endif /* EMBTEXTF_VUPRINTF_H */
