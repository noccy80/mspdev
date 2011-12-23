;*******************************************************************************
;   MSP430x42x0 Demo - FLL+, Runs Internal DCO at 2.45MHz
;
;   Description: This program demonstrates setting the internal DCO to run at
;   2.45MHz with auto-calibration by the FLL+ circuitry.
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO = (74+1) x ACLK = 2457600Hz
;   //* An external watch crystal between XIN & XOUT is required for ACLK *//	
;
;                MSP430F4270
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |        P1.1/MCLK|--> MCLK = 2.45MHz
;            |                 |
;            |        P1.5/ACLK|--> ACLK = 32kHz
;            |                 |
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x42x0.h"
;------------------------------------------------------------------------------
			.text							; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stackpointer
SetupWDT    mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupFLL2   bis.b   #FN_2,&SCFI0            ; Set DCO operating range
            bis.b   #XCAP14PF,&FLL_CTL0     ; Set load capacitance for xtal
            mov.b   #74,&SCFQCTL            ; (74+1) x 32768 = 2457600Hz
                                            ;
SetupPorts  bis.b   #022h,&P1DIR            ; P1.1 & P1.5 to output direction
            bis.b   #022h,&P1SEL            ; P1.1 & P1.5 to output MCLK & ACLK
                                            ;
Mainloop    jmp     Mainloop                ; Loop with CPU running
                                            ;
;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect    ".reset"                  ; RESET Vector
            .short   RESET                   ;
            .end






