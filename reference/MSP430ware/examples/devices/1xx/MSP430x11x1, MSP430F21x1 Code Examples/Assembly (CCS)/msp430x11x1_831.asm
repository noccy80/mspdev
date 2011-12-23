;*******************************************************************************
;   MSP430x11x1 Demo - Software SPI Interface to TLV0831
;
;   Description: This program will read a TLV0831 ADC and store the 8-bit
;   digital code in RAM byte 200h. The TLV0831 is sampled in a loop.
;   ACLK = n/a, MCLK = SMCLK = default DCO ~800k
;
;                       MSP430F1121
;                     ----------------
;                /|\|              XIN|-
;                 | |                 |
;                 --|RST          XOUT|-
;                   |                 |
;      TLV0831      |                 |
;    ----------     |                 |
;   |        CS|<---|P2.0             |
; ~>| IN+   CLK|<---|P2.1             |
;   |        DO|--->|P2.3             |
;
;
CS          .equ   001h                     ; P2.0 Chip Select
CLK         .equ   002h                     ; P2.1 Clock
DO          .equ   008h                     ; P2.3 Data Out
;
;   M. Buccini / Z. Albus
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430x11x1.h"
;-------------------------------------------------------------------------------
            .text                           ; Program Start
;-------------------------------------------------------------------------------
RESET       mov     #0300h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop Watchdog Timer
SetupP2     bis.b   #CS,&P2OUT              ; CS, set
            bis.b   #CS+CLK,&P2DIR          ; CS and Clk Output direction
                                            ;
Mainloop    call    #Meas_0831              ; Call subroutine
            jmp     Mainloop                ; Repeat
                                            ;
;-------------------------------------------------------------------------------
Meas_0831;  Subroutine to read TLV0831, data is shifted into RAM byte
;           200h - temporary use of stack for bit-counter.
;-------------------------------------------------------------------------------
            bic.b   #CS,&P2OUT              ; Chip Select low
            push.b  #9                      ; 9 bits = 1 start+8 data
ADC_Loop    bis.b   #CLK,&P2OUT             ; Clock high
            bic.b   #CLK,&P2OUT             ; Clock low
            bit.b   #DO,&P2IN               ; DO -> C (carry)
            rlc.b   &200h                   ; C -> 200h
            dec.b   0(SP)                   ; All shifted in?
            jnz     ADC_Loop                ; If not --> ADC_Loop
            incd.w  SP                      ; Clean up stack
            bis.b   #CS,&P2OUT              ; Chip Select high
            ret                             ; Return from Subroutine
                                            ;
;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
