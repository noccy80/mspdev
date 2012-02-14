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

#include <stdint.h>

#include "flash.h"
#include "dco.h"
#include "copy.h"

uint16_t code_in_ram[18];
#define CODE_IN_FLASH 0           /* must be 0, debug purpose */

static void flash_lock_segment(void) __attribute__ ((noinline));
static void flash_lock_segment(void) {
#if defined(__MSP430_HAS_FLASH2__)
    uint16_t lock_bits = (FCTL3 & LOCKA) ^ LOCKA;
    FCTL3 = FWKEY | LOCK | lock_bits;
#else
    FCTL3 = FWKEY | LOCK;
#endif
}

static void flash_unlock_segment(void) __attribute__ ((noinline));
static void flash_unlock_segment(void) {
#if defined(__MSP430_HAS_FLASH2__)
    uint16_t lock_bits = FCTL3 & LOCKA;
    FCTL3 = FWKEY | lock_bits;
#else
    FCTL3 = FWKEY;
#endif
}

void flash_setup(uint16_t calibrated_1mhz_dco) {
    dco_set(calibrated_1mhz_dco);
    FCTL2 = FWKEY | FSSEL_1 | (3 - 1); /* fFTG=MCLK/3=333kHz */
}

void flash_erase_segment_a() {
    flash_unlock_segment();
    FCTL1 = FWKEY | ERASE;
    *(uint16_t *)0x10c0 = 0;    /* trigger erase segment A */
    FCTL1 = FWKEY;
    flash_lock_segment();
}

#if CODE_IN_FLASH
static void do_mass_erase(uint16_t *etext) __attribute__ ((noreturn,noinline));
static void do_mass_erase(uint16_t *etext) {
    FCTL3 = FWKEY;              /* unlock main flash */
    FCTL1 = FWKEY | MERAS;
    *etext = 0;                 /* trigger mass erase main flash */
    while (FCTL3 & BUSY)        /* wait for erasing */
        ;
    FCTL3 = FWKEY | LOCK;       /* lock main flash */
    P1OUT |= 1;                 /* turn LED on */
    for (;;)
        ;
}
#else
typedef void (*do_mass_erase_t)(uint16_t *etext) __attribute__ ((noreturn));
#define do_mass_erase(etext)                                            \
    do {                                                                \
        copy_word(code_in_ram, do_mass_erase_body, ARRAY_SIZE(do_mass_erase_body)); \
        ((do_mass_erase_t)code_in_ram)(etext);                          \
    } while (0)
static const uint16_t do_mass_erase_body[] = {
    0x40b2, 0xa500, 0x012c,     /* mov #FWKEY,&FCTL3 */
    0x40b2, 0xa504, 0x0128,     /* mov #FWKEY|MERAS,&FCTL1 */
    0x438f, 0x0000,             /* mov #0,0(r15) */
    0xb392, 0x012c,             /* 1: bit #BUSY,&FCTL3 */
    0x23fd,                     /* jnz 1b */
    0x40b2, 0xa510, 0x012c,     /* mov #FWKEY|LOCK,&FCTL3 */
    0xd3d2, 0x0021,             /* bis.b #1,&P1OUT */
    0x3fff,                     /* 2: jmp 2b */
};
#endif

void flash_erase_mass() {
    extern uint16_t _etext[];   /* end of .text section */
    do_mass_erase(_etext);
}

#if CODE_IN_FLASH
static void do_block_write(uint16_t *to, const uint16_t *from, uint16_t *end)
    __attribute__ ((noinline));
static void do_block_write(uint16_t *to, const uint16_t *from, uint16_t *end) {
    FCTL1 = FWKEY | BLKWRT | WRT; /* enable block write */
    while (to < end) {
        *to++ = *from++;
        while ((FCTL3 & WAIT) == 0) /* wait for buffer ready */
            ;
    }
    FCTL1 = FWKEY;
    while (FCTL3 & BUSY)        /* wait for writing completion */
        ;
}
#else
typedef void (*do_block_write_t)(uint16_t *to, const uint16_t *from, uint16_t *end);
#define do_block_write(to, from, end)                                   \
    do {                                                                \
        copy_word(code_in_ram, do_block_write_body, ARRAY_SIZE(do_block_write_body)); \
        ((do_block_write_t)code_in_ram)((to), (from), (end));           \
    } while (0)
static const uint16_t do_block_write_body[] = {
    0x40b2, 0xa5c0, 0x0128,     /* mov #FWKEY|BLKWRT|WRT,&FCTL1 */
    0x4ebf, 0x0000,             /* 1: mov @r14+,0(r15) */
    0xb2b2, 0x012c,             /* 2: bit #WAIT,&FCTL3 */
    0x27fd,                     /* jz 2b */
    0x532f,                     /* incd r15 */
    0x9d0f,                     /* cmp r13,r15 */
    0x2bf8,                     /* jnc 1b */
    0x40b2, 0xa500, 0x0128,     /* mov #FWKEY,&FCTL1 */
    0xb392, 0x012c,             /* 3: bit #BUSY,&FCTL3 */
    0x23fd,                     /* jnz 3b */
    0x4130,                     /* ret */
};
#endif

void flash_write_block(const uint16_t *from, uint16_t *to, uint16_t words) {
    flash_unlock_segment();
    while (words > 0) {
        uint16_t size = (words < 32) ? words : 32;
        do_block_write(to, from, to + size);
        to += size;
        from += size;
        words -= size;
    }
    flash_lock_segment();
}

#if 0
void flash_write_word(uint16_t data, uintptr_t addr) {
    flash_unlock_segment();
    FCTL1 = FWKEY | WRT;
    *(uint16_t *)addr = data;
    FCTL1 = FWKEY;
    flash_lock_segment();
}
#endif

/*
 * Local Variables:
 * c-file-style: "bsd"
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 * vim: set et ts=4 sw=4:
 */
