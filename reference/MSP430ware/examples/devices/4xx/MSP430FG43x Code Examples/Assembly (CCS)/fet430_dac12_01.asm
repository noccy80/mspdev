;******************************************************************************
;   MSP-FET430P430 Demo - DAC12_0, Output 1.0V on DAC0
;
;   Description: Using DAC12_0 and 2.5V ADC12REF reference with a gain of 1,
;   output 1V on DAC0.
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;                MSP430FG439
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |        P6.6/DAC0|--> 1V
;            |                 |
;
;   M. Buccini / M. Mitchell
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430xG43x.h"
;------------------------------------------------------------------------------
            .text                  ; Progam Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupADC12  mov.w   #REF2_5V+REFON,&ADC12CTL0        ; Internal 2.5V ref on
SetupDAC120 mov.w   #DAC12IR+DAC12AMP_5+DAC12ENC,&DAC12_0CTL  ; Int ref gain 1
            mov.w   #0666h,&DAC12_0DAT      ; 1.0V
                                            ;
Mainloop    bis.w   #CPUOFF,SR              ; Enter LPM0
            nop                             ; Required only for debugger
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; RESET Vector
            .short  RESET                   ;
            .end
