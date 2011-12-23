;*******************************************************************************
;   MSP430x11x1 Demo - Comp_A, Detect Threshold, .set P1.0 if P2.3 > 0.25*Vcc
;
;   Description: Use comparator_A to detect a voltage threshold. Using an
;   external potentiometer, an unknown analog voltage is applied to P2.3.
;   Comparator_A compares the unknown voltage to an internal reference
;   voltage, in this example 0.25*VCC.  If the interesting voltage is higher
;   than 0.25*Vcc, P1.0 is set, if not, P1.0 is reset.
;   ACLK = n/a, MCLK = SMCLK = default DCO ~800k
;
;                 MSP430F1121
;             -----------------
;        /|\ |              XIN|-
;         |  |                 |
;         ---|RST          XOUT|-
;         |  |                 |
;         R<-|P2.3         P1.0|--> LED
;         |  |                 |			
;         ---|VSS
;
;   M. Buccini / Z. Albus
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430x11x1.h"
;-------------------------------------------------------------------------------
            .text                           ; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 = output
SetupCA     mov.b   #008h, &CAPD            ; Disconnect port pins
            mov.b   #CARSEL+CAREF0+CAON,&CACTL1   ; 0.25Vcc = -comp, on
            mov.b   #P2CA0,&CACTL2          ; P2.3 = +comp
                                            ;	
Mainloop    bit.b   #CAOUT,&CACTL2          ; Test comparator_A output
            jz      OFF                     ; jmp--> if CAOUT reset
                                            ;
ON          bis.b   #001h,&P1OUT            ; P1.0 = 1
            jmp     Mainloop                ;
OFF         bic.b   #001h,&P1OUT            ; P1.0 = 0
            jmp     Mainloop                ;
                                            ;
;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
