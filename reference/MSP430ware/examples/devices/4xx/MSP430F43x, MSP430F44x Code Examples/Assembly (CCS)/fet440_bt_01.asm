;******************************************************************************
;   MSP-FET430P440 Demo - Basic Timer, Toggle P5.1 Inside ISR, DCO SMCLK
;
;   Description: This program toggles P5.1 by xor'ing P5.1 inside of
;   a basic timer ISR. SMCLK provides clock source for basic timer.
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;                MSP430F449
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |             P5.1|-->LED
;
;   M. Buccini / A. Dannenberg
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST, "msp430x44x.h"
;------------------------------------------------------------------------------
            .text                  			; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stackpointer
Init_Sys    mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupBT     mov.b   #BTSSEL+BT_fCLK2_DIV256,&BTCTL ; ~244us Int.
            bis.b   #BTIE,&IE2              ; Enable Basic Timer interrupt
SetupP5     bis.b   #002h,&P5DIR            ; P5.1 output
                                            ;						
Mainloop    bis.w   #CPUOFF+GIE,SR          ; Enter LPM0, enable interrupts
            nop                             ; Required only for debugger
                                            ;
;------------------------------------------------------------------------------
BT_ISR;     Toggle P5.1
;------------------------------------------------------------------------------
            xor.b   #002h,&P5OUT            ; Toggle P5.1
            reti                            ;		
                                            ;
;-----------------------------------------------------------------------------
;           Interrupt Vectors
;-----------------------------------------------------------------------------
            .sect   ".reset"                ; RESET Vector
            .short  RESET                   ;
            .sect   ".int00"                ; Basic Timer Vector
            .short  BT_ISR                  ;
            .end
