;******************************************************************************
;    MSP430F54x Demo - Saturation mode underflow test
;
;   Description: The example illustrates a special case showing underflow.
;   Underflow occurs when adding 2 negative numbers yields a positive result.
;   By having the saturation mode enabled, the result if rounded off to the
;   highest negative number (0x8000.0000 for 16 bit). Results can be viewed
;   in the debugger window.
;
;   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
;
;                MSP430F5438
;             -----------------
;         /|\|                 |
;          | |                 |
;          --|RST              |
;            |                 |
;            |                 |
;
;   M. Morales
;   Texas Instruments Inc.
;   September 2008
;   Built with IAR Embedded Workbench Version: 4.11B
;******************************************************************************

#include <msp430x54x.h>

;-------------------------------------------------------------------------------
            RSEG    DATA16_N                ; RAM variables start @ 0x1C00
;-------------------------------------------------------------------------------
result_lower16  DS16    1
result_upper16  DS16    1

;-------------------------------------------------------------------------------
            RSEG    CSTACK                  ; Define stack segment
;-------------------------------------------------------------------------------
            RSEG    CODE                    ; Assemble to Flash memory
;-------------------------------------------------------------------------------
RESET       mov.w   #SFE(CSTACK),SP         ; Initialize stackpointer
            mov.w   #WDTPW + WDTHOLD,&WDTCTL; Stop WDT    

            mov.w   #MPYSAT + MPYC,&MPY32CTL0
                                            ; Saturation mode enable,
            clr.w   RES3
            clr.w   RES2
            clr.w   RES1                    ; Pre-load first negative value
            mov.w   #0x8000,&RES0  

            mov.w   #0x8000,&MACS           ; Add to second negative value
            mov.w   #0x05,&OP2 

            mov.w   &RESHI,result_upper16   ; Result_upper16 = 0x8000
            mov.w   &RESLO,result_lower16   ; Result_lower15 = 0x0000

            bic.w   #MPYSAT,&MPY32CTL0      ; Clear saturation mode
            
            bis.w   #LPM4,SR                ; Enter LPM4
            nop                             ; For debugger
  
;-------------------------------------------------------------------------------
            COMMON  INTVEC                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            ORG     RESET_VECTOR            ; POR, ext. Reset
            DW      RESET
            END

