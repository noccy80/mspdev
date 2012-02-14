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
#include "flash.h"
#include "delay.h"
#include "copy.h"

#include "check_freq.h"

#if defined(__MSP430_HAS_FLASH2__)
#define SEGMENT_A 0x10c0
uint16_t backup_segment_a[32];  /* 64 bytes */
#define INDEX_FREQ4 28
#define INDEX_FREQ3 29
#define INDEX_FREQ2 30
#define INDEX_1MHZ 31
#else  /* !defined(__MSP430_HAS_FLASH2__) */
#define SEGMENT_A 0x1080
uint16_t backup_segment_a[64];  /* 128 byte */
#define INDEX_FREQ4 60
#define INDEX_FREQ3 61
#define INDEX_FREQ2 62
#define INDEX_1MHZ 63
#endif

static void blink_led(void) {
    dco_set(backup_segment_a[INDEX_1MHZ]);
    uint16_t notify_loop = 10;
    while (--notify_loop != 0) {
        /* turn on LED */
        P1OUT = 0x01;
        delay_1000n(100);

        /* turn off LED */
        P1OUT = 0x00;
        delay_1000n(900);
    }
}

int main() __attribute__ ((noreturn));
int main() {
    /* Configure P1.0 as output */
    P1DIR = 0x01;

    copy_word(backup_segment_a, (const uint16_t *)SEGMENT_A, ARRAY_SIZE(backup_segment_a));

    dco_setup_calibrate();
    backup_segment_a[INDEX_1MHZ] = dco_calibrate(1000); /* 1MHz */
    backup_segment_a[INDEX_FREQ2] = dco_calibrate(FREQ2_KHZ);
    backup_segment_a[INDEX_FREQ3] = dco_calibrate(FREQ3_KHZ);
    backup_segment_a[INDEX_FREQ4] = dco_calibrate(FREQ4_KHZ);

#if defined(WRITE_TO_FLASH)
    flash_setup(backup_segment_a[INDEX_1MHZ]);
    flash_erase_segment_a();
    flash_write_block(backup_segment_a, (uint16_t *)SEGMENT_A, ARRAY_SIZE(backup_segment_a));
    blink_led();
    flash_erase_mass();         /* erase main flash, then turn on LED */
#else
    for (;;)
        blink_led();
#endif
}

/*
 * Local Variables:
 * c-file-style: "bsd"
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 * vim: set et ts=4 sw=4:
 */
