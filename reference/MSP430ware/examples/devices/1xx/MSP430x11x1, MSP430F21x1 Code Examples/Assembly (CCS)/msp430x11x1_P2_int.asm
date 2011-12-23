;*******************************************************************************
;   MSP430x11x1 Demo - Software Port Interrupt on P2.0 from LPM4
;
;   Description: A hi/low transition on P2.0 will trigger P2_ISR which,
;   toggles P1.0. Normal mode is LPM4 ~ 0.1uA. LPM4 current can be measured
;   with the LED removed, all unused P1.x/P2.x configured as output or inputs
;   pulled high or low, and ensure the P2.0 interrupt input does not float.
;   ACLK = n/a, MCLK = SMCLK = default DCO ~800k
;
;                 MSP430F1121
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;      /|\   |                 |
;       --o--| P2.0        P1.0|-->LED
;      \|/
;
;   M. Buccini / Z. Albus
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430x11x1.h"
;-------------------------------------------------------------------------------
            .text                           ;
;-------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 output
            bis.b   #001h,&P2IE             ; P2.0 Interrupt enabled
            bis.b   #001h,&P2IES            ; P2.0 hi/low edge
            bic.b   #001h,&P2IFG            ; P2.0 IFG Cleared
                                            ;
Mainloop    bis.w   #LPM4+GIE,SR            ; LPM4, enable interrupts
            nop                             ; Required only for debugger
                                            ;
;-------------------------------------------------------------------------------
P2_ISR;     Toggle P1.0 Output
;-------------------------------------------------------------------------------
            xor.b   #001h,&P1OUT            ; P1.0 = toggle
            bic.b   #001h,&P2IFG            ; P2.0 IFG Cleared
            reti                            ; Return from ISR
                                            ;
;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int03"                ; P2.x Vector
            .short  P2_ISR                  ;
            .end
