;*******************************************************************************
;   MSP430F22x4 Demo - ADC10, DTC Sample A2-0, AVcc, Single Sequence, DCO
;
;   Description: Sample A2/A1/A0 as single sequence with reference to AVcc.
;   Software sets ADC10SC to trigger sample sequence. In Mainloop MSP430 waits
;   in LPM0 to save power until ADC10 conversion complete, ADC10_ISR(DTC) will
;   force exit from any LPMx in Mainloop on reti. ADC10_ISR will force LPM0
;   exit. ADC10 internal oscillator times sample period (16x) and conversion
;   (13x). DTC transfers conversion code to RAM 200h - 206h. P1.0 set at start
;   of conversion burst, reset on completion.
;
;                MSP430F22x4
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;        >---|P2.2/A2      P1.0|-->LED
;        >---|P2.1/A1          |
;        >---|P2.0/A0          |
;
;  P.Thanigai
;  Texas Instruments Inc.
;  August 2007
;  Built with Code Composer Essentials Version: 2.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430x22x4.h"
                              
;------------------------------------------------------------------------------
            .text                  			; Program reset
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupADC10  mov.w   #INCH_2+CONSEQ_1,&ADC10CTL1 ; A2/A1/A0, single sequence
            mov.w   #ADC10SHT_2+MSC+ADC10ON+ADC10IE,&ADC10CTL0 ;
            bis.b   #07h,&ADC10AE0          ; P2.0,1,2 ADC10 option selects
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
;-------------------------------------------------------------------------------
ADC10_ISR;  Exit LPM0 on reti
;-------------------------------------------------------------------------------
            bic.w   #CPUOFF,0(SP)           ; Exit LPM0 on reti
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
