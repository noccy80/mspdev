;*******************************************************************************
;   MSP430F41x2 Demo - FLL+, Runs Internal DCO at 8MHz
;
;   Description: This program demonstrates setting the internal
;   DCO to run at 8MHz with auto-calibration by the FLL+.
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCOCLK = (121+1)x2xACLK = 7995392Hz
;   //* An external watch crystal between XIN & XOUT is required for ACLK *//	
;
;                MSP430F41x2
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |        P1.1/MCLK|--> MCLK = 8MHz
;            |                 |
;            |        P1.5/ACLK|--> ACLK = 32kHz
;            |                 |
;
;  P. Thanigai
;  Texas Instruments Inc.
;  January 2009
;  Built with CCE Version: 3.1   
;******************************************************************************
 .cdecls C,LIST, "msp430x41x2.h" 
 
            .global _main
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
_main
RESET       mov.w   #0400h,SP               ; Initialize stack pointer
SetupWDT    mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupFLL2   bis.b   #FN_4,&SCFI0            ; x2 DCO, 8MHz nominal DCO
            bis.b   #DCOPLUS+XCAP14PF,&FLL_CTL0 ; DCO+, configure load caps
            mov.b   #121,&SCFQCTL           ; (121+1) x 2 x 32768 = 7.99 MHz
            bis.b   #BIT1+BIT6, &P1SEL      ; P1.1= MCLK option select
                                            ; P1.6= ACLK option select
            bis.b   #BIT1+BIT6, &P1DIR      ; 
                                            ;
Mainloop    jmp     Mainloop                ; Loop with CPU running
                                            ;
;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;  
            .end







