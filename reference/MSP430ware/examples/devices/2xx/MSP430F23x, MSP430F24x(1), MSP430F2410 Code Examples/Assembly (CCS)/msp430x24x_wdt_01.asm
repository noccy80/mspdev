;*******************************************************************************
;   MSP430x24x Demo - WDT, Toggle P1.0, Interval Overflow ISR, DCO SMCLK
;
;   Description: Toggle P1.0 using software timed by the WDT ISR. Toggle rate
;   is approximately 32ms based on default DCO/SMCLK clock source
;   used in this example for the WDT.
;   ACLK = n/a, MCLK = SMCLK = default DCO ~1.045MHz
;
;                MSP430F249
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |             P1.0|-->LED
;
;  JL Bile
;  Texas Instruments Inc.
;  May 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x24x.h"
;-------------------------------------------------------------------------------
			.text							;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #0500h,SP         		; Initialize stackpointer
SetupWDT    mov.w   #WDT_MDLY_32,&WDTCTL    ; WDT ~32ms interval timer
            bis.b   #WDTIE,&IE1             ; Enable WDT interrupt
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 output
                                            ;
Mainloop    bis.w   #CPUOFF+GIE,SR          ; CPU off, enable interrupts
            nop                             ; Required only for debugger
                                            ;
;-------------------------------------------------------------------------------
WDT_ISR;    Toggle P1.0
;-------------------------------------------------------------------------------
            xor.b   #001h,&P1OUT            ; Toggle P1.0
            reti                            ;
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect    ".reset"            ; MSP430 RESET Vector
            .short   RESET                   ;
            .sect  ".int26"              ; WDT Vector
            .short   WDT_ISR                 ;
            .end
