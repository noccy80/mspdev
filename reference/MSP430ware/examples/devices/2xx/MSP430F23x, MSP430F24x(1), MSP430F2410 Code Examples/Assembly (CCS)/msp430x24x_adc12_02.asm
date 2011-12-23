;*******************************************************************************
;   MSP430x24x Demo - ADC12, Using the Internal Reference
;
;   This example shows how to use the internal reference of the ADC12.
;   It uses the internal 2.5V reference and performs a single conversion
;   on channel A0. The conversion results are stored in ADC12MEM0 and are
;   moved to R5 after the conversion is complete. Test by applying a voltage
;   to channel A0, then setting and running to a break point at "jmp Mainloop".
;   To view the conversion results, open a register window in Debugger and view
;   the contents of R5.
;
;                MSP430x24x
;              ---------------
;             |            XIN|-
;             |               | 32kHz
;      Vin -->|P6.0/A0    XOUT|-
;             |               |
;
;
;  JL Bile
;  Texas Instruments Inc.
;  May 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x24x.h"
;-------------------------------------------------------------------------------
	.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #0500h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog
            bis.b   #01h,&P6SEL             ; Enable A/D channel A0
                                            ;
SetupADC12  mov.w   #REFON+REF2_5V+ADC12ON+SHT0_2,&ADC12CTL0
                                            ; turn on 2.5V ref, set samp time
            mov.w   #SHP,&ADC12CTL1         ; Use sampling timer
            mov.b   #SREF_1,&ADC12MCTL0     ; Vr+=Vref+
                                            ;
            mov.w   #03600h,R15             ; Delay for needed ref start-up.
L$1         dec.w   R15                     ; See datasheet for details.
            jnz     L$1                     ;
                                            ;
            bis.w   #ENC,&ADC12CTL0         ; Enable conversions
                                            ;
Mainloop    bis.w   #ADC12SC,&ADC12CTL0     ; Start conversions
testIFG     bit.w   #01h,&ADC12IFG          ; Conversion done?
            jz      testIFG                 ; No, test again
            mov.w   &ADC12MEM0, R5          ; Move result
            jmp     Mainloop                ; SET BREAKPOINT HERE
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
           .sect    ".reset"            ; POR, ext. Reset
           .short    RESET
           .end
