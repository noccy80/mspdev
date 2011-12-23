;*****************************************************************************
;   MSP-FET430P140 Demo - ADC12, Sample A10 Temp, Set P1.0 if Temp ++ ~2C
;
;   Description: Use ADC12 and the integrated temperature sensor to detect
;   temperature gradients. The temperature sensor output voltage is sampled
;   ~ every 80ms and compared with the defined delta values using an ISR.
;   (ADC12OSC/256)/ determines sample time which needs to be greater than
;   30us for temperature sensor.
;   ADC12 is operated in repeat-single channel mode with the sample and
;   convert trigger sourced from Timer_A CCR1. The ADC12MEM)_IFG at the end
;   of each conversion will trigger an ISR.
;   ACLK = n/a, MCLK = SMCLK = default DCO ~800kHz, ADC12CLK = ADC12OSC
;
;                 MSP430F149
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |A10          P1.0|-->LED
;
ADCDeltaOn  .equ    12                      ;  ~ 2 Deg C delta for LED on
;
;   M. Buccini / G. Morton
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x14x.h"
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stackpointer
            mov.w   #WDTPW+WDTHOLD,WDTCTL   ; Stop watchdog
            mov.w   #SHS_1+SHP+CONSEQ_2,&ADC12CTL1  ; TA trig., rpt conv
            mov.b   #SREF_1+INCH_10,&ADC12MCTL0  ; Channel A10, Vref+
            bis.w   #001h,&ADC12IE          ; Enable ADC12IFG.0
            mov.w   #SHT0_8+REF2_5V+REFON+ADC12ON,&ADC12CTL0  ; Config ADC12
            mov.w   #13600,&TACCR0          ; Delay to allow Ref to settle
            bis.w   #CCIE,&TACCTL0          ; Compare-mode interrupt.
            mov.w   #TACLR+MC_1+TASSEL_2,&TACTL; up mode, SMCLK
            bis.w   #LPM0+GIE,SR            ; Enter LPM0, Enable interrupts
            bic.w   #CCIE,&TACCTL0          ; Disable timer interrupt
            dint                            ; Disable Interrupts
            bis.w   #ENC,&ADC12CTL0         ; Config ADC12
            mov.w   #OUTMOD_4,&TACCTL1      ; Toggle on EQU1 (TAR = 0)
            mov.w   #TASSEL_2+MC_2,&TACTL   ; SMCLK, cont-mode
ADC_Wait    bit.w   #001h,&ADC12IFG         ; First conversion?
            jz      ADC_Wait
            mov.w   &ADC12MEM0,R4           ; Read out 1st ADC value
            add.w   #ADCDeltaOn,R4          ;
            clr.b   &P1OUT                  ; Clear P1
            bis.b   #01h,&P1DIR             ; P1.0 as output
                                            ;
Mainloop    bis.w   #LPM0+GIE,SR            ; Enter LPM0, enable interrupts
            nop                             ; Required only for debugger
                                            ;
;------------------------------------------------------------------------------
TA0_ISR;    ISR for CCR0
;------------------------------------------------------------------------------
            clr     &TACTL                  ; clear Timer_A control registers
            bic     #LPM0,0(SP)             ; Exit LPMx, interrupts enabled
            reti                            ;
;------------------------------------------------------------------------------
;------------------------------------------------------------------------------
ADC12_ISR;
;------------------------------------------------------------------------------
            cmp.w   R4,&ADC12MEM0           ; ADC12MEM0 = A10 > R4
            jlo     ADC_ISR_1               ; Again
            bis.b   #01h,&P1OUT             ; P1.0 = 1
            reti                            ;		
ADC_ISR_1   bic.b   #01h,&P1OUT             ; P1.0 = 0
            reti                            ;		
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors Used MSP430x13x/14x/15x/16x
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int07"                ; ADC12 Vector
            .short  ADC12_ISR               ;
            .sect   ".int06"                ; Timer_A0 Vector
            .short  TA0_ISR                 ;
            .end
