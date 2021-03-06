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

static char *
xtoa (INT_T sval,
      char * str,
      int radix,
      int signedp)
{
  unsigned INT_T uval;
  unsigned int uradix = radix;
  char *sp = str;
  char *sp2;

  /* If signed, store sign at start of buffer for negative base-10 values */
  if (signedp && (10 == uradix) && (0 > sval)) {
    *sp++ = '-';
    uval = -sval;
  } else {
    uval = sval;
  }
  sp2 = sp;

  do {
    unsigned int rem = uval % uradix;
    uval /= uradix;
    if (10 > rem) {
      *sp++ = '0' + rem;
    } else {
      *sp++ = 'A' + rem - 10;
    }
  } while (0 < uval);

  /* Mark end of string */
  *sp-- = 0;

  /* Reverse string contents (excluding sign) in place */
  while (sp2 < sp) {
    char tmp = *sp2;
    *sp2++ = *sp;
    *sp-- = tmp;
  }

  return str;
}

char *
STOA(INT_T num, char *str, int radix)
{
  return xtoa(num, str, radix, 1);
}

char *
UTOA(unsigned INT_T num, char *str, int radix)
{
  return xtoa((INT_T)num, str, radix, 0);
}

/*
 * Local Variables:
 * mode:c
 * End:
 */
