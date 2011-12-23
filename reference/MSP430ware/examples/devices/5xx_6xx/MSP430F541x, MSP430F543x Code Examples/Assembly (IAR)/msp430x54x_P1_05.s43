;******************************************************************************
;   MSP430F54x Demo - Write a byte to Port 1
;
;   Description: Writes a byte(0xFF) to Port 1 and stays in LPM4 mode
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;                MSP430F5438
;             -----------------
;         /|\|                 |
;          | |                 |
;          --|RST              |
;            |             P1.x|-->HI
;            |                 |
;            |                 |
;
;   M. Morales
;   Texas Instruments Inc.
;   September 2008
;   Built with IAR Embedded Workbench Version: 4.11B
;******************************************************************************

#include "msp430x54x.h"

;-------------------------------------------------------------------------------
            RSEG    CSTACK                  ; Define stack segment
;-------------------------------------------------------------------------------
            RSEG    CODE                    ; Assemble to Flash memory
;-------------------------------------------------------------------------------
RESET       mov.w   #SFE(CSTACK),SP         ; Initialize stackpointer
            mov.w   #WDTPW + WDTHOLD,&WDTCTL; Stop WDT    
            mov.b   #0xFF,&P1DIR            ; Set P1.x to output direction
            mov.b   #0xFF,&P1OUT            ; Set all P1 pins HI

            bis.w   #LPM4 + GIE,SR          ; Enter LPM4, enable interrupts
            nop                             ; For debugger
;-------------------------------------------------------------------------------
            COMMON  INTVEC                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            ORG     RESET_VECTOR            ; POR, ext. Reset
            DW      RESET
            END


