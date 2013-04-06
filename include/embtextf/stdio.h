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
 * @brief Declarations for functions implementing libc stdio functions
 *
 * Using #EMBTEXTF_ENABLE_PROVIDE_LIBC embtextf can provide
 * implementations for standard libc functions such as printf(),
 * puts(), etc. based on an application-provided putchar()
 * implementation.
 *
 * These functions are provided: printf(), sprintf(), snprintf(), setvbuf()
 *
 * These functions are required: putchar()
 *
 * These functions are not provided: fprintf(), fputc(), fputs(), putc()
 *
 * Stream-oriented functions (viz. those that reference a libc @c FILE
 * object) are not included as one might conceivably want to use @c
 * FILE to hold the #embtextf_putchar_fn instance that is used to
 * perform output to that stream.  If such an interface is desired it
 * can be provided by the application.
 *
 * @see <embtextf/stdarg.h>.
 *
 * @homepage http://github.com/pabigot/embtextf
 * @copyright Copyright 2013, Peter A. Bigot.  Licensed under <a href="http://www.opensource.org/licenses/BSD-3-Clause">BSD-3-Clause</a>
 */

#ifndef EMBTEXTF_STDIO_H
#define EMBTEXTF_STDIO_H

#if defined(EMBTEXTF_DOXYGEN)
/** The <stdio.h> constant that indicates an error.
 *
 * @warning This is declared for documentation purposes only.  The
 * actual value is obtained from the toolchain's <stdio.h> header.
 * Normally one should expect its value to be -1. */
#define EOF -1

/** Declaration for stream-dependent function
 *
 * This function is defined at the link-level because some BSPs
 * (e.g. for Energy Micro's chips) assume it is available when using
 * GCC and newlib.  Since a major purpose of this module is to bypass
 * newlib's bloated i/o infrastructure we stub the function so that
 * it's ignored.
 *
 * Note that because the real function prototype depends on @c FILE
 * and we don't know that type we're describing the corresponding
 * argument as if it were a pointer-to-void; in fact, this prototype
 * is present only in the documentation, not in the actual header used
 * when building the library or applications that use it.  We assume
 * that at the binary interface level a pointer-to-void will be passed
 * in the same manner as a pointer-to-@c FILE.
 *
 * The implementation does nothing but return EOF. */
int setvbuf (void * stream, char * buf, int mode, size_t size);

#endif /* EMBTEXTF_DOXYGEN */

/** Write a single character, cast to an unsigned char, to an output device.
 *
 * @param c the character to be emitted.
 *
 * @return the character, or #EOF if an error occurs.
 *
 * @note The implementation of this function must be provided externally to embtextf.
 *
 * @note The implementation of functions that use putchar() may ignore
 * any error return from putchar(). */
extern int putchar (int c);

/** ISO C standard function based on putchar() dependent on #EMBTEXTF_ENABLE_PROVIDE_LIBC.
 *
 * @param s the string to be written.  The terminating NUL is not
 * emitted.
 *
 * @return A non-negative number on success, or #EOF if an error is
 * encountered. */
int puts (const char * s);

/** ISO C standard function based on embtextf_vuprintf() dependent on #EMBTEXTF_ENABLE_PROVIDE_LIBC. */
int
#if __GNUC__
__attribute__((format (printf, 1, 2)))
#endif /* __GNUC__ */
printf (const char *fmt, ...);

/** ISO C standard function based on embtextf_vuprintf() dependent on #EMBTEXTF_ENABLE_PROVIDE_LIBC. */
int
#if __GNUC__
__attribute__((format (printf, 2, 3)))
#endif /* __GNUC__ */
sprintf (char * s, const char * fmt, ...);

/** ISO C standard function based on embtextf_vuprintf() dependent on #EMBTEXTF_ENABLE_PROVIDE_LIBC. */
int
#if __GNUC__
__attribute__((format (printf, 3, 4)))
#endif /* __GNUC__ */
snprintf (char * s, size_t size, const char * fmt, ...);

#endif /* EMBTEXTF_STDIO_H */
