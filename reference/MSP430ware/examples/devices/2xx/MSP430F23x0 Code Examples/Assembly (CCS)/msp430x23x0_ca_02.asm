;*******************************************************************************
;   MSP430F23x0 Demo - Comp_A+, Detect Threshold, Set P1.0 if P2.4 > 0.25*Vcc
;
;   Description: Use Comparator_A+ to detect a voltage threshold.
;   Using an external potentiometer, an unknown voltage is applied to P2.4.
;   Comparator_A+ compares the unknown voltage to an internal reference
;   voltage, in this example 0.25*VCC. If the unknown voltage is higher
;   than 0.25*VCC, P1.0 is set, if not, P1.0 is reset.
;   ACLK = n/a, MCLK = SMCLK = default DCO ~1.2MHz
;
;              MSP430F23x0
;             ---------------
;        /|\ |            XIN|-
;         |  |               |
;         ---|RST        XOUT|-
;         |  |               |
;         R<-|P2.4/CA1   P1.0|-->LED
;         |  |               |
;         ---|VSS            |
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x23x0.h"
;-------------------------------------------------------------------------------
	.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #450h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 = output
            mov.b   #CARSEL+CAREF0+CAON,&CACTL1  ; 0.25*Vcc = -Comp, on
            mov.b   #P2CA4,&CACTL2          ; P2.4/CA1 = +Comp
                                            ;
Mainloop    bit.b   #CAOUT,&CACTL2          ; Test Comparator_A+ output
            jz      OFF                     ; jmp--> if CAOUT reset
                                            ;
ON          bis.b   #001h,&P1OUT            ; P1.0 = 1
            jmp     Mainloop                ;
OFF         bic.b   #001h,&P1OUT            ; P1.0 = 0
            jmp     Mainloop                ;
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ; MSP430 RESET Vector
            .short	RESET                   ;
            .end
