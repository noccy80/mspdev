;*******************************************************************************
;   MSP430x11x1 Demo - Use JTAG for Downloadable Test Code
;
;   Description: This program demonstrates how to use JTAG to load a one-time
;   test code kernel into RAM. The test code is used only during initial
;   power up. The main program on power up tests for a key 0AA55h in RAM
;   location 0200h and if valid calls a test routine at RAM location 0202h.
;   After the test program has been executed, the RAM key is cleared. For
;   demonstration, the test code toggles P1.0 8 times.
;   The main program sets P1.0.
;   ACLK = n/a, MCLK = SMCLK = default DCO ~800k
;
;                MSP430F1121
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |             P1.0|-->LED
;
;   M. Buccini / Z. Albus
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430x11x1.h"
;-------------------------------------------------------------------------------
            .sect   ".sysmem"               ;
;-------------------------------------------------------------------------------
KEY         .short  0AA55h
ENTRY       mov.b   #16,R4                  ; R4 used as event counter
T1          xor.b   #001h,&P1OUT            ; Toggle P1.0
            mov.w   #0FFFFh,R5              ; R5 used as delay counter
T2          dec     R5                      ;
            jnz     T2                      ; Delay over?
            dec.b   R4                      ;
            jnz     T1                      ; Event over?
            clr.w   &KEY                    ; Clear password
            clr.w   &WDTCTL                 ; Force POR
                                            ;
;-------------------------------------------------------------------------------
            .text                           ;
;-------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 output
            cmp.w   #0AA55h,&200h           ; Check selftest password
            jne     Mainloop                ; jmp --> normal program
            call    #ENTRY                  ; Call selftest
                                            ;				          							
Mainloop    bis.b   #001h,&P1OUT            ; Set P1.0
            jmp     Mainloop                ; Again
;
;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
