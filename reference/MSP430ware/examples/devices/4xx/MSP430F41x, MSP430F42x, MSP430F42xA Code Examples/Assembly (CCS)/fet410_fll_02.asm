;*******************************************************************************
;   MSP-FET430P410 Demo - FLL+, Runs Internal DCO at 8MHz
;
;   Description: This program demonstrates setting the internal
;   DCO to run at 8Mhz with auto-calibration by the FLL+.
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO = (121+1) x 2 x ACLK = 7995392Hz
;   ;* An external watch crystal between XIN & XOUT is required for ACLK *//	
;
;                MSP430F413
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |        P1.1/MCLK|--> MCLK = 8Mhz
;            |                 |
;            |        P1.5/ACLK|--> ACLK = 32kHz
;            |                 |
;
;   M. Buccini / S. Karthikeyan
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x41x.h"
;------------------------------------------------------------------------------
            .text                  ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stackpointer
SetupWDT    mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupFLL2   bis.b   #FN_3,&SCFI0            ; .set DCO operating range
            bis.b   #DCOPLUS+XCAP14PF,&FLL_CTL0 ; DCO+, configure load caps
            mov.b   #121,&SCFQCTL           ; (121+1) x 2 x 32768 = 7995392Hz
SetupPorts  bis.b   #022h,&P1DIR            ; P1.1 & P1.5 to output direction
            bis.b   #022h,&P1SEL            ; P1.1 & P1.5 to output MCLK & ACLK
                                            ;
Mainloop    jmp     Mainloop                ; Loop with CPU running
                                            ;
;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect     ".reset"                  ; RESET Vector
            .short  RESET                   ;
            .end







