;*******************************************************************************
;   MSP430x11x1 Demo - Software Interface to Read ADS7822
;
;   Description: This program will read an ADS7822 ADC using software and
;   store the 12-bit digital code in ADCData (R11), buffering 16 samples in
;   RAM @ 200h.
;   ACLK = n/a, MCLK = SMCLK = default DCO ~800k
;   ;* VCC must be 2.7v+ for ADS7822, add CAPs as required *//
;
;                      MSP430F1121
;                    -----------------
;                /|\|              XIN|-
;                 | |                 |
;                 --|RST          XOUT|-
;                   |                 |
;     ADS7822       |                 |
;    ----------     |                 |
;   |        CS|<---|P2.0             |
; ~>|+In DCLOCK|<---|P2.1             |
;   |      Dout|--->|P2.3             |
;
Pointer  .equ     R10
ADCData  .equ     R11
Counter  .equ     R12
CS          .equ     001h                   ; P2.0 - Chip Select
DCLOCK      .equ     002h                   ; P2.1 - Clock
Dout        .equ     008h                   ; P2.3 - Data Out
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
RESET       mov.w   #0300h,SP               ; Initialize stack
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop Watchdog Timer
SetupP2     mov.b   #CS,&P2OUT              ; /CS set, - P2.x reset
            bis.b   #CS+DCLOCK,&P2DIR       ; /CS and DCLOCK outputs
                                            ;
Mainloop    call    #Meas_ADC_16            ; Call subroutine
            jmp     Mainloop                ; Repeat
                                            ;
;-------------------------------------------------------------------------------
Meas_ADC_16; Subroutine to call  Meas_7822 16x, results stored in RAM @200h
;           Pointer (R10) is used.
;-------------------------------------------------------------------------------
            mov.w   #200h,Pointer           ; Buffer @ 200h
Meas_Loop   call    #Meas_7822              ;
            mov.w   ADCData,0(Pointer)      ; Store ADC code
            incd.w  Pointer                 ;
            cmp.w   #0220h,Pointer          ; End of 16 word (32 byte) buffer
            jne     Meas_Loop               ;
            ret                             ; Return from subroutine

;-------------------------------------------------------------------------------
Meas_7822;  Subroutine to read ADS7822, data is shifted into ADCData (R11),
;           Counter (R12) is used as a bit counter.
;-------------------------------------------------------------------------------
            mov.w   #15,Counter             ; 2 smpl+null+12 data bits
            clr.w   ADCData                 ; Clear data buffer
            bic.b   #CS,&P2OUT              ; /CS reset, enable ADC
ADC_Loop    bis.b   #DCLOCK,&P2OUT          ; (4) Clock high
            bit.b   #Dout,&P2IN             ; (4) Dout -> C (carry)
            rlc.w   ADCData                 ; (1) C -> ADCData
            bic.b   #DCLOCK,&P2OUT          ; (4) Clock low
            dec.w   Counter                 ; (1) All bits shifted in?
            jnz     ADC_Loop                ; (2) If not --> ADC_Loop
            bis.b   #CS,&P2OUT              ; /CS set, disable ADC
            and.w   #0FFFh,ADCData          ; Keep only databits
            ret                             ; Return from subroutine
                                            ;
;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
