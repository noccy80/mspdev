;*******************************************************************************
;   MSP430x11x1 Demo - Software SPI Interface to HC164 Shift Register
;
;   Description: Transfer byte data from Data (R4) serially to HC164. Data
;   incremented in the mainloop, effectively incrementing HC164 QA - QH.
;   ACLK = n/a, MCLK = SMCLK = default DCO ~800k
;
;                MSP430F1121     ^     HC164
;             -----------------  |  ----------
;            |                 | |-|/CLR,B    |  8
;            |             P2.1|-->|CLK     Qx|--\->
;            |             P2.3|-->|A         |
;            |                 |   |          |
;
Data        .equ     R4
CLK         .equ     002h                   ; P2.1 Serial Clock
A           .equ     008h                   ; P2.3 Data Out
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
RESET       mov.w   #0300h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop Watchdog Timer
SetupP2     bic.b   #CLK+A,&P2OUT           ; Reset CLK and A
            bis.b   #CLK+A,&P2DIR           ; CLK and A config. as output
            mov.b   #0FFh,Data              ;
                                            ;
Mainloop    inc.b   Data                    ; Increment Data value
            call    #TX_HC164               ; Data --> HC164
            call    #Delay                  ; Wait
            jmp     Mainloop                ; Repeat
                                            ;
;-------------------------------------------------------------------------------
TX_HC164;   Shift Data (R4) --> HC164
;-------------------------------------------------------------------------------
            push.b  Data                    ; TOS = Save Data
            push.b  #8                      ; TOS = 8-bit counter
TX_loop     bic.b   #A,&P2OUT               ; A reset
            rla.b   Data                    ; Data MSB -> Carry
            jnc     Clk_1                   ;
Out_1       bis.b   #A,&P2OUT               ; A set
Clk_1       bis.b   #CLK,&P2OUT             ; SCLK set
Clk_0       bic.b   #CLK,&P2OUT             ; SCLK reset
            dec.b   0(SP)                   ; All 8 bits sent?
            jnz     TX_loop                 ;
            incd.w  SP                      ; bit counter off stack
            pop.b   Data                    ; Original data
            ret                             ; Return from subroutine
                                            ;
;-------------------------------------------------------------------------------
Delay;      Software delay
;-------------------------------------------------------------------------------
            push.w  #0FFFFh                 ; Delay to TOS
L1          dec.w   0(SP)                   ; Decrement TOS
            jnz     L1                      ; Delay over?
            incd.w  SP                      ; Clean TOS
            ret                             ;
                                            ;
;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
