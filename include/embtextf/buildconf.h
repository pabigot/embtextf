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
 * @brief Build-time configuration options
 *
 * This header declares the configuration options that control feature availability.
 *
 * It should not be included by end-user programs, because it gives
 * the false impression that the defaults can be overridden to change
 * the behavior of the library or that they reflect the capabilities
 * of the library.  This may not be true when using an archive file
 * for which settings might have been overridden when the compilation
 * occurred.
 *
 * @homepage http://github.com/pabigot/embtextf
 * @copyright Copyright 2013, Peter A. Bigot.  Licensed under <a href="http://www.opensource.org/licenses/BSD-3-Clause">BSD-3-Clause</a>
 */

#ifndef EMBTEXTF_BUILDCONF_H
#define EMBTEXTF_BUILDCONF_H

#ifndef ENABLE_VUPRINTF_DEFAULT
/** Set to a preprocessor true value when the default for vuprintf
 * features is to enable them.  Set to a preprocessor false value when
 * the default for vuprintf features is to disable them. */
#define ENABLE_VUPRINTF_DEFAULT 1
#endif /* ENABLE_VUPRINTF_DEFAULT */

#ifndef ENABLE_VUPRINTF_INTPTR
/** Set to a preprocessor true value to allow the @c %p conversion
 * specification to support printing pointer values.  If false, the
 * conversion specification will be passed through as text. */
#define ENABLE_VUPRINTF_INTPTR ENABLE_VUPRINTF_DEFAULT
#endif /* ENABLE_VUPRINTF_INTPTR */

#ifndef ENABLE_VUPRINTF_LONG
/** Set to a preprocessor true value to allow the @c l length modifier
 * to be recognized supporting long integer parameters.  If false, the
 * @c l length modifier will be unrecognized and its containing
 * conversion specification passed through as text. */
#define ENABLE_VUPRINTF_LONG ENABLE_VUPRINTF_DEFAULT
#endif /* ENABLE_VUPRINTF_LONG */

#ifndef ENABLE_VUPRINTF_LONGLONG
/** Set to a preprocessor true value to allow two @c l length
 * modifiers to be recognized for a <c>long long</c> integer
 * parameter.  If false, the second @c l length modifier will be
 * unrecognized and its containing conversion specification passed
 * through as text.
 *
 * @note Use of this option requires use of
 * #ENABLE_VUPRINTF_LONG. */
#define ENABLE_VUPRINTF_LONGLONG ENABLE_VUPRINTF_DEFAULT
#endif /* ENABLE_VUPRINTF_LONGLONG */

#ifndef ENABLE_VUPRINTF_PRECISION
/** Set to a preprocessor true value to allow precision to be
 * recognized in conversion specifications.  If false, a precision
 * specification will be unrecognized and its containing conversion
 * specification passed through as text. */
#define ENABLE_VUPRINTF_PRECISION ENABLE_VUPRINTF_DEFAULT
#endif /* ENABLE_VUPRINTF_PRECISION */

#ifndef ENABLE_VUPRINTF_OCTAL
/** Set to a preprocessor true value to allow the @c %o conversion
 * specifier to be recognized.  If false, an octal conversion
 * specifier will be unrecognized and passed through as text. */
#define ENABLE_VUPRINTF_OCTAL ENABLE_VUPRINTF_DEFAULT
#endif /* ENABLE_VUPRINTF_OCTAL */

#ifndef ENABLE_VUPRINTF_ALTERNATE_FORM
/** Set to a preprocessor true value to allow the @c # alternate form
 * flag to be recognized for @c x and @c o conversions.  If false, the
 * alternate form flag will be unrecognized and its containing
 * conversion specification passed through as text. */
#define ENABLE_VUPRINTF_ALTERNATE_FORM ENABLE_VUPRINTF_DEFAULT
#endif /* ENABLE_VUPRINTF_ALTERNATE_FORM */

#ifndef ENABLE_XTOA_LONGLONG
/** Set to a preprocessor true value to generate conversion for @c
 * long @c long integer types.
 *
 * @c long @c long is a non-standard extension prior to C99.  If false,
 * the conversion specification will be passed through as text. */
#define ENABLE_XTOA_LONGLONG 1
#endif /* ENABLE_XTOA_LONGLONG */

#endif /* EMBTEXTF_BUILDCONF_H */
