;******************************************************************************
;   MSP-FET430P430 Demo - DMA0, Repeated Block to DAC0 Sine Output, CCR2, DCO
;
;   Description: DMA0 is used to transfer a sine look-up table word-by-word
;   as a repeating block to DAC12_0. The effect is sine wave output. Timer_A
;   operates in up mode with CCR2 loading DAC12.0 on rising edge and DAC12_0IFG
;   triggering next DMA0 transfer. DAC12_0 uses internal 1.5V reference.
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;                MSP430FG439
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |        P6.6/DAC0|--> ~ 1kHz sine wave
;            |                 |
;
;
;   M. Buccini / M. Mitchell
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Compose Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430xG43x.h"
;------------------------------------------------------------------------------
            .text                  ; Progam Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
SetupADC12  mov.w   #REFON,&ADC12CTL0       ; Internal reference
SetupDMA0   mov.w   #Sin_tab,&DMA0SA        ; Source block address
            mov.w   #DAC12_0DAT,&DMA0DA     ; Destination single address
            mov.w   #020h,&DMA0SZ           ; Block size
            mov.w   #DMA0TSEL_5,&DMACTL0    ; DAC12IFG trigger
            mov.w   #DMADT_4+DMASRCINCR_3+DMAEN,&DMA0CTL; Rpt, inc src, word-word
SetupDAC120 mov.w   #DAC12LSEL_2+DAC12IR+DAC12AMP_5+DAC12IFG+DAC12ENC,&DAC12_0CTL
SetupC1     mov.w   #OUTMOD_3,&CCTL1        ; CCR1 set/reset
            mov.w   #01,&CCR1               ; CCR1 PWM Duty Cycle	
SetupC0     mov.w   #032-1,&CCR0            ; Clock period of CCR0
SetupTA     mov.w   #TASSEL_2+MC_1,&TACTL   ; SMCLK, contmode
                                            ;
Mainloop    bis.b   #CPUOFF,SR              ; Enter LPM0
            nop                             ; Needed only for debugger
                                            ;
;------------------------------------------------------------------------------
; 12-bit Sine Lookup table with 32 steps
;------------------------------------------------------------------------------
Sin_tab     .short 2048, 2447, 2831, 3185, 3495, 3750, 3939, 4056
            .short 4095, 4056, 3939, 3750, 3495, 3185, 2831, 2447
            .short 2048, 1648, 1264,  910,  600,  345,  156,   39
            .short 0,   39,  156,  345,  600,  910, 1264, 1648
                                            ;
;-----------------------------------------------------------------------------
;           Interrupt Vectors
;-----------------------------------------------------------------------------
            .sect   ".reset"                ; RESET Vector
            .short  RESET                   ;
            .end
