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

typedef int (* vuprintf_emitchar_fn) (int);

#ifndef EMBTEXTF_VUPRINTF_ENABLE_INTPTR
#define EMBTEXTF_VUPRINTF_ENABLE_INTPTR 0
#endif /* EMBTEXTF_VUPRINTF_ENABLE_INTPTR */

#ifndef EMBTEXTF_VUPRINTF_ENABLE_LONG
#define EMBTEXTF_VUPRINTF_ENABLE_LONG 0
#endif /* EMBTEXTF_VUPRINTF_ENABLE_LONG */

#ifndef EMBTEXTF_VUPRINTF_ENABLE_LONGLONG
#define EMBTEXTF_VUPRINTF_ENABLE_LONGLONG 0
#endif /* EMBTEXTF_VUPRINTF_ENABLE_LONGLONG */

int vuprintf (vuprintf_emitchar_fn write_char, const char *format, va_list args);

int uprintf (vuprintf_emitchar_fn emit_char, const char *fmt, ...);

#endif /* EMBTEXTF_VUPRINTF_H */