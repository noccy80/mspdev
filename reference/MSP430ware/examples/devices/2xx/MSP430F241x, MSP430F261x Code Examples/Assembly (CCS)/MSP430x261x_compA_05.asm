;******************************************************************************
;   MSP430x261x Demo - Comparator A, Input to CA0, Interrupt triggered
;
;   Description:  Normal operation is in LPM3.  When Vcompare crosses the ref
;   voltage, an interrupt is generated, and the ISR toggles the LED.
;   //* External watch crystal on XIN XOUT is required for ACLK *//
;
;             MSP430F261x/241x
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |         P2.3/CA0|<--Vcompare
;            |                 |
;            |             P1.0|-->I/O - LED
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

            mov.b   #CAON+CAREF_2+CARSEL, &CACTL1  ; Enable comp, ref = 0.5*Vcc
            mov.b   #P2CA0, &CACTL2         ; Pin to CA0

SetupP1     bis.b   #BIT0,&P1DIR            ; P1.0 = output direction
            bic.b   #BIT0,&P1OUT
            
SetupCAIRQ  bis.b   #CAIE,&CACTL1           ; Setup interrupt for Comparator

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
            .sect	".reset"            ; POR, ext. Reset
            .short   RESET                   ;
            .sect	".int27"      ; Comparator A
            .short	COMPA_ISR
            .end
            