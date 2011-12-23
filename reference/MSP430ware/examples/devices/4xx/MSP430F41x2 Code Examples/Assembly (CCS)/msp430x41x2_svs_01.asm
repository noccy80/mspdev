;******************************************************************************
;   MSP430x41x2 Demo - SVS, POR @ 2.5V Vcc
;
;   Description: The SVS POR feature is used to disable normal operation that
;   toggles P5.1 by xor'ing P5.1 inside of a software loop.
;   In the example, when VCC is above 2.5V, the MSP430 toggles P5.1. When VCC is
;   below 2.5V, the SVS resets the MSP430, and no toggle is seen.
;   ACLK= n/a, MCLK= SMCLK= default DCO ~ 1.045MHz
;
;                MSP430F41x2
;              -----------------
;          /|\|              XIN|-
;           | |                 |
;           --|RST          XOUT|-
;             |                 |
;             |             P5.1|-->LED
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
SetupP1     bis.b   #002h,&P5DIR            ; P5.1  output
            mov.b   #060h+PORON,&SVSCTL     ; SVS POR enabled @ 2.5V
                                            ;
Mainloop    mov.w   #050000,R15             ; Delay to R15
L1          dec.w   R15                     ; Decrement R15
            jnz     L1                      ; Delay over?
            xor.b   #002h,&P5OUT            ; Toggle P5.1
            jmp     Mainloop                ; Again
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"	           ; POR, ext. Reset, Watchdog
            .short  RESET
            .end
            