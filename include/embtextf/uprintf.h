/* Copyright (c) 2012, Peter A. Bigot
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

#ifndef EMBTEXTF_VUPRINTF_H
#define EMBTEXTF_VUPRINTF_H

#include <stdarg.h>

/** Type of function required by (v)uprintf.h for emitting characters.
 * putchar(3) is the template. */
typedef int (* vuprintf_putchar_fn) (int);

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

int
#if __GNUC__
__attribute__((format (printf, 2, 3))) 
#endif /* __GNUC__ */
uprintf (vuprintf_putchar_fn emit_char, const char *fmt, ...);

int vuprintf (vuprintf_putchar_fn write_char, const char *format, va_list args);

#endif /* EMBTEXTF_VUPRINTF_H */
