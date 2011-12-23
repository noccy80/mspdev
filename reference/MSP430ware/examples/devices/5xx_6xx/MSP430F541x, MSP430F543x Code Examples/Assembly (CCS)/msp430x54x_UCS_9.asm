;*****************************************************************************
;  MSP430F54x Demo - LFXT1 HF Xtal + Internal DCO
;
;  Description:  This program demonstrates using an external high speed crystal
;  or resonator to supply ACLK and MCLK for the CPU. SMLCK is supplied by the
;  internal DCO.  The high speed crystal or resonator connects between pins
;  Xin and Xout. The DCO clock is generated internally and calibrated from REFO
;  ACLK is brought out on pin P11.0, SMCLK is brought out on P11.2, and MCLK is
;  brought out on pin P11.1.
;  ACLK = LFXT1 = HF XTAL, MCLK = HF XTAL, SMCLK = 32 x ACLK = 1048576Hz
;
;  NOTE: External matching capacitors must be added for the high
;       speed crystal or resonator as required.
;
;                MSP430F5438
;             -----------------
;        /|\ |              XIN|-
;         |  |                 | HF XTAL or Resonator (add capacitors)
;         ---|RST          XOUT|-
;            |                 |
;            |            P11.0|--> ACLK = High Freq Xtal or Resonator Out
;            |                 |
;            |            P11.2|--> SMCLK = Default DCO
;            |                 |
;            |            P11.1|--> MCLK = High Freq Xtal or Resonator Out
;            |                 |
;
;   M. Morales
;   Texas Instruments Inc.
;   February 2009
;   Built with Code Composer Essentials v3.x
;******************************************************************************

    .cdecls C,LIST,"msp430x54x.h"

count    .equ    R4 
;-------------------------------------------------------------------------------
            .global _main 
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x5C00,SP              ; Initialize stackpointer
            mov.w   #WDTPW + WDTHOLD,&WDTCTL; Stop WDT

            bis.b   #0x07,&P11DIR           ; P11.2,1,0 to output direction
            bis.b   #0x07,&P11SEL           ; P11.2 to output SMCLK, P11.1
                                            ; to output MCLK and P11.0 to
                                            ; output ACLK
            bis.b   #0x03,&P7SEL            ; Port select XT1
            bis.w   #SELREF_2,&UCSCTL3      ; FLL Ref = REFO
            bic.w   #XT1OFF,&UCSCTL6        ; Set XT1 On
            bis.w   #XT1DRIVE_3+XTS,&UCSCTL6; Max drive strength, adjust
                                            ; according to crystal frequency.
                                            ; LFXT1 HF mode

            ; Loop until XT1,XT2 & DCO stabilizes
do_while    bic.w   #XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG,&UCSCTL7
                                            ; Clear XT2,XT1,DCO fault flags
            bic.w   #OFIFG,&SFRIFG1         ; Clear fault flags
            bit.w   #OFIFG,&SFRIFG1         ; Test oscillator fault flag
            jc      do_while

            mov.w   #SELA_0+SELS_4+SELM_0,&UCSCTL4
                                            ; Select ACLK = LFXT1
                                            ;       SMCLK = DCO
                                            ;        MCLK = LFXT1
mainloop    jmp      mainloop               ; Loop in place

;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end