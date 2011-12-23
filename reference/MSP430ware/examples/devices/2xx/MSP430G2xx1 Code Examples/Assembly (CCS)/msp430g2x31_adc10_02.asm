;*******************************************************************************
;   MSP430G2x31 Demo - ADC10, Sample A1, 1.5V Ref, Set P1.0 if A1 > 0.2V
;
;   Description: A single sample is made on A1 with reference to internal
;   1.5V Vref. Software sets ADC10SC to start sample and conversion - ADC10SC
;   automatically cleared at EOC. ADC10 internal oscillator times sample (16x)
;   and conversion. In Mainloop MSP430 waits in LPM0 to save power until ADC10
;   conversion complete, ADC10_ISR will force exit from any LPMx in Mainloop on
;   reti. If A1 > 0.2V, P1.0 set, else reset.
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
SetupADC10  mov.w   #SREF_1+ADC10SHT_2+REFON+ADC10ON+ADC10IE,&ADC10CTL0;
            mov.w   #30,&TACCR0             ; Delay to allow Ref to settle
            bis.w   #CCIE,&TACCTL0          ; Compare-mode interrupt.
            mov.w   #TACLR+MC_1+TASSEL_2,&TACTL; up mode, SMCLK
            bis.w   #LPM0+GIE,SR            ; Enter LPM0, enable interrupts
            bic.w   #CCIE,&TACCTL0          ; Disable timer interrupt
            dint
            bis.b   #02h,&ADC10AE0          ; P1.1 ADC10 option select
            mov.w   #INCH_1, &ADC10CTL1     ; A1 input
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 output

Mainloop    bis.w   #ENC+ADC10SC,&ADC10CTL0 ; Start sampling/conversion
            bis.w   #CPUOFF+GIE,SR          ; LPM0, ADC12 ISR will force exit
            bic.b   #01h,&P1OUT             ; P1.0 = 0
            cmp.w   #088h,&ADC10MEM         ; ADC10MEM = A1 > 0.2V?
            jlo     Mainloop                ; Again
            bis.b   #01h,&P1OUT             ; P1.0 = 1
            jmp     Mainloop                ; Again

;-------------------------------------------------------------------------------
TA0_ISR;    ISR for TACCR0
;-------------------------------------------------------------------------------
            clr.w   &TACTL                  ; Clear Timer_A control registers
            bic.w   #LPM0,0(SP)             ; Exit LPM0, interrupts enabled
            reti                            ;
;-------------------------------------------------------------------------------
ADC10_ISR;  Exit LPM0 on reti
;-------------------------------------------------------------------------------
            bic.w   #LPM0,0(SP)             ; Exit LPM0, interrupts enabled
            reti                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int05"                ; ADC10 Vector
            .short  ADC10_ISR               ;
            .sect   ".int09"                ; Timer_A0 Vector
            .short  TA0_ISR                 ;
            .end

