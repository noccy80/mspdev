;******************************************************************************
;   MSP430x41x2 Demo - Software Poll P1.4, Set P5.1 if P1.4 = 1
;
;   Description: Poll P1.4 in a loop, if HI, P5.1 is set, if LOW, P5.1 reset.
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
                                            ;				          			
Mainloop    bit.b   #010h,&P1IN             ; P1.4 hi/low?
            jc      ON                      ; jmp--> P1.4 is set
                                            ;
OFF         bic.b   #BIT1,&P5OUT            ; P5.1 = 0 / LED OFF
            jmp     Mainloop                ;
ON          bis.b   #BIT1,&P5OUT            ; P5.1 = 1 / LED ON
            jmp     Mainloop                ;
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"	           ; POR, ext. Reset, Watchdog
            .short  RESET
            .end
