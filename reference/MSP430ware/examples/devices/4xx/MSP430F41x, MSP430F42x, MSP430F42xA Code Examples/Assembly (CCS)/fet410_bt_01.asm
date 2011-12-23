;******************************************************************************
;   MSP-FET430P410 Demo - Basic Timer, Toggle P5.1 Inside ISR, DCO SMCLK
;
;   Description: This program toggles P5.1 by xor'ing P5.1 inside of
;   a basic timer ISR. SMCLK provides basic timer clock source.
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;                MSP430F413
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |             P5.1|-->LED
;
;   M. Buccini / S. Karthikeyan
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials  Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x41x.h"
;------------------------------------------------------------------------------
            .text                  ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stackpointer
Init_Sys    mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupBT     mov.b   #BTSSEL+BTIP2+BTIP1+BTIP0,&BTCTL  ; SMCLK/256
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
            .sect     ".reset"                  ; RESET Vector
            .short  RESET                   ;
            .sect   ".int00"                  ; Basic Timer Vector
            .short  BT_ISR                  ;
            .end
