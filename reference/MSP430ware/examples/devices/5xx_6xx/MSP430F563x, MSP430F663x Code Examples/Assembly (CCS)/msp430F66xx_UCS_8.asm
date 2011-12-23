;******************************************************************************
;  MSP430F66xx Demo - XT2 sources MCLK & SMCLK, ACLK = REF0
;
;  Description: This program demonstrates using XT2 to source MCLK. XT1 is not
;  connected in this case.
;
;  By default, LFXT1 is requested by the following modules:
;     - FLL
;     - ACLK
;  If LFXT1 is NOT used and if the user does not change the source modules,
;  it causes the XT1xxOFIFG flag to be set because it is constantly looking
;  for LFXT1. OFIFG, global oscillator fault flag, will always be set if LFXT1
;  is set. Hence, it is important to ensure LFXT1 is no longer being sourced
;  if LFXT1 is NOT used.
;  MCLK = XT2
;
;  NOTE: if the SMCLK/HF XTAL frequency exceeds 8MHz, VCore must be set
;  accordingly to support the system speed. Refer to MSP430x5xx Family User's Guide
;  Section 2.2 for more information.

;               MSP430F6638
;             -----------------
;        /|\ |                 |
;         |  |                 |
;         ---|RST              |
;            |            XT2IN|-
;            |                 | HF XTAL (455kHz - 16MHz)
;            |           XT2OUT|-
;            |                 |
;            |            P3.4 |--> MCLK = SMCLK = XT2
;            |                 |
;
;
;   Priya Thanigai
;   Texas Instruments Inc.
;   August 2011
;   Built with CCS V5
;******************************************************************************
            .cdecls C,LIST,"msp430f6638.h"

;-------------------------------------------------------------------------------
            .global _main
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x63FE,SP              ; Initialize stackpointer
            mov.w   #WDTPW + WDTHOLD,&WDTCTL; Stop WDT
            
            bis.b   #BIT0,&P1DIR            ; P1.0 output
            bis.b   #BIT0,&P1SEL            ; ACLK set out to pins
            bis.b   #BIT4,&P3DIR            ; P3.4 output
            bis.b   #BIT4,&P3SEL            ; SMCLK set out to pins
            
           
Clock_Init  bis.b   #BIT2 + BIT3,&P7SEL     ; Port select XT2
            bic.w   #XT2OFF,&UCSCTL6        ; Clear XT1OFF & XT2OFF bit
            
            bis.w   #SELREF_2,&UCSCTL3      ; FLLref = REFO
                                            ; Since LFXT1 is not used,
                                            ; sourcing FLL with LFXT1 can cause
                                            ; XT1OFFG flag to set
            bis.w   #SELA_2,&UCSCTL4        ; ACLK=REFO,SMCLK=DCO,MCLK=DCO

            ; Loop until XT1,XT2 & DCO stabilizes
do_while    bic.w   #XT2OFFG + XT1LFOFFG + DCOFFG,&UCSCTL7
                                            ; Clear XT2,XT1,DCO fault flags
            bic.w   #OFIFG,&SFRIFG1         ; Clear fault flags
            bit.w   #OFIFG,&SFRIFG1         ; Test oscillator fault flag
            jc      do_while

            bic.w   #XT2DRIVE0,&UCSCTL6     ; Decrease XT2 Drive according to
                                            ; expected frequency
            bis.w  #SELS_5 + SELM_5,&UCSCTL4; SMCLK=MCLK=XT2

while_loop  jmp     while_loop

;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end
            
            
