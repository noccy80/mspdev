;******************************************************************************
;   MSP430F54x Demo - Saturation mode overflow test
;
;   Description: The example illustrates a special case showing overflow.
;   The addition result of 2 positive numbers may exceed the highest positive
;   number (0x7FFF FFFF for 32 bit result) due to overflow indicating a negative
;   result. By having the saturation mode enabled, this result can be truncated
;   off to this highest positive number. Results with and without saturation
;   mode are shown.
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

            mov.w   #MPYSAT,&MPY32CTL0      ; Enable saturation mode

            clr.w   RES3 
            clr.w   RES2

  ;------32-bit Result of a multiply operation (not shown) in RES0 and RES1------
            mov.w   #0x7FFF,&RES1           ; Pre-load result registers
            mov.w   #0xFFFD,&RES0

            mov.w   #0x05,&MACS             ; Add 5 to previous result
            mov.w   #0x01,&OP2 
            
            mov.w   &RESHI,result_upper16   ; Result_upper15 = 0x7FFF
            mov.w   &RESLO,result_lower16   ; Result_lower15 = 0xFFFF

            bic.w   #MPYSAT,&MPY32CTL0      ; Clear saturation mode
            
            bis.w   #LPM4,SR                ; Enter LPM4
            nop                             ; For debugger
  
;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end