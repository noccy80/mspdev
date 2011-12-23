;*******************************************************************************
;   MSP430F66xx Demo - DAC12_0, Output Voltage Ramp on DAC0
;
;   Description: Using DAC12_0 and AVcc reference with a gain of 1,
;   output positive ramp on P6.6. Normal mode is LPM0 with CPU off.  WDT used
;   to provide ~0.5ms interrupt used to wake up the CPU and update the DAC
;   with software. 
;   ACLK = 32kHz, SMCLK = MCLK = WDTCLK = default DCO 1048576Hz
;
;
;                MSP430F6638
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |        DAC0/P6.6|--> Ramp_positive
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
SetupWDT    mov.w   #WDT_MDLY_0_064,&WDTCTL ; WDT ~0.064ms interval timer
            bis.w   #WDTIE,&SFRIE1          ; Enable WDT interrupt
SetupDAC120 mov.w   #DAC12IR+DAC12SREF_0+DAC12AMP_5+DAC12ENC,&DAC12_0CTL0 
                                            ;
Mainloop    bis.w   #CPUOFF+GIE,SR          ; Enter LPM0, interrupts enabled
            inc.w   &DAC12_0DAT             ; Positive ramp
            and.w   #0FFFh,&DAC12_0DAT      ;
            jmp     Mainloop                ;
                                            ;
;-------------------------------------------------------------------------------
WDT_ISR;    Exit LPM0 on reti
;-------------------------------------------------------------------------------
            bic.w   #CPUOFF,0(SP)           ; TOS = clear LPM0
            reti                            ;
                                            ;
;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int57"                ; ADC12 isr vector
            .short  WDT_ISR
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end
