;*******************************************************************************
;   MSP430G2x31 Demo - ADC10, Sample A1, AVcc Ref, Set P1.0 if A1 > 0.5*AVcc
;
;   Description: A single sample is made on A1 with reference to AVcc.
;   Software sets ADC10SC to start sample and conversion - ADC10SC
;   automatically cleared at EOC. ADC10 internal oscillator times sample (16x)
;   and conversion. In Mainloop MSP430 waits in LPM0 to save power until ADC10
;   conversion complete, ADC10_ISR will force exit from any LPMx in Mainloop on
;   reti. If A1 > 0.5*AVcc, P1.0 set, else reset.
;
;                MSP430G2x31
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;        >---|P1.1/A1      P1.0|--> LED
;
;   D. Dang
;   Texas Instruments Inc.
;   October 2010
;   Built with Code Composer Essentials Version: 4.2.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430g2231.h"

;------------------------------------------------------------------------------
            .text                           ; Progam Start
;------------------------------------------------------------------------------
RESET       mov.w   #0280h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupADC10  mov.w   #ADC10SHT_2+ADC10ON+ADC10IE,&ADC10CTL0 ; 16x, enable int.
            mov.w   #INCH_1, &ADC10CTL1
            bis.b   #02h,&ADC10AE0          ; P1.1 ADC10 option select
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 output
                                            ;
Mainloop    bis.w   #ENC+ADC10SC,&ADC10CTL0 ; Start sampling/conversion
            bis.w   #CPUOFF+GIE,SR          ; LPM0, ADC10_ISR will force exit
            bic.b   #01h,&P1OUT             ; P1.0 = 0
            cmp.w   #01FFh,&ADC10MEM        ; ADC10MEM = A1 > 0.5AVcc?
            jlo     Mainloop                ; Again
            bis.b   #01h,&P1OUT             ; P1.0 = 1
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
