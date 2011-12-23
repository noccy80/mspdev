;******************************************************************************
;   MSP-FET430P120 Demo - ADC10, Sample A0, 1.5V Ref, .set P1.0 if A0 > 0.2V
;
;   Description: A single sample is made on A0 with reference to internal
;   1.5V Vref. Software sets ADC10SC to start sample and conversion - ADC10SC
;   automatically cleared at EOC. ADC10 internal oscillator times sample (16x)
;   and conversion. In Mainloop MSP430 waits in LPM0 to save power until ADC10
;   conversion complete, ADC10_ISR will force exit from any LPMx in Mainloop on
;   reti. If A0 > 0.2V, P1.0 set, else reset.
;   //* MSP430F1232 or MSP430F1132 Device Required *//
;
;                MSP430F1232
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;        >---|P2.0/A0     P1.0 |--> LED
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
SetupADC10  mov.w   #SREF_1+ADC10SHT_2+REFON+ADC10ON+ADC10IE,&ADC10CTL0;
            mov.w   #30,&TACCR0             ; Delay to allow Ref to settle
            bis.w   #CCIE,&TACCTL0          ; Compare-mode interrupt.
            mov.w   #TACLR+MC_1+TASSEL_2,&TACTL; up mode, SMCLK
            bis.w   #LPM0+GIE,SR            ; Enter LPM0, enable interrupts
            bic.w   #CCIE,&TACCTL0          ; Disable timer interrupt
            dint
            bis.b   #01h,&ADC10AE           ; P2.0 ADC10 option select
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 output

Mainloop    bis.w   #ENC+ADC10SC,&ADC10CTL0 ; Start sampling/conversion
            bis.w   #CPUOFF+GIE,SR          ; LPM0, ADC12 ISR will force exit
            bic.b   #01h,&P1OUT             ; P1.0 = 0
            cmp.w   #088h,&ADC10MEM         ; ADC10MEM = A0 > 0.2V?
            jlo     Mainloop                ; Again
            bis.b   #01h,&P1OUT             ; P1.0 = 1
            jmp     Mainloop                ; Again

;------------------------------------------------------------------------------
TA0_ISR;    ISR for CCR0
;------------------------------------------------------------------------------
            clr     &TACTL                  ; clear Timer_A control registers
            bic     #LPM0,0(SP)             ; Exit LPMx, interrupts enabled
            reti                            ;
;------------------------------------------------------------------------------
;------------------------------------------------------------------------------
ADC10_ISR;  Exit any LPMx on reti
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
            .sect   ".int09"                ; Timer_A0 Vector
            .short  TA0_ISR                 ;
            .end
