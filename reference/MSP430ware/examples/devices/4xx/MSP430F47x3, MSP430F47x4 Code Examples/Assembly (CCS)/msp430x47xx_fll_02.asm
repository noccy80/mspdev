;******************************************************************************
;   MSP430x47xx Demo - FLL+, Runs Internal DCO at 16MHz
;
;  Description: This program demonstrates setting the internal DCO to run at
;  8MHz with auto-calibration by the FLL+.
;  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO = (121+1) x 4 x ACLK = 16MHz
;  For correct CPU operation @ 16MHz, the supply voltage should be set accordingly
;  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
;
;                  MSP430x47xx
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |             P1.1|--> MCLK = 16MHz
;            |                 |
;            |             P1.5|--> ACLK = 32kHz
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

SetupFLL2   mov.b   #FN_4+FLLD_4,&SCFI0     ; x4 DCO, 16MHz nominal DCO
            bis.b   #DCOPLUS+XCAP14PF,&FLL_CTL0 ; DCO+, configure load caps
            mov.b   #121,&SCFQCTL           ; (121+1) x 4 x 32768 = 16 Mhz
SetupPorts  bis.b   #BIT1+BIT5,&P1DIR       ; P1.1 & P1.5 to output direction
            bis.b   #BIT1+BIT5,&P1SEL       ; P1.1 & P1.5 to output MCLK & ACLK
                                            ;
Mainloop    jmp     Mainloop                ; Loop with CPU running
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect	".reset"            	; MSP430 RESET Vector
            .short  RESET                   ;
            .end
     