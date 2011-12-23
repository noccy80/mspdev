;******************************************************************************
;  MSP430F54x Demo - WDT+ Failsafe Clock, WDT mode, DCO SMCLK
;
;  Description; Allow WDT+ in watchdog mode to timeout. Toggle P1.0 in main
;  function. LPM4 is entered, this example will demonstrate WDT+ feature
;  of preventing WDT+ clock to be disabled.
;  The WDT+ will not allow active WDT+ clock to be disabled by software, the
;  LED continues to Flash because the WDT times out normally (in 32768 DCOCLK
;  cycles) even though software has attempted to disable WDT+ clock source.
;  ACLK = n/a, MCLK = SMCLK = default DCO ~1.045MHz
;
;                MSP430F5438
;             -----------------
;         /|\|                 |
;          | |                 |
;          --|RST              |
;            |                 |
;            |             P1.0|-->LED
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
            bis.b   #BIT0,&P1DIR            ; Set P1.0 to output - SET BREAKPOINT HERE
            xor.b   #BIT0,&P1OUT            ; Toggle P1.0
            
            bis.w   #LPM4 + GIE,SR          ; Stop all clocks
            nop                             ; For debugger
            
;-------------------------------------------------------------------------------
            COMMON  INTVEC                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            ORG     RESET_VECTOR            ; POR, ext. Reset
            DW      RESET
            END
            