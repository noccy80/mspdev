;******************************************************************************
;   MSP-FET430P430 Demo - ADC12, Using the Internal Reference, Channel A12
;
;   Description: This program shows how to use one of the additional
;                channels for ADC12 in the MSP430FG439
;
;   This example shows how to use the internal reference of the ADC12.
;   It uses the internal 2.5V reference and performs a single conversion
;   on channel A12. The conversion results are stored in ADC12MEM0 and are
;   moved to R5 after the conversion is complete. Test by applying a voltage
;   to channel A12, then setting and running to a break point at "jmp Mainloop"
;   To view the conversion results, open a register window with the debugger
;   and view the contents of R5.
;   ACLK = n/a, MCLK = SMCLK = default DCO, ADC12CLK = ADC12OSC
;
;
;                MSP430FG439
;              ---------------
;             |               |
;      Vin -->|P5.1/A12       |
;             |               |
;
;
;   M. Mitchell / M. Mitchell
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430xG43x.h"
;------------------------------------------------------------------------------
            .text                  ; Program Start
;------------------------------------------------------------------------------
RESET       mov     #0A00h,SP               ; Initialize stack pointer
StopWDT     mov     #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog
            bis.b   #BIT1,&P5SEL            ; Enable A/D channel A12
                                            ;
SetupADC12  mov     #REFON+REF2_5V+ADC12ON+SHT0_2,&ADC12CTL0
                                            ; turn on 2.5V ref, set samp time
            mov     #SHP,&ADC12CTL1         ; Use sampling timer
            mov.b   #SREF_1+INCH_12,&ADC12MCTL0; Vr+=Vref+,  channel 12
                                            ;
            mov     #03600h,R15             ; Delay for needed ref start-up.
L$1         dec     R15                     ; See datasheet for details.
            jnz     L$1                     ;
            bis     #ENC,&ADC12CTL0         ; Enable conversions
                                            ;
Mainloop    bis     #ADC12SC,&ADC12CTL0     ; Start conversions
testIFG     bit     #BIT0,&ADC12IFG         ; Conversion done?
            jz      testIFG                 ; No, test again
            mov     &ADC12MEM0, R5          ; Move result
            jmp     Mainloop                ; Set BREAKPOINT HERE
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; RESET Vector
            .short  RESET                   ;
            .end