;******************************************************************************
;  MSP430F54x Demo - Software Port Interrupt Service on P1.4 from LPM4 with
;                    Internal Pull-up Resistance Enabled
;
;  Description: A hi "TO" low transition on P1.4 will trigger P1_ISR which,
;  toggles P1.0. P1.4 is internally enabled to pull-up. Normal mode is
;  LPM4 ~ 0.1uA. LPM4 current can be measured with the LED removed, all
;  unused Px.x configured as output or inputs pulled high or low.
;  ACLK = n/a, MCLK = SMCLK = default DCO
;
;               MSP430F5438
;            -----------------
;        /|\|              XIN|-
;         | |                 |
;         --|RST          XOUT|-
;     /|\   |                 |
;      --o--|P1.4         P1.0|-->LED
;     \|/
;
;   M. Morales
;   Texas Instruments Inc.
;   September 2008
;   Built with Code Composer Essentials v3.x
;******************************************************************************

    .cdecls C,LIST,"msp430x54x.h"

;-------------------------------------------------------------------------------
            .global _main 
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x5C00,SP              ; Initialize stackpointer
            mov.w   #WDTPW + WDTHOLD,&WDTCTL; Stop WDT    
            bis.b   #BIT0,&P1DIR            ; Set P1.0 to output direction
            bis.b   #BIT4,&P1REN            ; Enable P1.4 internal resistor
            bis.b   #BIT4,&P1OUT            ; Set P1.4 as pull-Up resistor
            bis.b   #BIT4,&P1IE             ; P1.4 Interrupt enabled
            bis.b   #BIT4,&P1IES            ; P1.4 Hi/Lo edge
            bic.b   #BIT4,&P1IFG            ; P1.4 IFG cleared

            bis.w   #LPM4 + GIE,SR          ; Enter LPM4, enable interrupts
            nop                             ; For debugger
;-------------------------------------------------------------------------------
PORT1_ISR
;-------------------------------------------------------------------------------
            xor.b   #BIT0,&P1OUT            ; Toggle P1.0 (LED) 
            bic.b   #BIT4,&P1IFG            ; Clear P1.4 IFG 
            reti                            ; Return from interrupt 

;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int47"    
            .short  PORT1_ISR
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end            
