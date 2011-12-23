;******************************************************************************
;   MSP430x42x0 Demo - Basic Timer, Toggle P1.0 Inside ISR, DCO SMCLK
;
;   Description: This program toggles P1.0 by xor'ing P1.0 inside of
;   a basic timer ISR. SMCLK provides basic timer clock source.
;   The output frequency is 2.048 KHz.
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;                MSP430F4270
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |             P1.0|-->LED
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x42x0.h"
;------------------------------------------------------------------------------
			.text							; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stackpointer
Init_Sys    mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
            bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps
SetupBT     mov.b   #BTSSEL+BTIP2+BTIP1+BTIP0,&BTCTL  ; SMCLK/256
            bis.b   #BTIE,&IE2              ; Enable Basic Timer interrupt
SetupP5     bis.b   #001h,&P1DIR            ; P1.0 output
                                            ;						
Mainloop    bis.w   #CPUOFF+GIE,SR          ; Enter LPM0, enable interrupts
            nop                             ; Required only for debugger
                                            ;
;------------------------------------------------------------------------------
BT_ISR;     Toggle P1.0
;------------------------------------------------------------------------------
            xor.b   #001h,&P1OUT            ; Toggle P1.0
            reti                            ;		
                                            ;
;-----------------------------------------------------------------------------
;           Interrupt Vectors
;-----------------------------------------------------------------------------
            .sect   ".reset"                  ; RESET Vector
            .short  RESET                   ;
            .sect   ".int00"                  ; Basic Timer Vector
            .short  BT_ISR                  ;
            .end
