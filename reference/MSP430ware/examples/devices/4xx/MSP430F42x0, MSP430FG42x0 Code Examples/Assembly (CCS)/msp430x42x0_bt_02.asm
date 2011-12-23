;******************************************************************************
;   MSP430x42x0 Demo - Basic Timer, Toggle P1.0 Inside ISR, 32kHz ACLK
;
;   Description: This program toggles P1.0 by xor'ing P1.0 inside of
;   a basic timer ISR. ACLK provides basic timer clock source.
;   The output frequency is 4 Hz.
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   //* An external watch crystal between XIN & XOUT is required for ACLK *//	
;
;                MSP430F4270
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
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
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps
SetupBT     mov.b   #BTDIV+BTIP1+BTIP0,&BTCTL  ; ACLK/(256*16)
            bis.b   #BTIE,&IE2              ; Enable Basic Timer interrupt
SetupP5     bis.b   #001h,&P1DIR            ; P1.0 output
                                            ;						
Mainloop    bis.w   #LPM3+GIE,SR            ; Enter LPM3, enable interrupts
            nop                             ; Required only for debugger
                                            ;
;------------------------------------------------------------------------------
BT_ISR;     Toggle P5.1
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
