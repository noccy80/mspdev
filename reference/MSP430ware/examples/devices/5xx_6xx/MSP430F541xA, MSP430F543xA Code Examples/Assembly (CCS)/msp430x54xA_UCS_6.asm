;******************************************************************************
;  MSP430F54xA Demo - XT1 sources ACLK Toggles P1.0
;
;  Description: This program demonstrates using XT1 to source ACLK
;  ACLK = LFXT1 = 32,768Hz	
;  ;* An external watch crystal between XIN & XOUT is required for ACLK *;	
;
;               MSP430F5438
;             -----------------
;        /|\ |              XIN|-
;         |  |                 | 32kHz
;         ---|RST          XOUT|-
;            |                 |
;            |            P11.0|--> ACLK = ~32kHz
;            |                 |
;            |             P1.0|-->LED
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
            mov.w   #WDT_ADLY_1000,&WDTCTL  ; WDT ~1000ms, ACLK, interval timer
            bis.w   #WDTIE,&SFRIE1          ; Enable WDT interrupt
            bis.w   #SELA_0,&UCSCTL4        ; LFXT1 Sources ACLK

            bis.b   #BIT0,&P1DIR;           ; P1.0 to output direction
            bis.b   #BIT0,&P11DIR           ; P11.0 to output direction
            bis.b   #BIT0,&P11SEL           ; P11.0 to output ACLK

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

            bis.w   #LPM3 + GIE,SR          ; Enter LPM3 w/ interrupts
            nop                             ; For debugger

;-------------------------------------------------------------------------------
WDT_ISR;    Watchdog Timer interrupt service routine
;-------------------------------------------------------------------------------
            xor.b   #0x01,&P1OUT            ; Toggle P1.0 using exclusive-OR
            reti
;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int58"                  ; WDT Vector
            .short  WDT_ISR
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end
            
            