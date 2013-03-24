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
 * @brief Utility functions for converting from integer to ASCII representations
 *
 * @section xtoa_intro Mixed-Base Integer to String Conversion Functions
 *
 * The routines in this module convert signed and unsigned @c int and
 * @c long values into text expressed in base 2 through base 36 and
 * stored a user-provided buffer.
 *
 * @homepage http://github.com/pabigot/embtextf
 * @copyright Copyright 2013, Peter A. Bigot.  Licensed under <a href="http://www.opensource.org/licenses/BSD-3-Clause">BSD-3-Clause</a>
 */

#ifndef EMBTEXTF_XTOA_H
#define EMBTEXTF_XTOA_H

/** Convert value into text representation.
 *
 * The value is converted into a base-@a radix ASCII representation.
 * If the radix is 10 and @a value is negative a minus sign will be
 * generated prior to representation of the absolute value of the
 * input.
 *
 * @param value the number to be converted
 *
 * @param str a buffer of sufficient size to hold the ASCII
 * representation of the value in the given base, including a
 * terminating NUL.  Passing an insufficiently large buffer results in
 * undefined behavior.
 *
 * @param radix the radix for the ASCII representation.  Valid values
 * are 2 through 36.  Multiples greater than 9 are represented by
 * capitalized alphabetics beginning with @c A (10) and continuing
 * through @c Z (35).  Passing an invalid value results in undefined
 * behavior.
 *
 * @return a pointer into str beginning at the first character of the
 * ASCII representation of the value. */
char * embtextf_itoa (int value, char * str, int radix);

/** As with itoa() but for unsigned integers. */
char * embtextf_utoa (unsigned int value, char * str, int radix);

/** As with itoa() but for long integers. */
char * embtextf_ltoa (long value, char * str, int radix);

/** As with itoa() but for unsigned long integers. */
char * embtextf_ultoa (unsigned long value, char * str, int radix);

/** As with itoa() but for long long integers.
 *
 * Availability conditional on #ENABLE_XTOA_LONGLONG. */
char * embtextf_lltoa (long long value, char * str, int radix);

/** As with itoa() but for unsigned long long integers. 
 *
 * Availability conditional on #ENABLE_XTOA_LONGLONG. */
char * embtextf_ulltoa (unsigned long long value, char * str, int radix);

#endif /* EMBTEXTF_XTOA_H */
