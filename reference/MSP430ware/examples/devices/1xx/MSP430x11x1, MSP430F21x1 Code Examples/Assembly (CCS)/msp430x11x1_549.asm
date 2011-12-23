;*******************************************************************************
;   MSP430x11x1 Demo - Software SPI Interface TLC549, .set P1.0 if > 0.5*Vcc
;
;   Description: Read a TLC549 ADC with reference to Vcc using software SPI and
;   store the 8-bit digital code in ADCData(R11).  The TLC549 is sampled in a
;   continous loop. If ADCData > 0.5*Vcc, P1.0 set, else reset.
;   ACLK = n/a, MCLK = SMCLK = default DCO ~800k
;   ;* VCC must be at least 3v for TLC549 *//
;
;                        MSP430F1121
;                     -----------------
;                 /|\|              XIN|-
;                  | |                 |
;                  --|RST          XOUT|-
;       TLC549       |                 |
;     ----------     |                 |
;    |        CS|<---|P2.0         P1.0|-->LED
;  ~>| AIN+  CLK|<---|P2.1             |
;    |        DO|--->|P2.3             |
;
ADCData  .equ     R11
Counter  .equ     R12
CS          .equ     001h                    ; P2.0 - Chip Select
CLK         .equ     002h                    ; P2.1 - Clock
DO          .equ     008h                    ; P2.3 - Data Out
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
SetupP2     mov.b   #CS,&P2OUT              ; /CS set, - P2.x reset
            bis.b   #CS+CLK,&P2DIR          ; /CS and CLK outputs
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 output
                                            ;
Mainloop    call    #Meas_549               ; Call subroutine
            bic.b   #01h,&P1OUT             ; P1.0 = 0
            cmp.w   #07Fh,ADCData           ; ADCData > 0.5Vcc?
            jlo     Mainloop                ; Again
            bis.b   #01h,&P1OUT             ; P1.0 = 1
            jmp     Mainloop                ; Again
                                            ;
;-------------------------------------------------------------------------------
Meas_549;   Subroutine to read TLC549, data is shifted into ADCData
;           (R11), Counter (R12) is used as a bit counter.
;-------------------------------------------------------------------------------
            mov.w   #8,Counter              ; 8 data bits
            clr.w   ADCData                 ; Clear data buffer
            bic.b   #CS,&P2OUT              ; /CS reset, enable ADC
ADC_Loop    bit.b   #DO,&P2IN               ; (4) DO -> C (carry)
            rlc.w   ADCData                 ; (1) C -> ADCData
            bis.b   #CLK,&P2OUT             ; (4) Clock high
            bic.b   #CLK,&P2OUT             ; (4) Clock low
            dec.w   Counter                 ; (1) All bits shifted in?
            jnz     ADC_Loop                ; (2) If not --> ADC_Loop
            bis.b   #CS,&P2OUT              ; /CS set, disable ADC
            ret                             ; Return from subroutine
                                            ;
;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
