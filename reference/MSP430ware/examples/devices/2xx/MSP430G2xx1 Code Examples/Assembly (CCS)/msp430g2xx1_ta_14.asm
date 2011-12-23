;*******************************************************************************
;   MSP430G2xx1 Demo - Timer_A, Toggle P1.1/TA0, Up/Down Mode, 32kHz ACLK
;
;   Description: Toggle P1.1 using hardware TA0 output. Timer_A is configured
;   for up/down mode with CCR0 defining period, TA0 also output on P1.1. In
;   this example, CCR0 is loaded with 5 and TA0 will toggling P1.1 at
;   TACLK/2*5. Thus the output frequency on P1.1 will be the TACLK/20.
;   No CPU or software resources required. Normal operating mode is LPM3.
;   As coded with TACLK = ACLK, P1.1 output frequency = 32768/20 = 1.6384kHz.
;   ACLK = TACLK = 32kHz, MCLK = default DCO
;   //* External watch crystal installed on XIN XOUT is required for ACLK *//	
;
;                MSP430G2xx1
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |         P1.1/TA0|--> ACLK/20
;
;   D. Dang
;   Texas Instruments Inc.
;   October 2010
;   Built with Code Composer Essentials Version: 4.2.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430g2231.h"

;------------------------------------------------------------------------------
            .text                           ; Progam Start
;------------------------------------------------------------------------------
RESET       mov.w   #0280h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     bis.b   #002h,&P1DIR            ; P1.1 output
            bis.b   #002h,&P1SEL            ; P1.1 option slect
SetupC0     mov.w   #OUTMOD_4,&CCTL0        ; CCR0 toggle mode
            mov.w   #5,&CCR0                ;
SetupTA     mov.w   #TASSEL_1+MC_3,&TACTL   ; ACLK, updown mode
                                            ;						
Mainloop    bis.w   #LPM3,SR                ; Enter LPM3
            nop                             ; Required only for debugger
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
