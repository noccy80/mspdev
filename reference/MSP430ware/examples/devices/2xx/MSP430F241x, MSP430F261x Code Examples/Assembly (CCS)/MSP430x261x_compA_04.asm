;******************************************************************************
;   MSP430x261x Demo - Comparator A, Poll input CA0, result in P1.0
;
;   Description: The voltage at pin CA0 (Vcompare) is compared with reference
;   voltage of diode ref.  LED is toggled when Vcompare crosses the ref voltage.
;
;                MSP430F241x
;                MSP430F261x
;             -----------------
;         /|\|                 |
;          | |                 |
;          --|RST           CA0|<--Vcompare
;            |                 |
;            |       P1.0/CAOUT|-->LED
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x26x.h"
;-------------------------------------------------------------------------------
	.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #0850h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT

            mov.b   #CAON+CAREF_3+CARSEL, &CACTL1  ;Enable comp, ref = Diode ref
            mov.b   #P2CA0, &CACTL2         ; Pin to CA0

SetupP1     bis.b   #BIT0,&P1DIR            ; P1.0 = output direction
            bis.b   #BIT0,&P1SEL            ; P1.0 = CAOUT
            bis.w   #LPM0,SR                ; LPM0
;-----------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ; POR, ext. Reset
            .short      RESET
            .end
