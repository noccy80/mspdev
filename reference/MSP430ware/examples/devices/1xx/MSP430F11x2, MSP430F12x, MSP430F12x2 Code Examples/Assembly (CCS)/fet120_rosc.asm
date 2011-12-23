;******************************************************************************
;   MSP-FET430P120 Demo - DCOCLK Biased with External Resistor Rosc
;
;   Description: Use external resistor on P2.5 as DCO current source. DCOCLK
;   is used by default as the MCLK source. Mainloop drives a 10 cycle software
;   loop toggling P1.1. Measure DCOCLK/10 on P1.1. Example also disables XTAL
;   buffer. Use of external resistor reduces temperature sensitivity of DCOCLK.
;
;   DCOCLK = Using default DCO and RSEL values @ 2.85V
;   022k ~ 5.5MHz
;   100k ~ 2Mhz
;   220k ~ 860kHz
;   470k ~ 400kHz
;
;                MSP430F123(2)
;             -----------------
;    /|\  /|\|              XIN|-
;     |    | |                 |
;     R    --|RST          XOUT|-
;     |      |                 |
;     -------|P2.5/ROSC    P1.1|-->DCOCLK/10
;
;   M. Buccini / M. Raju
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x12x2.h"
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupBC     bis.b   #DCOR,&BCSCTL2          ; Rosc
            bis.w   #OSCOFF,SR              ; XTAL not used
            bis.b   #002h,&P1DIR            ; P1.1 = output direction
                                            ;
Mainloop    bis.b   #002h,&P1OUT            ; P1.1 = 1
            bic.b   #002h,&P1OUT            ; P1.1 = 0
            jmp     Mainloop                ; Repeat
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
