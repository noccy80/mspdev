;*******************************************************************************
;   MSP430F22x4 Demo - ADC10, Sample A10 Temp, Set P1.0 if Temp ++ ~2C
;
;   Description: Set ADC10 and the integrated temperature sensor to detect
;   temperature gradients. The temperature sensor output voltage is sampled
;   ~ every 120ms and compared with the defined delta values using an ISR.
;   (ADC10OSC/4)/64 determines sample time which needs to be greater than
;   30us for temperature sensor.
;   ADC10 is operated in repeat-single channel mode with the sample and
;   convert trigger sourced from Timer_A CCR1. The ADC10IFG at the end
;   of each converstion will trigger an ISR.
;   ACLK = n/a, MCLK = SMCLK = default DCO ~1.2MHz, ADC10CLK = ADC10OSC
;
;                MSP430F22x4
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |A10 (Temp)   P1.0|-->LED
;
;  P.Thanigai
;  Texas Instruments Inc.
;  August 2007
;  Built with Code Composer Essentials Version: 2.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430x22x4.h"

ADCDeltaOn  .set   3                               
;------------------------------------------------------------------------------
            .text                  			; Program reset
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stack pointer
            mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
            mov.w   #ADC10DIV_3+INCH_10+SHS_1+CONSEQ_2,&ADC10CTL1
            mov.w   #SREF_1+ADC10SHT_3+REF2_5V+ADC10IE+REFON+ADC10ON,&ADC10CTL0
            mov.w   #30,&TACCR0             ; Delay to allow Ref to settle
            bis.w   #CCIE,&TACCTL0          ; Compare-mode interrupt.
            mov.w   #TACLR+MC_1+TASSEL_2,&TACTL; up mode, SMCLK
            bis.w   #LPM0+GIE,SR            ; Enter LPM0, enable interrupts
            bic.w   #CCIE,&TACCTL0          ; Disable timer interrupt
            bis.w   #ENC,&ADC10CTL0         ;
            mov.w   #OUTMOD_4,&TACCTL1      ; Toggle on EQU1 (TAR = 0)
            mov.w   #TASSEL_2+MC_2,&TACTL   ; SMCLK, cont-mode
ADC_Wait    bit.w   #ADC10IFG,&ADC10CTL0    ; First conversion?
            jnc     ADC_Wait
            mov.w   &ADC10MEM,R4            ; Read out 1st ADC value
            add.w   #ADCDeltaOn,R4          ;
            clr.b   &P1OUT                  ; Clear P1
            bis.b   #01h,&P1DIR             ; P1.0 as output
                                            ;
Mainloop    bis.w   #LPM0+GIE,SR            ; Enter LPM0, enable interrupts
            nop                             ; Required only for debugger
                                            ;
;-------------------------------------------------------------------------------
TA0_ISR;    ISR for TACCR0
;-------------------------------------------------------------------------------
            clr.w   &TACTL                  ; Clear Timer_A control registers
            bic.w   #LPM0,0(SP)             ; Exit LPM0 on reti
            reti                            ;
;-------------------------------------------------------------------------------
ADC10_ISR;
;-------------------------------------------------------------------------------
            cmp.w   R4,&ADC10MEM            ; ADC10MEM = A10 > R4
            jlo     ADC_ISR_1               ; Again
            bis.b   #01h,&P1OUT             ; P1.0 = 1
            reti                            ;
ADC_ISR_1   bic.b   #01h,&P1OUT             ; P1.0 = 0
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
