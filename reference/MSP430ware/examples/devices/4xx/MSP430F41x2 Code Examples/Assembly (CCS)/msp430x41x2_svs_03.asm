;******************************************************************************
;   MSP430F41x2 Demo - SVS, Toggle P5.1 on Vcc < 2.8V
;
;  Description: The SVS feature is used to monitor VCC. LED toggles when Vcc 
;  drops below reference threshold of 2.8V.SVS flags need to be reset in
;  software.
;  
;  ACLK= n/a, MCLK= SMCLK= default DCO ~ 1.1MHz
;
;               MSP430F41x2
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |             P5.1|-->LED
;            |                 |
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
SetupP5     bis.b   #002h,&P5DIR            ; P5.1  output            
            mov.b   #VLD3,&SVSCTL           ; SVS enabled @ 2.8V, no POR
                                            
Mainloop    clr.b   &P5OUT
            bit.b   #SVSFG,&SVSCTL
            jz      Mainloop
            bic.b   #SVSFG,&SVSCTL
            bis.b   #002h,&P5OUT            ; Turn LED on
            mov.w   #050000,R15             ; Delay to R15
L1          dec.w   R15                     ; Decrement R15
            jnz     L1    
            jmp     Mainloop                ; Again                                          
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"	           ; POR, ext. Reset, Watchdog
            .short  RESET
            .end
            