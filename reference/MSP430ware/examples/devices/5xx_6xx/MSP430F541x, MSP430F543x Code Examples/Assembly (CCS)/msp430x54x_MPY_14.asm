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
;   Built with Code Composer Essentials v3.x
;******************************************************************************

    .cdecls C,LIST,"msp430x54x.h"

;-------------------------------------------------------------------------------
;-------------------------------------------------------------------------------
            .bss    result_lower16,2 
            .bss    result_upper16,2 

;-------------------------------------------------------------------------------
            .global _main 
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x5C00,SP              ; Initialize stackpointer
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
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end

