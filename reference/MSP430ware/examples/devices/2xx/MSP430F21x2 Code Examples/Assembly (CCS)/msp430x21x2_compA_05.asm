;******************************************************************************
;    MSP430x21x2 Demo - Comparator A, Poll input CA0, interrupt triggered
;
;   Description:  Normal operation is in LPM3.  When Vcompare crosses the ref
;   voltage, an interrupt is generated, and the ISR toggles the LED.
;
;
;                  MSP430x21x2
;             -----------------
;         /|\|                 |
;          | |                 |
;          --|RST           CA0|<--Vcompare
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
			.text							;Program Start
;-----------------------------------------------------------------------------
RESET       mov.w   #025Fh,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT

            mov.b   #CAON+CAREF_2+CARSEL, &CACTL1  ; Enable comp, ref = 0.5*Vcc
            mov.b   #P2CA0, &CACTL2         ; Pin to CA0
            bis.b   #CAPD6,&CAPD            ; Port pin buffer disable

SetupP1     bis.b   #BIT0,&P1DIR            ; P1.0 = output direction
SetupP2     bis.b   #BIT6,&P2SEL            ; P2.6 = CAOUT

SetupCAIRQ  bis.b   #CAIE,&CACTL1           ; Setup interrupt for Comparator
            bis.w   #GIE,SR                 ; Enter LPM3, interrupts enabled

mainloop    bis.w   #LPM3+GIE,SR            ; Enter LPM3, enable interrupts

;------------------------------------------------------------------------------
COMPA_ISR   ;     COMPARATOR A ISR - toggles LED
;------------------------------------------------------------------------------
            xor.b   #CAIES,&CACTL1          ; Toggles interrupt edge
            xor.b   #BIT0,&P1OUT            ; Toggle P1.0
            reti                            ;		

;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect	".reset"            ; MSP430 RESET Vector
            .short	RESET               ; 
            .sect	".int11"      		; Comparator A
            .short	COMPA_ISR
            .end
