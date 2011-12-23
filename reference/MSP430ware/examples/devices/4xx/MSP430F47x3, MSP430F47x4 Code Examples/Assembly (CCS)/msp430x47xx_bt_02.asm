;******************************************************************************
;   MSP430x47xx Demo - Basic Timer, Toggle P5.1 Inside ISR, DCO SMCLK
;
;   Description: This program toggles P5.1 by xor'ing P5.1 inside of
;   a basic timer ISR. SMCLK provides basic timer clock source.
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;                MSP430x47xx
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |             P5.1|-->LED
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x47x4.h"
;-------------------------------------------------------------------------------
			.text							; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #900h,SP         ; Initialize stackpointer
Init_Sys    mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupBT     mov.b   #BTSSEL+BT_fCLK2_DIV256,&BTCTL   ; SMCLK/256
            bis.b   #BTIE,&IE2              ; Enable Basic Timer interrupt
SetupP5     bis.b   #BIT1,&P5DIR            ; P5.1 output
                                            ;						
Mainloop    bis.w   #CPUOFF+GIE,SR          ; Enter LPM0, enable interrupts
            nop                             ; Required only for debugger
                                            ;
;------------------------------------------------------------------------------
Basic_Timer_ISR ;     Toggle P5.1
;------------------------------------------------------------------------------
            xor.b   #BIT1,&P5OUT            ; Toggle P5.1
            reti                            ;		
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect	".reset"            ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int00"	       ; MSP430 Basic Timer Interrupt Vector
            .short  Basic_Timer_ISR         
            .end
            