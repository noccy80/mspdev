;*******************************************************************************
;  MSP430F54x Demo - RTC in Counter Mode toggles P1.0 every 1s
;
;  This program demonstrates RTC in counter mode configured to source from ACLK
;  to toggle P1.0 LED every 1s.
;
;                MSP430F5438
;             -----------------
;        /|\ |                 |
;         |  |                 |
;         ---|RST              |
;            |                 |
;            |             P1.0|-->LED
;
;   M. Morales
;   Texas Instruments Inc.
;   April 2009
;   Built with CCE Version: 3.2.2 and Code Composer Essentials v3.x
;*******************************************************************************

    .cdecls C,LIST,"msp430x54x.h"

;-------------------------------------------------------------------------------
            .global _main 
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT

            bic.b   #0x01,&P1OUT            ; Clear P1.0
            bis.b   #0x01,&P1DIR            ; P1.0 Output

            ; Setup RTC Timer
            mov.w   #RTCTEVIE + RTCSSEL_2 + RTCTEV_0,&RTCCTL01
                                            ; Counter Mode, RTC1PS, 8-bit ovf
                                            ; overflow interrupt enable
            mov.w   #RT0PSDIV_2,&RTCPS0CTL  ; ACLK, /8, start timer
            mov.w   #RT1SSEL_2 + RT1PSDIV_3,&RTCPS1CTL
                                            ; out from RT0PS, /16, start timer

            bis.b   #LPM3 + GIE,SR          ; Enter LPM3 w/ interrupt

;-------------------------------------------------------------------------------
RTC_ISR ;   RTC Interrupt Handler
;-------------------------------------------------------------------------------
            add     &RTCIV,PC
            reti                            ; No interrupts
            reti                            ; RTCRDYIFG
            jmp     RTCEVIFG_HND            ; RTCEVIFG
            reti                            ; RTCAIFG
            reti                            ; RT0PSIFG
            reti                            ; RT1PSIFG
            reti                            ; Reserved
            reti                            ; Reserved
            reti                            ; Reserved
            reti
RTCEVIFG_HND
            xor.b   #BIT0,&P1OUT            ; Toggle P1.0
            reti
;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int41"                  ; RTC Vector
            .short  RTC_ISR
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end