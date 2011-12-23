;*******************************************************************************
;   MSP430F21x2 Demo - DCOCLK Biased with External Resistor Rosc
;
;   Description: Use external resistor on P2.5 as DCO current source. DCOCLK
;   is used by default as the MCLK source. Mainloop drives a 10 cycle software
;   loop toggling P1.1. Measure DCOCLK/10 on P1.1. Example also disables XTAL
;   buffer. Use of external resistor reduces temperature sensitivity of DCOCLK.
;   NOTE: With no resistor conencted, the oscillator will stop. Also, in this
;   case, the ability of re-establishing JTAG connectivity may be affected.
;
;   DCOCLK Frequency using DCO = 3 and RSEL = 4 values @ 3V
;   R=100K -> ~2MHz (See device datasheet)
;
;                MSP430F21x2
;             -----------------
;    /|\  /|\|              XIN|-
;     |    | |                 |
;     R    --|RST          XOUT|-
;     |      |                 |
;     -------|P2.5/ROSC    P1.1|-->DCOCLK/10
;
;  JL Bile
;  Texas Instruments Inc.
;  May 2008
;  Built with Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x21x2.h"
;-------------------------------------------------------------------------------
 			.text							; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #025Fh,SP         		; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupBC     bis.b   #DCOR,&BCSCTL2          ; Rosc
            bic.b   #RSEL1+RSEL0,&BCSCTL1   ; RSEL = 4
            bis.w   #OSCOFF,SR              ; XTAL not used
SetupP1     bis.b   #003h,&P1DIR            ; P1.1 = output direction
                                            ;
Mainloop    bis.b   #002h,&P1OUT            ; P1.1 = 1
            bic.b   #002h,&P1OUT            ; P1.1 = 0
            jmp     Mainloop                ; Repeat
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"				; MSP430 RESET Vector
            .short	RESET                   ;
            .end
