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

#include "dco.h"
#include "delay.h"

#if !defined(LFXT1_HZ)
#define LFXT1_HZ 32768          /* 32.768kHz */
#elif LFXT1_HZ < 1000
#error "LFXT1_HZ is too low"
#elif LFXT1_HZ > 40000
#error "LFXT1_HZ is too high"
#endif

void dco_set(uint16_t calib) {
#if defined(ERRATA_BCL12)
    /* Errata BCL12 - Switching RSEL can cause DCO dead time
     *  RSEL=14..15 -> RSEL=0..12 : switch to 13 first, then to target RSEL
     *  RSEL=0..12  -> RSEL=13..15: set DCO to 0 first, then set target RSEL, and set DCO. */
    uint8_t old_bc1 = BCSCTL1;
    uint8_t cur_rsel = old_bc1 & RSEL_MASK;
    uint8_t new_rsel = calib2rsel(calib);
    old_bc1 &= ~RSEL_MASK;
    if (cur_rsel >= 14 && new_rsel <= 12) {
        BCSCTL1 = old_bc1 | 13;
        BCSCTL1 = old_bc1 | new_rsel;
        DCOCTL = calib2dco(calib);
    } else {
        DCOCTL &= ~(DCO2|DCO1|DCO0); /* DCO=0 */
        BCSCTL1 = old_bc1 | new_rsel;
        DCOCTL = calib2dco(calib);
    }
#elif defined(ERRATA_BCL5)
    /* Errata BCL5 - RSEL bit modification can generate high frequency spikes on MCLK
     *  DIVM=0 or 1 cause this issue.
     * Setting DIVM=2 or 3 and modify RSEL and restore DIVM will work. */
    uint8_t old_bc2 = BCSCTL2;
    BCSCTL2 |= DIVM1;
    BCSCTL1 = (BCSCTL1 & ~RSEL_MASK) | calib2rsel(calib);
    DCOCTL = calib2dco(calib);
    BCSCTL2 = old_bc2;
#else
    BCSCTL1 = (BCSCTL1 & ~RSEL_MASK) | calib2rsel(calib);
    DCOCTL = calib2dco(calib);
#endif
}

static uint16_t dco_fine(uint16_t calib, uint16_t dco_khz) {
    dco_set(calib);
    P1OUT ^= 1;
    TACTL |= TACLR;             /* clear TAR */
    delay_1000n(dco_khz);
    return TAR;
}

static uint16_t dco_coarse(uint16_t calib, uint16_t dco_khz) {
    dco_set(calib);
    P1OUT ^= 1;
    TACTL |= TACLR;             /* clear TAR */
    delay_10n(dco_khz);
    return TAR;
}

uint16_t dco_calibrate(uint16_t dco_khz) {
    uint16_t calib = 0;
    uint16_t step;
    for (step = rsel2calib(RSEL_MAXBIT); step >= DCO0; step >>= 1) {
        if (dco_coarse(calib | step, dco_khz) >= LFXT1_HZ / 100)
            calib |= step;
    }

    for (step = rsel2calib(RSEL_MAXBIT); step != 0; step >>= 1) {
        if (dco_fine(calib | step, dco_khz) >= LFXT1_HZ) {
            calib |= step;
        } else {
            calib &= ~step;
        }
    }

    if ((calib2dco(calib) & (DCO2 | DCO1 | DCO0)) == (DCO2 | DCO1 | DCO0))
        calib &= ~(MOD4 | MOD3 | MOD2 | MOD1 | MOD0); /* clear MODx */

    return calib | (XT2OFF << 8);
}

void dco_setup_calibrate() {
    /* set LFXT1/32.768kHz XTAL oscillator */
    BCSCTL1 &= ~(XTS | DIVA1 | DIVA0); /* LF mode, ACLK=LFXT1CLK/1 */
#if defined(__MSP430_HAS_BC2__)
#if defined(ERRATA_XOSC8)
    BCSCTL3 = LFXT1S_0 | XCAP_3; /* LFXT1=32.768kHz, CAP=12.5pF */
#else
    BCSCTL3 = LFXT1S_0 | XCAP_2; /* LFXT1=32.768kHz, CAP=10pF */
#endif
    P2SEL |= 0xc0;              /* enable P2.6/XIN and P2.7/XOUT */
    P2OUT |= 0x80;              /* some chips need P2.7 set as OUT */
#endif

    /* turn on DCO and LFXT1 */
    _BIC_SR(SCG0 | OSCOFF);

#if defined(__MSP430_HAS_BC2__)
    /* wait for oscillating */
    do {
        IFG1 &= ~OFIFG;
        delay_995();
    } while ((IFG1 & OFIFG) != 0);
#else
    /* In MSP430x1xx, OFIFG works only for LFXT1/HF mode or XT2 */
    delay_1000n(100);
#endif

#if defined(USE_ROSC)
    /* MCLK=DCOCLK/1, SMCLK=DCOCLK/1, external Rosc */
    BCSCTL2 = SELM_0 | DIVM_0 | DIVS_0 | DCOR;
#else
    /* MCLK=DCOCLK/1, SMCLK=DCOCLK/1, internal Rosc */
    BCSCTL2 = SELM_0 | DIVM_0 | DIVS_0;
#endif

    /* TimerA=ACLK/1, continuous mode, reset */
    TACTL = TASSEL_1 | ID_0 | MC_2 | TACLR;
}

/*
 * Local Variables:
 * c-file-style: "bsd"
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 * vim: set et ts=4 sw=4:
 */
