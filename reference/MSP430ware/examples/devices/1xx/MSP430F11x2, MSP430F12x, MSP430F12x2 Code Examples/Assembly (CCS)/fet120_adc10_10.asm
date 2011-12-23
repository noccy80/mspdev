;******************************************************************************
;   MSP-FET430P120 Demo - ADC10, DTC Sample A2-0, AVcc, Single Sequence, DCO
;
;   Description: Sample A1/A0/A3 as single sequence with reference to Avcc.
;   Software sets ADC10SC to trigger sample sequence. In Mainloop MSP430 waits
;   in LPM0 to save power until ADC10 conversion complete, ADC10_ISR(DTC) will
;   force exit from any LPMx in Mainloop on reti. ADC10_ISR will force any LPMx
;   exit. ADC10 internal oscillator times sample period (16x) and conversion
;   (13x). DTC transfers conversion code to RAM 200h - 206h. P1.0 .set at start
;   of conversion burst, reset on completion.
;   //* MSP430F1232 or MSP430F1132 Device Required *//
;
;                MSP430F1232
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;        >---|A3           P1.0|-->LED
;        >---|A2               |
;        >---|A0               |
;
;   M. Buccini / M. Raju
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x12x2.h"
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0300h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupADC10  mov.w   #INCH_2+CONSEQ_1,&ADC10CTL1 ; A2/A1/A0, single sequence
            mov.w   #ADC10SHT_2+MSC+ADC10ON+ADC10IE,&ADC10CTL0 ;
            bis.b   #07h,&ADC10AE           ; P2.0,1,2 ADC10 option selects
            mov.b   #03h,&ADC10DTC1         ; 3 conversions
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 output
                                            ;
Mainloop    bic.w   #ENC,&ADC10CTL0         ;
busy_test   bit     #BUSY,&ADC10CTL1        ; ADC10 core inactive?
            jnz     busy_test               ;
            mov.w   #0200h,&ADC10SA         ; Data buffer start
            bis.b   #001h,&P1OUT            ; P1.0 = 0
            bis.w   #ENC+ADC10SC,&ADC10CTL0 ; Start sampling
            bis.w   #CPUOFF+GIE,SR          ; LPM0, ADC10_ISR will force exit
            bic.b   #001h,&P1OUT            ; P1.0 = 1
            jmp     Mainloop                ; Again
                                            ;
;------------------------------------------------------------------------------
ADC10_ISR;
;------------------------------------------------------------------------------
            mov.w   #GIE,0(SP)              ; Exit any LPMx on reti
            reti                            ;		
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int05"                ; ADC10 Vector
            .short  ADC10_ISR               ;
            .end
