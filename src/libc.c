/* Copyright (c) 2011-2012, Peter A. Bigot
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

/* We assume that the toolchain declaration for setvbuf() is
 * ABI-compatible with ours, but it probably won't be type-compatible,
 * so try to fool the compiler into not performing a compatibility
 * check. */
#define setvbuf NOT_REALLY_SETVBUF
#include <stdio.h>
#undef setvbuf

/* Make sure nobody defined putchar to be a macro.  That's not how we
 * use the thing. */
#undef putchar

#include <embtextf/config.h>
#include <embtextf/stdio.h>
#include <embtextf/stdarg.h>
#include <embtextf/uprintf.h>

#if PROVIDE_LIBC - 0

int setvbuf (void * stream, char * buf, int mode, size_t size)
{
  return EOF;
}

int
printf (const char *fmt, ...)
{
  va_list argp;
  int rc;

  va_start(argp, fmt);
  rc = embtextf_vuprintf(putchar, fmt, argp);
  va_end(argp);
  return rc;
}

int
vprintf (const char *fmt, va_list argp)
{
  return embtextf_vuprintf(putchar, fmt, argp);
}

int
puts (const char *s)
{
  while (*s && (0 <= putchar(*s++))) {
    ;
  }
  if (*s) {
    return EOF;
  }
  return putchar('\n');
}

/* Pointer to the next location into which an output can be stored. */
static char * strPtr_;

/* Pointer to the last location into which an output can be stored.
 * Value will be NULL if there is no user-provided maximum length. */
static char * strEnd_;

static int
strAppend_ (int c)
{
  /* Do not store the character if doing so would use up the last
   * available space in the output.  Return as though the store
   * succeeded, whether or not it did; this ensures the total length
   * that would have been written is returned. */

  if ((NULL == strEnd_) || (strPtr_ < strEnd_)) {
    *strPtr_ = c;
    ++strPtr_;
  }
  return c;
}

int
vsprintf (char *buf, const char *fmt, va_list argp)
{
  int rc;

  strPtr_ = buf;
  strEnd_ = NULL;
  rc = embtextf_vuprintf(strAppend_, fmt, argp);
  *strPtr_ = 0;
  return rc;
}

int
sprintf (char *buf, const char *fmt, ...)
{
  va_list argp;
  int rc;

  va_start(argp, fmt);
  rc = vsprintf(buf, fmt, argp);
  va_end(argp);
  return rc;
}

int
vsnprintf (char *buf, size_t size, const char *fmt, va_list argp)
{
  int rc;

  strPtr_ = buf;
  strEnd_ = strPtr_ + size;
  if (0 < size) {
    --strEnd_;
  }
  rc = embtextf_vuprintf(strAppend_, fmt, argp);
  if (0 < size) {
    *strPtr_ = 0;
  }
  return rc;
}

int
snprintf (char *buf, size_t size, const char *fmt, ...)
{
  va_list argp;
  int rc;

  va_start(argp, fmt);
  rc = vsnprintf(buf, size, fmt, argp);
  va_end(argp);
  return rc;
}

#endif /* PROVIDE_LIBC */
