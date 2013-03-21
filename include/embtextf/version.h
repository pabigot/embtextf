/* Copyright 2013, Peter A. Bigot
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
 *
 * @brief Version data and documentation for embtextf library
 *
 * @homepage http://github.com/pabigot/embtextf
 * @copyright @copyrightblock
 *
 * @mainpage embtextf: Embedded System Text Formatting
 *
 * embtextf is a collection of functions supporting *printf(3c) and
 * numeric formatting functionality on embedded devices with highly
 * constrained memory:
 *
 * @li The base embtextf_vuprintf() function supports *printf(3c)
 * functions through a caller-provided callback function that handles
 * each formatted character as it is produced.  This approach
 * eliminates the need for large internal buffers to hold the
 * constructed data.
 *
 * @li The supported @ref uprintf_format "format-string capabilities"
 * cover most non-floating-point format specifiers and modifiers, with
 * some compile-time control to mediate between features and required
 * code space.
 *
 * @li @ref xtoa_intro format @c int and @c long values into a
 * caller-provided buffer in any radix from base 2 to base 36.
 *
 * The conversions operate on native C types, abstracting away from
 * word size and byte order.  The module has been tested on both 16-
 * and 32-bit microcontrollers.
 *
 * Each provided function is prefixed with @c embtextf_ to isolate it
 * from both the toolchain and application namespaces.  This allows
 * embtextf to co-exist with toolchains like mspgcc, which provide the
 * same functionality in a compatible way, and others like Code
 * Composer Studio which provide similarly named functions but with
 * different semantics or interfaces.  The application program can use
 * the preprocessor to redirect unqualified names to the embtextf
 * implementations.
 *
 * @homepage http://github.com/pabigot/embtextf
 * @copyright Copyright 2011-2013, Peter A. Bigot.  embtextf_vuprintf() contains material copyright 2011, Chris Liechti.  Licensed under <a href="http://www.opensource.org/licenses/BSD-3-Clause">BSD-3-Clause</a>
 */

#ifndef EMBTEXTF_VERSION_H
#define EMBTEXTF_VERSION_H

/** Version of the embtextf library.  This is a monotonically
 * non-decreasing integer value suitable for ordinal comparisons. */
#define EMBTEXTF_VERSION 20130321

#endif /* EMBTEXTF_VERSION_H */
