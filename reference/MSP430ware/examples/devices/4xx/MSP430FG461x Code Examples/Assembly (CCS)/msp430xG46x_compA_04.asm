;******************************************************************************
;   MSP430xG46x Demo - Comparator A, Poll input CA0, result in P5.1
;
;   Description: The voltage at pin CA0 (Vcompare) is compared with reference
;   voltage of diode ref.  LED is toggled when Vcompare crosses the ref voltage.
;
;
;                 MSP430xG461x
;             -----------------
;         /|\|                 |
;          | |                 |
;          --|RST           CA0|<--Vcompare
;            |                 |
;            |                 |
;            |             P5.1|-->LED
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430xG46x.h"
;-------------------------------------------------------------------------------
			.text	;Program Start
;-----------------------------------------------------------------------------
RESET       mov.w   #900,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps

            mov.b   #CAON+CAREF_3+CARSEL, &CACTL1  ;Enable comp, ref = Diode ref
            mov.b   #P2CA0, &CACTL2         ; Pin to CA0

SetupP5     bis.b   #BIT1,&P5DIR            ; P5.1 = output direction
SetupP2     bis.b   #BIT6,&P2SEL            ; P2.6 = CAOUT

mainloop:
            bit.b   #1, &CACTL2             ; Test result
            jz      CAOUT0                  ; jump if result = 0
                                            ; Set LED on if result =1
            bis.b   #BIT1,&P5OUT            ; Set P5.1
            jmp     mainloop
CAOUT0
            bic.b   #BIT1,&P5OUT            ; Clear P5.1
            jmp     mainloop

;-----------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect 	".reset"	           ; MSP430 RESET Vector
            .short   RESET                   ;
            .end
            