;  MSP430F543xA Demo - Timer_B, Toggle P1.0, Overflow ISR, DCO SMCLK
;
;  Description: Toggle P1.0 using software and Timer_B overflow ISR.
;  In this example an ISR triggers when TB overflows.  TB overflow has the
;  lowest priority. Inside the TB overflow ISR P1.0 is toggled. Toggle rate is
;  approximatlely 7.822Hz = [1.045MHz/FFFFh]/2. Proper use of TBIV interrupt vector
;  generator is shown.
;  ACLK = n/a, MCLK = SMCLK = TBCLK = default DCO ~1.045MHz.
;
;           MSP430F5438A
;         ---------------
;     /|\|               |
;      | |               |
;      --|RST            |
;        |               |
;        |           P1.0|-->LED
;
;   D. Dang
;   Texas Instruments Inc.
;   December 2009
;   Built with CCS Version: 4.0.2 
;******************************************************************************

    .cdecls C,LIST,"msp430x54xA.h"

;-------------------------------------------------------------------------------
            .global _main 
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x5C00,SP              ; Initialize stackpointer
            mov.w   #WDTPW + WDTHOLD,&WDTCTL; Stop WDT    
            bis.b   #BIT0,&P1DIR            ; P1.0 output
            mov.w   #TBSSEL_2 + MC_2 + TBCLR + TBIE,&TBCTL
                                            ; SMCLK, contmode, clear TBR
                                            ; enable interrupt
            bis.w   #LPM0 + GIE,SR          ; Enter LPM0, enable interrupts 
            nop                             ; For debugger
            
;-------------------------------------------------------------------------------
TIMERB1_ISR                          ; Timer_B Interrupt Vector (TBIV) handler
;-------------------------------------------------------------------------------
            add.w  #TBIV,PC                 ; Vector to ISR handler
            reti                            ; No interrupt
            reti                            ; CCR1 not used
            reti                            ; CCR2 not used
            reti                            ; CCR3 not used
            reti                            ; CCR4 not used
            reti                            ; CCR5 not used
            reti                            ; CCR6 not used
TBIFG_HND   xor.b  #BIT0,&P1OUT             ; Timer overflow handler 
            reti                            ; Return from interrupt 

;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int59"     
            .short  TIMERB1_ISR
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end