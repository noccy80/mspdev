/* -*- mode: c; mode: flyspell-prog; -*- */
/* Copyright (c) 2010, Tadashi G Takaoka
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
 * - Neither the name of Tadashi G. Takaoka nor the names of its
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

#include <msp430.h>

#if defined(__MSP430_HAS_BC2__)

#if !defined(FREQ2_KHZ)
#define FREQ2_KHZ 8000          /* 8MHz */
#elif FREQ2_KHZ < 100
#error "FREQ2_KHZ is too low"
#elif FREQ2_KHZ > 16000
#error "FREQ2_KHZ is too high"
#endif

#if !defined(FREQ3_KHZ)
#define FREQ3_KHZ 12000         /* 12MHz */
#elif FREQ3_KHZ < 100
#error "FREQ3_KHZ is too low"
#elif FREQ3_KHZ > 16000
#error "FREQ3_KHZ is too high"
#endif

#if !defined(FREQ4_KHZ)
#define FREQ4_KHZ 16000         /* 16MHz */
#elif FREQ4_KHZ < 100
#error "FREQ4_KHZ is too low"
#elif FREQ4_KHZ > 16000
#error "FREQ4_KHZ is too high"
#endif

#else

#if !defined(FREQ2_KHZ)
#define FREQ2_KHZ 8000          /* 8MHz */
#elif FREQ2_KHZ < 100
#error "FREQ2_KHZ is too low"
#elif FREQ2_KHZ > 8000
#error "FREQ2_KHZ is too high"
#endif

#if !defined(FREQ3_KHZ)
#define FREQ3_KHZ 2000          /* 2MHz */
#elif FREQ3_KHZ < 100
#error "FREQ3_KHZ is too low"
#elif FREQ3_KHZ > 8000
#error "FREQ3_KHZ is too high"
#endif

#if !defined(FREQ4_KHZ)
#define FREQ4_KHZ 4000          /* 4MHz */
#elif FREQ4_KHZ < 100
#error "FREQ4_KHZ is too low"
#elif FREQ4_KHZ > 8000
#error "FREQ4_KHZ is too high"
#endif

#endif

/*
 * Local Variables:
 * c-file-style: "bsd"
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 * vim: set et ts=4 sw=4:
 */
