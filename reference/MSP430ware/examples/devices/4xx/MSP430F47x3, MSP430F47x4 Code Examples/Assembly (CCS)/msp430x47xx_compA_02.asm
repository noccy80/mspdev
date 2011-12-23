;******************************************************************************
;  MSP430x47xx Demo - Comparator A, Poll input CA0, CA exchange, result in P5.1
;
;   Description: The Voltage at pin CA0 (Vcompare) is compared with reference
;   voltage of 0.5*Vcc. LED is toggled when Vcompare crosses the ref voltage.
;
;
;                 MSP430x47xx
;             -----------------
;         /|\|                 |
;          | |                 |
;          --|RST      P1.6/CA0|<--Vcompare
;            |                 |
;         <--|CAOUT/P2.6       |
;            |             P5.1|-->LED
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x47x4.h"
;-------------------------------------------------------------------------------
			.text							; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #900h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps

            mov.b   #CAEX+CAON+CAREF_2+CARSEL, &CACTL1 ; Enable comp,
                                            ; ref=0.5*Vcc, CA exchange
            mov.b   #P2CA0, &CACTL2         ; Pin to CA0
            bis.b   #CAPD6,&CAPD            ; Port pin buffer disable
            
SetupP5     bis.b   #BIT1,&P5DIR            ; P5.1 = output direction
SetupP2     bis.b   #BIT6,&P2SEL            ; P2.6 = CAOUT

Mainloop:
            bit.b   #CAOUT, &CACTL2         ; Test result
            jz      CAOUT0                  ; jump if result = 0
                                            ; Set LED on if result =1
            bis.b   #BIT1,&P5OUT            ; Set P5.1
            jmp     Mainloop
CAOUT0
            bic.b   #BIT1,&P5OUT            ; Clear P5.1
            jmp     Mainloop

;-----------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect	".reset"            	; RESET Vector
            .short  RESET                   ;
            .end

