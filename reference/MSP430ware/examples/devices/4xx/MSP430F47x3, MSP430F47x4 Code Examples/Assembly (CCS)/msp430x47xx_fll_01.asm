;*******************************************************************************
;   MSP430x47xx Demo - FLL+, Runs Internal DCO at 2.45MHz
;
;   Description: This program demonstrates setting the internal DCO to run at
;   2.45MHz with auto-calibration by the FLL+.
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   //* An external watch crystal is required between XIN & XOUT for ACLK *//	
;
;                MSP430x47xx
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |        P1.1/MCLK|--> MCLK = 2.4576MHz
;            |                 |
;            |        P1.5/ACLK|--> ACLK = 32kHz
;            |                 |
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

SetupFLL2   bis.b   #FN_2,&SCFI0            ; x2 DCO, 4MHz nominal DCO
            bis.b   #XCAP18PF,&FLL_CTL0     ; Set load capacitance for xtal
            mov.b   #74,&SCFQCTL            ; (74+1) x 32768 = 2.4576MHz
                                            ;
SetupPorts  bis.b   #BIT1+BIT5,&P1DIR       ; P1.1 & P1.5 to output direction
            bis.b   #BIT1+BIT5,&P1SEL       ; P1.1 & P1.5 to output MCLK & ACLK
                                            ;
            jmp     $                       ; Loop with CPU running
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect	".reset"            	; MSP430 RESET Vector
            .short  RESET                   ;
            .end
     







