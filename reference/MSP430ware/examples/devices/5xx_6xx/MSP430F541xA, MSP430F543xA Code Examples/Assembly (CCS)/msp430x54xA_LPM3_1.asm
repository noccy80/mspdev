;******************************************************************************
;   MSP430x54x Demo - Enters LPM3 (ACLK = LFXT1)
;
;   Description: Configure ACLK = LFXT1 and enters LPM3. Measure current.
;   ACLK = LFXT1 = 32kHz, MCLK = SMCLK = default DCO
;   Note: SVS(H,L) & SVM(H,L) not disabled
;
;                 MSP430x5438A
;             -----------------
;        /|\ |              XIN|-
;         |  |                 | 32kHz
;         ---|RST          XOUT|-
;            |                 |
;
;   D. Dang
;   Texas Instruments Inc.
;   December 2009
;   Built with CCS Version: 4.0.2 
;******************************************************************************
    .cdecls C,LIST,"msp430x54xA.h"

;-------------------------------------------------------------------------------
            .global _main 
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x5C00,SP              ; Initialize stackpointer
            mov.w   #WDTPW + WDTHOLD,&WDTCTL; Stop WDT

            bis.b   #0x03,&P7SEL            ; Select XT1
            bic.w   #XT1OFF,&UCSCTL6        ; XT1 On
            bis.w   #XCAP_3,&UCSCTL6        ; Internal load cap

            ; Loop until XT1,XT2 & DCO stabilizes
do_while    bic.w   #XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG,&UCSCTL7
                                            ; Clear XT2,XT1,DCO fault flags
            bic.w   #OFIFG,&SFRIFG1         ; Clear fault flags
            bit.w   #OFIFG,&SFRIFG1         ; Test oscillator fault flag
            jc      do_while

            bic.w   #XT1DRIVE_3,&UCSCTL6    ; XT1 stable, reduce drive strength

            mov.b   #0xFF,&P1DIR
            mov.b   #0xFF,&P2DIR
            mov.b   #0xFF,&P3DIR
            mov.b   #0xFF,&P4DIR
            mov.b   #0xFF,&P5DIR
            mov.b   #0xFF,&P6DIR
            mov.b   #0xFF,&P7DIR
            mov.b   #0xFF,&P8DIR
            mov.b   #0xFF,&P9DIR
            mov.b   #0xFF,&P10DIR
            mov.b   #0xFF,&P11DIR
            mov.w   #0xFF,&PJDIR
            clr.b   P1OUT
            clr.b   P2OUT
            clr.b   P3OUT
            clr.b   P4OUT
            clr.b   P5OUT
            clr.b   P6OUT
            clr.b   P7OUT
            clr.b   P8OUT
            clr.b   P9OUT
            clr.b   P10OUT
            clr.b   P11OUT
            clr.w   PJOUT

            bis.w   #LPM3,SR                ; Enter LPM3
            nop                             ; For debugger

;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end
