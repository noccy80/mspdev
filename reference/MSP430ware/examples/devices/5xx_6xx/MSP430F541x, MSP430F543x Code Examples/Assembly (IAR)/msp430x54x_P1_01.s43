;******************************************************************************
;  MSP430F54x Demo - Software Poll P1.4, Set P1.0 if P1.4 = 1
;
;  Description: Poll P1.4 in a loop, if hi P1.0 is set, if low, P1.0 reset.
;  ACLK = n/a, MCLK = SMCLK = default DCO
;
;              MSP430F5438
;            -----------------
;        /|\|              XIN|-
;         | |                 |
;         --|RST          XOUT|-
;     /|\   |                 |
;      --o--|P1.4         P1.0|-->LED
;     \|/
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
            bis.b   #BIT0,&P1DIR            ; Set P1.0 to output direction

while_loop  bit.b   #BIT4,&P1IN             ; P1.4 (In) == 1?
            jnc     turn_off_LED
turn_on_LED bis.b   #BIT0,&P1OUT            ; Yes -> set P1.0 (LED)
            jmp     while_loop 
turn_off_LED 
            bic.b   #BIT0,&P1OUT            ; No  -> reset P1.0 (LED)
            jmp     while_loop 

;-------------------------------------------------------------------------------
            COMMON  INTVEC                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            ORG     RESET_VECTOR            ; POR, ext. Reset
            DW      RESET
            END
