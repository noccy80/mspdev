;******************************************************************************
;  MSP430F66xx Demo - VLO sources ACLK
;
;  Description: This program demonstrates using VLO to source ACLK
;  ACLK = VLO = ~9kHz	
;
;                 MSP430F6638
;             -----------------
;         /|\|                 |
;          | |                 |
;          --|RST              |
;            |                 |
;            |                 |
;            |             P1.0|--> ACLK = ~9kHz
;            |                 |
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
            mov.w   #WDT_ADLY_250,&WDTCTL   ; WDT ~1000ms, ACLK, interval timer
            bis.w   #WDTIE,&SFRIE1          ; Enable WDT interrupt

            bis.b   #BIT0 + BIT1,&P1DIR;    ; P1.0, P1.1 to output direction
            bis.b   #BIT0,&P1SEL            ; P1.0 to output ACLK

            bis.w   #SELA_1,&UCSCTL4        ; VLO Clock Sources ACLK

            bis.w   #LPM3 + GIE,SR          ; Enter LPM3 w/ interrupts
            nop                             ; For debugger

;-------------------------------------------------------------------------------
WDT_ISR;    Watchdog Timer interrupt service routine
;-------------------------------------------------------------------------------
            xor.b   #BIT1,&P1OUT            ; Toggle P1.0 using exclusive-OR
            reti
;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int57"                ; ADC12 isr vector
            .short  WDT_ISR
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end
