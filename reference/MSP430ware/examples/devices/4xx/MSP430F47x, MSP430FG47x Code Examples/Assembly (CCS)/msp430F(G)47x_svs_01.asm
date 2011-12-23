;******************************************************************************
;   MSP430FG47x Demo - SVS, POR @ 2.5V Vcc
;
;   Description: The SVS POR feature is used to disable normal operation that
;   toggles P4.6 by xor'ing P4.6 inside of a software loop.
;   In the example, when VCC is above 2.5V, the MSP430 toggles P4.6. When VCC is
;   below 2.5V, the SVS resets the MSP430, and no toggle is seen.
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;                 MSP430FG47x
;              -----------------
;          /|\|              XIN|-
;           | |                 |
;           --|RST          XOUT|-
;             |                 |
;             |             P4.6|-->LED
;
;   P.Thanigai
;   Texas Instruments Inc.
;   September 2008
;   Built with Code Composer Essentials Version: 3.0
;******************************************************************************
 .cdecls C,LIST, "msp430xG47x.h" 

;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP4     bis.b   #040h,&P4DIR            ; P4.6  output
            mov.b   #060h+PORON,&SVSCTL     ; SVS POR enabled @ 2.5V
                                            ;
Mainloop    mov.w   #050000,R15             ; Delay to R15
L1          dec.w   R15                     ; Decrement R15
            jnz     L1                      ; Delay over?
            xor.b   #040h,&P4OUT            ; Toggle P4.6
            jmp     Mainloop                ; Again
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;  
            .end
