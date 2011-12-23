;******************************************************************************
;   MSP-FET430P120 Demo - Timer_A, Toggle P1.0, CCR0 Up Mode ISR, 32kHz ACLK
;
;   Description: Toggle P1.0 using software and the TA_0 ISR. Timer_A is
;   configured for up mode, thus the the timer overflows when TAR counts
;   to CCR0. In this example CCR0 is loaded with 1000-1.
;   ACLK = TACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO ~800kHz
;   //* An external watch crystal on XIN XOUT is required for ACLK *//	
;
;                MSP430F123(2)
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |             P1.0|-->LED
;
;   M. Buccini / M. Raju
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x12x2.h"
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 output
SetupC0     mov.w   #CCIE,&CCTL0            ; CCR0 interrupt enabled
            mov.w   #1000-1,&CCR0           ; CCR0 counts to 1000
SetupTA     mov.w   #TASSEL_1+MC_1,&TACTL   ; ACLK, upmode
                                            ;													
Mainloop    bis.w   #LPM3+GIE,SR            ; Enter LPM3, interrupts enabled
            nop                             ; Required for debugger
                                            ;
;------------------------------------------------------------------------------
TA0_ISR;    Toggle P1.0
;------------------------------------------------------------------------------
            xor.b   #001h,&P1OUT            ; Toggle P1.0
            reti                            ;		
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int09"                ; Timer_A0 Vector
            .short  TA0_ISR                 ;
            .end
