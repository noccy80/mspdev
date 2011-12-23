;*******************************************************************************
;   MSP430xG461x Demo - ADC12, Using an External Reference
;
;   This example shows how to use an external positive reference for the ADC12.
;   The external reference is applied to the VeREF+ pin. Avss is used for the
;   negative reference. A single conversion is performed on channel A0. The
;   conversion results are stored in ADC12MEM0 and are moved to R5 after the
;   conversion is complete. Test by applying a voltage to channel A0, then
;   setting and running to a break point at "jmp Mainloop". To view the
;   conversion results, open a register window in debugger and view the contents
;   of R5.
;
;
;                  MSP430xG461x
;                ---------------
;               |            XIN|-
;        Vin -->|P6.0/A0        | 32kHz
;               |           XOUT|-
;        REF -->|VeREF+         |
;               |               |
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430xG46x.h"
;-------------------------------------------------------------------------------
			.text	;Program Start
;-----------------------------------------------------------------------------
RESET       mov.w   #900,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog
            bis.b   #01h,&P6SEL             ; Enable A/D channel A0
                                            ;
SetupADC12  mov.w   #ADC12ON+SHT0_2,&ADC12CTL0  ; turn on ADC12, set samp time
            mov.w   #SHP,&ADC12CTL1         ; Use sampling timer
            mov.b   #SREF_2,&ADC12MCTL0     ; Vr+=VeREF+ (external)
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
;------------------------------------------------------------------------------
            .sect 	".reset"	           ; MSP430 RESET Vector
            .short   RESET                   ;
            .end
