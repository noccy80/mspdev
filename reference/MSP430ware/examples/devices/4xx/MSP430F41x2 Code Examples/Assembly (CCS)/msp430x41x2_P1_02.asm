;******************************************************************************
;   MSP430x41x2 Demo - Software Port Interrupt on P1.4 from LPM4
;
;   Description: A hi/low transition on P1.4 will trigger P1_ISR which,
;   toggles P5.1. Normal mode is LPM4 ~ 0.1uA. LPM4 current can be measured
;   with the LED removed, all unused P1.x/P2.x configured as output or inputs
;   pulled high or low, and ensure the interrupt input does not float.
;   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
;
;                MSP430F41x2
;             -----------------
;         /|\|                 |
;          | |                 |
;          --|RST              |
;      /|\   |                 |
;       --o--|P1.4         P5.1|-->LED
;      \|/
;
;  P. Thanigai
;  Texas Instruments Inc.
;  January 2009
;  Built with CCE Version: 3.1
;******************************************************************************
 .cdecls C,LIST, "msp430x41x2.h" 
 
            .global _main
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
_main
RESET       mov.w   #0400h,SP               ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP5     bis.b   #BIT1,&P5DIR            ; P5.1 output
            bis.b   #010h,&P1IE             ; P1.4 Interrupt enabled
            bis.b   #010h,&P1IES            ; P1.4 hi/low edge
            bic.b   #010h,&P1IFG            ; P1.4 IFG Cleared
                                            ;
Mainloop    bis.w   #LPM4+GIE,SR            ; LPM4, enable interrupts
            nop                             ; Required only for debugger
                                            ;
;-----------------------------------------------------------------------------
P1_ISR     ; Toggle P5.1 Output
;-----------------------------------------------------------------------------
            xor.b   #BIT1,&P5OUT            ; P5.1 = toggle
            bic.b   #010h,&P1IFG            ; P1.4 IFG Cleared
            reti                            ; Return from ISR
                                            ;
;-----------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"	           ; POR, ext. Reset, Watchdog
            .short  RESET
            .sect   ".int04"               ; P1.x Vector
            .short   P1_ISR                ;
            .end
