;******************************************************************************
;  MSP430F54x Demo - VLO sources ACLK
;
;  Description: This program demonstrates using VLO to source ACLK
;  ACLK = VLO = ~9kHz	
;
;                 MSP430F5438
;             -----------------
;         /|\|                 |
;          | |                 |
;          --|RST              |
;            |                 |
;            |                 |
;            |            P11.0|--> ACLK = ~9kHz
;            |                 |
;
;   M. Morales
;   Texas Instruments Inc.
;   April 2009
;   Built with Code Composer Essentials v3.x
;******************************************************************************

    .cdecls C,LIST,"msp430x54x.h"

;-------------------------------------------------------------------------------
            .global _main 
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x5C00,SP              ; Initialize stackpointer
            mov.w   #WDT_ADLY_250,&WDTCTL   ; WDT ~1000ms, ACLK, interval timer
            bis.w   #WDTIE,&SFRIE1          ; Enable WDT interrupt

            bis.b   #BIT0,&P1DIR;           ; P1.0 to output direction
            bis.b   #BIT0,&P11DIR           ; P11.0 to output direction
            bis.b   #BIT0,&P11SEL           ; P11.0 to output ACLK

            bis.w   #SELA_1,&UCSCTL4        ; VLO Clock Sources ACLK

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