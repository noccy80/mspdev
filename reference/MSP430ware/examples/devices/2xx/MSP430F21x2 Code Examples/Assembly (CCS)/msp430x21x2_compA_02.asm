;******************************************************************************
;  MSP430x21x2 Demo - Comparator A, Poll input CA0, CA exchange, result in P5.1
;
;   Description: The Voltage at pin CA0 (Vcompare) is compared with reference
;   voltage of 0.5*Vcc. LED is toggled when Vcompare crosses the ref voltage.
;
;
;                 MSP430x21x2
;             -----------------
;         /|\|                 |
;          | |                 |
;          --|RST      P2.3/CA0|<--Vcompare
;            |                 |
;         <--|CAOUT/P2.6       |
;            |             P1.0|-->LED
;
;  JL Bile
;  Texas Instruments Inc.
;  May 2008
;  Built with Code Composer Essentials: v3 FET
;******************************************************************************
 .cdecls C,LIST,  "msp430x21x2.h"
;-------------------------------------------------------------------------------
			.text							; Program Start
;-----------------------------------------------------------------------------
RESET       mov.w   #025Fh,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT

            mov.b   #CAEX+CAON+CAREF_2+CARSEL, &CACTL1 ; Enable comp,
                                            ; ref=0.5*Vcc, CA exchange
            mov.b   #P2CA0, &CACTL2         ; Pin to CA0

SetupP1     bis.b   #BIT0,&P1DIR            ; P1.0 = output direction
SetupP2     bis.b   #BIT6+BIT3,&P2SEL       ; P2.6 = CAOUT
					


Mainloop:
            bit.b   #CAOUT, &CACTL2         ; Test result
            jz      CAOUT0                  ; jump if result = 0
                                            ; Set LED on if result = 1
            bis.b   #BIT0,&P1OUT            ; Set P1.0
            jmp     Mainloop
CAOUT0
            bic.b   #BIT0,&P1OUT            ; Clear P1.0
            jmp     Mainloop

;-----------------------------------------------------------------------------
;			Interrupt Vectors
;-----------------------------------------------------------------------------
            .sect	".reset"            ; RESET Vector
            .short	RESET                   ;
            .end
