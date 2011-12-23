;*******************************************************************************
;   MSP430xG461x Demo - ADC12, Extend Sampling Period with SHT Bits
;
;   This example shows how to extend the sampling time using the sampling
;   timer. In this example, the ADC12OSC is used to provide the sampling period
;   and the SHT0 bits are set to extend the sampling period to 4xADC12CLKx256.
;   A single conversion is performed on channel A0. The A/D conversion results
;   are stored in ADC12MEM0 and are moved to R5 upon completion of the
;   conversion. Test by setting and running to a break point at "jmp Mainloop."
;   To view the conversion results, open a register window in debugger and view
;   the contents of R5.
;
;
;               MSP430xG461x
;              ---------------
;             |            XIN|-
;      Vin -->|P6.0/A0        | 32kHz
;             |           XOUT|-
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
                                            ;
SetupADC12  mov.w   #ADC12ON+SHT0_15,&ADC12CTL0 ; Turn on ADC12, set SHT0
                                                ; for longer sampling
            mov.w   #SHP,&ADC12CTL1         ; Use sampling timer
            bis.w   #01h,&ADC12IE           ; Enable ADC12IFG.0 for ADC12MEM0
            bis.w   #ENC,&ADC12CTL0         ; Enable conversions
                                            ;
Mainloop    bis.w   #ADC12SC,&ADC12CTL0     ; Start conversions
            bis.w   #LPM0+GIE,SR            ; Wait for conversion completion
                                            ; Enable interrupts
            nop                             ; Only required for CSPY
            jmp     Mainloop                ; SET BREAKPOINT HERE
                                            ;
;-------------------------------------------------------------------------------
ADC12_ISR   ; Interrupt Service Routine for ADC12
;-------------------------------------------------------------------------------
            mov.w   &ADC12MEM0,R5           ; Move result, IFG is reset
            bic.w   #CPUOFF,0(SP)           ; Return active
            reti                            ;
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect    ".int23"            ; ADC12 Vector
            .short   ADC12_ISR
            .sect 	".reset"	           ; MSP430 RESET Vector
            .short   RESET                   ;
            .end

