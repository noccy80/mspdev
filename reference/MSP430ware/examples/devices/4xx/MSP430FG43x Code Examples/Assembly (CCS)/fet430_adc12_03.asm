;******************************************************************************
;   MSP-FET430P430 Demo - ADC12, Sample A10 Temp, set P5.1 if temp ++ ~2c
;
;   Description: Use ADC12 and the integrated temperature sensor to detect
;   temperature gradients. The temperature sensor output voltage is sampled
;   ~ every 125ms and compared with the defined delta values using an ISR.
;   (ADC12OSC/256) determines sample time which needs to be greater than
;   30us for temperature sensor.
;   ADC12 is operated in repeat-single channel mode with the sample and
;   convert trigger sourced from Timer_A CCR1. The ADC12MEM0_IFG at the end
;   of each converstion will trigger an ISR.
;   ACLK = n/a, MCLK = SMCLK = default DCO, ADC12CLK = ADC12OSC
;
;                MSP430FG439
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |A10 (Temp)   P5.1|-->LED
;
;   M. Buccini / M. Mitchell
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430xG43x.h"

ADCDeltaOn  .equ     12                     ;  ~ 2 Deg C delta for LED on

;------------------------------------------------------------------------------
            .text                  ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stack pointer
            mov.w   #WDTPW+WDTHOLD,WDTCTL   ; Stop watchdog
            mov.w   #SHS_1+SHP+CONSEQ_2,&ADC12CTL1  ; TA trig., rpt conv
            mov.b   #SREF_1+INCH_10,&ADC12MCTL0  ; Channel A10, Vref+
            bis.w   #001h,&ADC12IE          ; Enable ADC12IFG.0
            mov.w   #SHT0_8+REF2_5V+REFON+ADC12ON+ENC,&ADC12CTL0  ; Config ADC12
            mov.w   #OUTMOD_4,&TACCTL1      ; Toggle on EQU1 (TAR = 0)
            mov.w   #TASSEL_2+MC_2,&TACTL   ; SMCLK, cont-mode
ADC_Wait    bit.w   #001h,&ADC12IFG         ; First conversion?
            jz      ADC_Wait
            mov.w   &ADC12MEM0,R4           ; Read out 1st ADC value
            add.w   #ADCDeltaOn,R4          ;
            clr.b   &P5OUT                  ; Clear P5
            bis.b   #02h,&P5DIR             ; P5.1 as output

                                            ;
Mainloop    bis.w   #LPM0+GIE,SR            ; Enter LPM0, enable interrupts
            nop                             ; Required only for debugger
                                            ;
;------------------------------------------------------------------------------
ADC12_ISR;
;------------------------------------------------------------------------------
            cmp.w   R4,&ADC12MEM0           ; ADC12MEM0 = A10 > R4
            jlo     ADC_ISR_1               ; Again
            bis.b   #02h,&P5OUT             ; P5.1 = 1
            reti                            ;		
ADC_ISR_1   bic.b   #02h,&P5OUT             ; P5.1 = 0
            reti                            ;		
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int07"                ; ADC12 Vector
            .short  ADC12_ISR               ;
            .end
