/* Copyright (c) 2011, Peter A. Bigot
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 * - Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdarg.h>
#include <limits.h>

/** Maximum number of characters that can be stored.
 *
 * On the MSP430, generating a string longer than 32767 characters is
 * really not rational. */
static int available_;

/** Pointer to the next location into which an output can be stored */
static char *destination_;

static int
append (int c)
{
  if (available_ <= 0)
    return -1;
  *destination_++ = c;
  --available_;
  return c;
}

static int
call_vuprintf (const char *fmt, va_list argp)
{
  char *destination = destination_;
  int available = available_;
  int rc;

  rc = vuprintf (append, fmt, argp);
  va_end (argp);
  if (rc >= available)
    destination[available - 1] = 0;
  else
    *destination_ = 0;
  return rc;
}

int
sprintf (char *buf, const char *fmt, ...)
{
  va_list argp;

  va_start (argp, fmt);
  destination_ = buf;
  available_ = INT_MAX;
  return call_vuprintf (fmt, argp);
}

int
snprintf (char *buf, size_t size, const char *fmt, ...)
{
  va_list argp;

  va_start (argp, fmt);
  destination_ = buf;
  available_ = size;
  return call_vuprintf (fmt, argp);
}

int
vsprintf (char *buf, const char *fmt, va_list argp)
{
  destination_ = buf;
  available_ = INT_MAX;
  return call_vuprintf (fmt, argp);
}

int
vsnprintf (char *buf, size_t size, const char *fmt, va_list argp)
{
  destination_ = buf;
  available_ = size;
  return call_vuprintf (fmt, argp);
}
