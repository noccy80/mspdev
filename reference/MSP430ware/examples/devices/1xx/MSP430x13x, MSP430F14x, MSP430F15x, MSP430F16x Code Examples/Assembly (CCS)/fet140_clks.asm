;******************************************************************************
;   MSP-FET430P140 Demo - Basic Clock, Output Buffered SMCLK, ACLK and MCLK
;
;   Description: Output buffered MCLK, SMCLK and ACLK.
;   ACLK = LFXT1 = 32768Hz, MCLK = DCO Max, SMCLK = XT2
;   //* XTAL's REQUIRED - NOT INSTALLED ON FET *//
;   //* Min Vcc required varies with MCLK frequency - refer to datasheet *//	
;
;                 MSP430F149
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |            XT2IN|-
;            |                 | XTAL (455k - 8MHz)
;            |RST        XT2OUT|-
;            |                 |
;            |             P5.4|-->MCLK = DCO Max
;            |             P5.5|-->SMCLK = XT2
;            |             P5.6|-->ACLK = 32kHz
;
;
;   M. Buccini / G. Morton
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x14x.h"
;-----------------------------------------------------------------------------
            .text                           ; Program Start
;-----------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupBC     mov.b   #DCO0 + DCO1 + DCO2,DCOCTL ; Max DCO
            mov.b   #RSEL0 + RSEL1 + RSEL2,&BCSCTL1 ; XT2on, max RSEL
            bis.b   #SELS,&BCSCTL2          ; SMCLK = XT2
SetupP5     bis.b   #070h,&P5DIR            ; P5.6,5,4 output
            bis.b   #070h,&P5SEL            ; P5.6,5,4 option
                                            ;													
Mainloop    jmp      Mainloop               ;
                                            ;
;-----------------------------------------------------------------------------
;           Interrupt Vectors Used MSP430x13x/14x/15x/16x
;-----------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
