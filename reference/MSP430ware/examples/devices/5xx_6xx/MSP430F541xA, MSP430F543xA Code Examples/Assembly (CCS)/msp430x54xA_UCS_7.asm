;*****************************************************************************
;  MSP430F54xA Demo - FLL+, Output 32kHz Xtal + HF Xtal + Internal DCO
;
;  Description:  This program demonstrates using an external 32kHz crystal to
;  supply ACLK, and using a high speed crystal or resonator to supply SMCLK.
;  MLCK for the CPU is supplied by the internal DCO.  The 32kHz crystal
;  connects between pins Xin and Xout. The high frequency crystal or
;  resonator connects between pins XT2IN and XT2OUT.  The DCO clock is
;  generated internally and calibrated from the 32kHz crystal.  ACLK is
;  brought out on pin P11.0, SMCLK is brought out on P11.2, and MCLK is
;  brought out on pin P11.1.
;  ACLK = LFXT1 = 32768Hz, MCLK = default DCO = 32 x ACLK = 1048576Hz
;  SMCLK = HF XTAL
;  PMMCOREV = 2 to support up to 20MHz clock
;
;  NOTE: if the SMCLK/HF XTAL frequency exceeds 8MHz, VCore must be set
;  accordingly to support the system speed. Refer to MSP430x5xx Family User's Guide
;  Section 2.2 for more information.

;  ;* An external watch crystal between XIN & XOUT is required for ACLK *;	
;
;  NOTE: External matching capacitors must be added for the high
;       speed crystal or resonator as required.

;  
;                MSP430F5438A
;             -----------------
;        /|\ |              XIN|-
;         |  |                 | 32kHz
;         ---|RST          XOUT|-
;            |                 |
;            |                 |
;            |            XT2IN|-
;            |                 | HF XTAL or Resonator (add capacitors)
;            |           XT2OUT|-
;            |                 |
;            |            P11.0|--> ACLK = 32kHz Crystal Out
;            |                 |
;            |            P11.2|--> SMCLK = High Freq Xtal or Resonator Out
;            |                 |
;            |            P11.1|--> MCLK = Default DCO Frequency
;            |                 |
;            |                 |
;
;  	Note: 
;      	In order to run the system at up to 20MHz, VCore must be set at 1.8V 
;		or higher. This is done by invoking function SetVCore(), which requires 
;		2 files, hal_pmm.asm and hal_pmm.h, to be included in the project.
;      	hal_pmm.asm and hal_pmm.h are located in the same folder as the code 
;		example. 
;
;   D. Dang
;   Texas Instruments Inc.
;   December 2009
;   Built with CCS Version: 4.0.2 
;******************************************************************************

    .cdecls C,LIST,"msp430x54xA.h"
    .cdecls C,LIST,"hal_pmm.h"		
count    .equ    R4 

;-------------------------------------------------------------------------------
            .global _main 
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x5C00,SP              ; Initialize stackpointer
            mov.w   #WDTPW + WDTHOLD,&WDTCTL; Stop WDT
			mov.w	#PMMCOREV_2, R12		; Set VCore to 1.8MHz 
			calla	#SetVCore				; To support up to 20MHz clock
            mov.b   #BIT0 + BIT1 + BIT2,&P11DIR
                                            ; P11.0,1,2 to output direction
            mov.b   #BIT0 + BIT1 + BIT2,&P11SEL
                                            ; P11.2 > SMCLK, P11.1 > MCLK
                                            ; P11.0 > ACLK
            bis.b   #0x0C,&P5SEL            ; Port select XT2
            bis.b   #0x03,&P7SEL            ; Port select XT1
            bic.w   #XT1OFF+XT2OFF,&UCSCTL6 ; Clear XT1OFF & XT2OFF bit
            bis.w   #XCAP_3,&UCSCTL6        ; Internal load cap

            ; Loop until XT1,XT2 & DCO stabilizes
do_while    bic.w   #XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG,&UCSCTL7
                                            ; Clear XT2,XT1,DCO fault flags
            bic.w   #OFIFG,&SFRIFG1         ; Clear fault flags
            bit.w   #OFIFG,&SFRIFG1         ; Test oscillator fault flag
            jc      do_while

            bic.w   #XT2DRIVE0,&UCSCTL6     ; Decrease XT2 Drive according to
                                            ; expected frequency
            bis.w   #SELA_0 + SELS_5,&UCSCTL4
                                            ; Select SMCLK, ACLK, DCO source
while_loop  nop
            jmp     while_loop

;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end
