;******************************************************************************
;  MSP430F249 Demo - Timer_A, Toggle P1.0, CCR0 Up Mode ISR, 32kHz INCLK
;
;  Description: Toggle P1.0 using software and the TA_0 ISR. Timer_A is
;  configured for up mode, thus the timer overflows when TAR counts
;  to CCR0. In this example, CCR0 is loaded with 1000-1.
;  ACLK = TACLK = INCLK = 32768Hz, MCLK = SMCLK = default DCO ~1.1MHz
;  //* An external watch crystal on XIN XOUT is required for ACLK *//	
;
;           MSP430F249
;         ---------------
;     /|\|            XIN|-
;      | |               | 32kHz
;      --|RST        XOUT|-
;        |               |
;        |      P2.0/ACLK|---+
;        |               |   |
;        |     P2.1/INCLK|<--+
;        |               |
;        |           P1.0|-->LED (Toggle rate is ACLK/1000)
;
;  JL Bile
;  Texas Instruments Inc.
;  May 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x24x.h"
;-------------------------------------------------------------------------------
			.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #0500h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     bis.b   #BIT0,&P1DIR            ; P1.0 output
SetupP2     bis.b   #BIT0+BIT1,&P2SEL       ; Select P2.0,1 ACLK,INCLK options
            bis.b   #BIT0, &P2DIR           ; Set P2.0 as output

SetupC0     mov.w   #1000-1,&TACCR0         ; 
            mov.w   #CCIE, &TACCTL0         ; CCR0 interrupt enabled
            
SetupTA     mov.w   #TASSEL_3+MC_1,&TACTL   ; INCLK, up mode
                                            ;					
Mainloop    bis.w   #LPM3+GIE,SR            ; LPM3, enable interrupts
            nop                             ; Required only for debugger
                                            ;
;-----------------------------------------------------------------------------
TA0_ISR;    Toggle P1.0
;-----------------------------------------------------------------------------
            xor.b   #BIT0,&P1OUT            ; Toggle P1.0
            reti                            ;		
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ;  MSP430 RESET Vector
            .short  RESET                  ;
            .sect   ".int25"          ; Timer_A0 Vector
            .short  TA0_ISR                 ;
            .end