;*******************************************************************************
;   MSP430F22x4 Demo - Software Port Interrupt Service on P1.2 from LPM4
;
;   Description: A hi/low transition on P1.2 will trigger P1_ISR which,
;   toggles P1.0. Normal mode is LPM4 ~ 0.1uA. LPM4 current can be measured
;   with the LED removed, all unused Px.x configured as output or inputs
;   pulled high or low, and ensure the P1.2 interrupt input does not float.
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;                MSP430F22x4
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;      /|\   |                 |
;       --o--|P1.2         P1.0|-->LED
;      \|/
;
;  P.Thanigai / W. Goh
;  Texas Instruments Inc.
;  November 2008
;  Built with Code Composer Essentials Version: 3.2.2
;*******************************************************************************
 .cdecls C,LIST,  "msp430x22x4.h"
                              
;------------------------------------------------------------------------------
            .text                  			; Program reset
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupPx     bis.b   #001h,&P1DIR            ; P1.0 output
            bis.b   #004h,&P1IE             ; P1.2 Interrupt enabled
            bis.b   #004h,&P1IES            ; P1.2 hi/low edge
            bic.b   #004h,&P1IFG            ; P1.2 IFG Cleared
                                            ;
Mainloop    bis.w   #LPM4+GIE,SR            ; LPM4, enable interrupts
            nop                             ; Required only for debugger
                                            ;
;-------------------------------------------------------------------------------
P1_ISR;     Toggle P1.0 Output
;-------------------------------------------------------------------------------
            xor.b   #001h,&P1OUT            ; P1.0 = toggle
            bic.b   #004h,&P1IFG            ; P1.2 IFG Cleared
            reti                            ; Return from ISR
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int02"                ; P1.x Vector
            .short  P1_ISR                  ;
            .end
