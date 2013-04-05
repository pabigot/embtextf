/* Copyright (c) 2013, Peter A. Bigot
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
 * @brief Declarations for functions implementing libc stdarg functions
 *
 * Using #EMBTEXTF_PROVIDE_LIBC embtextf can provide implementations for
 * standard libc functions such as vprintf(), etc. based on an
 * application-provided putchar() implementation.
 *
 * These functions are provided: vprintf(), vsprintf(), vsnprintf()
 *
 * These functions are required: putchar()
 *
 * These functions are not provided: vfprintf()
 *
 * Stream-oriented functions (viz. those that reference a libc @c FILE
 * object) are not included as one might conceivably want to use @c
 * FILE to hold the #embtextf_putchar_fn instance that is used to
 * perform output to that stream.  If such an interface is desired it
 * can be provided by the application.
 *
 * @see <embtextf/stdio.h>.
 *
 * @homepage http://github.com/pabigot/embtextf
 * @copyright Copyright 2013, Peter A. Bigot.  Licensed under <a href="http://www.opensource.org/licenses/BSD-3-Clause">BSD-3-Clause</a>
 */

#ifndef EMBTEXTF_STDARG_H
#define EMBTEXTF_STDARG_H

#include <stdarg.h>

/** ISO C standard function based on embtextf_vuprintf() dependent on #EMBTEXTF_PROVIDE_LIBC. */
int vprintf(const char * fmt, va_list argp);

/** ISO C standard function based on embtextf_vuprintf() dependent on #EMBTEXTF_PROVIDE_LIBC. */
int vsprintf(char * s, const char * fmt, va_list argp);

/** ISO C standard function based on embtextf_vuprintf() dependent on #EMBTEXTF_PROVIDE_LIBC. */
int vsnprintf(char * s, size_t size, const char * fmt, va_list argp);

#endif /* EMBTEXTF_STDARG_H */
