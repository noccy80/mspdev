;*******************************************************************************
;   MSP430FG479 Demo - FLL+, Runs Internal DCO at 2.45MHz
;
;   Description: This program demonstrates setting the internal DCO to run at
;   2.45MHz with auto-calibration by the FLL+.
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO = (74+1) x ACLK = 2457600Hz
;   //* An external watch crystal between XIN & XOUT is required for ACLK *//	
;
;                MSP430FG479
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
;   P.Thanigai
;   Texas Instruments Inc.
;   September 2008
;   Built with Code Composer Essentials Version: 3.0
;******************************************************************************
 .cdecls C,LIST, "msp430xG47x.h" 

;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stack pointer
SetupWDT    mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupFLL2   bis.b   #FN_2,&SCFI0            ; Set DCO  operating range
            bis.b   #XCAP18PF,&FLL_CTL0     ; Set load capacitance for xtal
            mov.b   #74,&SCFQCTL            ; (74+1) x 32768 = 2.45MHz
                                            ;
SetupPorts  bis.b   #022h,&P1DIR            ; P1.1 & P1.5 to output direction
            bis.b   #022h,&P1SEL            ; P1.1 & P1.5 to output MCLK & ACLK
            bis.b   #002h,&P1SEL2           ; P1.1 to output MCLK
                                            ;
Mainloop    jmp     Mainloop                ; Loop with CPU running
                                            ;
;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;  
            .end








