;******************************************************************************
;   MSP-FET430P140 Demo - ADC12, Using the Internal Reference
;
;   Description: This program will show how to use the internal reference
;                for ADC12.
;
;   This example shows how to use the internal reference of the ADC12.
;   It uses the internal 2.5V reference and performs a single conversion
;   on channel A0. The conversion results are stored in ADC12MEM0 and are
;   moved to R5 after the conversion is complete. Test by applying a voltage
;   to channel A0, then setting and running to a break point at "jmp Mainloop".
;   To view the conversion results, open a register window in Debugger and view
;   the contents of R5.
;
;
;                MSP430F149
;              ---------------
;             |               |
;      Vin -->|P6.0/A0        |
;             |               |
;
;
;   M. Mitchell / G. Morton
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x14x.h"
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov     #0A00h,SP               ; Initialize stackpointer
StopWDT     mov     #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog
            bis.b   #BIT0,&P6SEL            ; Enable A/D channel A0
                                            ;
SetupADC12  mov     #REFON+REF2_5V+ADC12ON+SHT0_2,&ADC12CTL0
                                            ; Turn on 2.5V ref, set samp time
            mov     #SHP,&ADC12CTL1         ; Use sampling timer
            mov.b   #SREF_1,&ADC12MCTL0     ; Vr+=Vref+
                                            ;
            mov     #03600h,R15             ; Delay for needed ref start-up.
L$1         dec     R15                     ; See datasheet for details.
            jnz     L$1                     ;
                                            ;
            bis     #ENC,&ADC12CTL0         ; Enable conversions
                                            ;
Mainloop    bis     #ADC12SC,&ADC12CTL0     ; Start conversions
testIFG     bit     #BIT0,&ADC12IFG         ; Conversion done?
            jz      testIFG                 ; No, test again
            mov     &ADC12MEM0, R5          ; Move result
            jmp     Mainloop                ; SET BREAKPOINT HERE
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end