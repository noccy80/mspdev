;*******************************************************************************
;   MSP430xG461x Demo - DAC12_0, Output 1.0V on DAC0
;
;   Description: Using DAC12_0 and AVcc reference with a gain of 1,
;   output 1.5V on DAC0
;
;
;                MSP430F6638
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |        DAC0/P6.6|--> 1.5V
;            |                 |
;
;   Priya Thanigai
;   Texas Instruments Inc.
;   August 2011
;   Built with CCS V5
;******************************************************************************
            .cdecls C,LIST,"msp430f6638.h"

;-------------------------------------------------------------------------------
            .global _main
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x63FE,SP              ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT

SetupDAC120 mov.w   #DAC12IR+DAC12SREF_1+DAC12AMP_5+DAC12CALON,&DAC12_0CTL0 
            bis.w   #DAC12ENC,&DAC12_0CTL0
            mov.w   #07ffh,&DAC12_0DAT      ; 1.5V
                                            ;
Mainloop    bis.w   #LPM0,SR                ; Enter LPM0
            nop                             ; Required only for debugger
                                            ;
;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end
