;*******************************************************************************
;   MSP430x11x1 Demo - Software Interface to HC165 Shift Register
;
;   Description: Read an HC165 shift register.  /LD is pulsed low to latch
;   in parallel data, then 8-bits are shifted out of the HC165 into the MSP430
;   stored in register Data (R4).
;   ACLK = n/a, MCLK = SMCLK = default DCO ~800k
;
;                       MSP430F1121
;                    -----------------
;                /|\|              XIN|-
;                 | |                 |
;       HC165     --|RST          XOUT|-
;     ----------    |                 |
;    |      /LD|<---|P2.0             |
;  ->|A-H   CLK|<---|P2.1             |
;  |-|INH    QH|--->|P2.2             |
;  |-|SER      |    |                 |
;  v
;
Data        .equ     R4
LD          .equ     001h                   ; P2.0 LD
CLK         .equ     002h                   ; P2.1 Serial clock
QH          .equ     004h                   ; P2.2 Data out
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
SetupP2     mov.b   #LD,&P2OUT              ; /LD set, - P2.x reset
            bis.b   #LD+CLK,&P2DIR          ; /LD and CLK outputs
                                            ;
Mainloop    call    #Read_HC165             ; Data <-- HC165
            jmp     Mainloop                ; Repeat
                                            ;
;-------------------------------------------------------------------------------
Read_HC165; Shift data from HC165 --> Data (R4)
;-------------------------------------------------------------------------------
            bic.b   #LD,&P2OUT              ; /LD reset
            bis.b   #LD,&P2OUT              ; /LD set
            clr.w   Data                    ;
            push.b  #8                      ; 8 bits to Read - TOS
RX_loop     bit.b   #QH,&P2IN               ; QH --> Carry
            rlc.b   Data                    ; Carry --> Data
            bis.b   #CLK,&P2OUT             ; CLK set
            bic.b   #CLK,&P2OUT             ; CLK reset
            dec.b   0(SP)                   ; All 8 bits sent?
            jnz     RX_loop                 ;
            incd.w  SP                      ; bit counter off stack
            ret                             ; Return from subroutine
                                            ;
;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
