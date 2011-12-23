;*******************************************************************************
;   MSP430xG461x Demo - ADC12, Using 10 External Channels for Conversion
;
;   This example shows how to perform A/D conversion on up to 10 external
;   channels by showing that channels A8 and A9 can be used for conversion
;   of external signals when not using these channels as external reference
;   inputs. A single sequence of conversions is performed - one
;   conversion on A8 and then one conversion on A9. Each conversion uses AVcc
;   and AVss for the references. The conversion results are stored in ADC12MEM0
;   and ADC12MEM1 respectively and are moved to R5 and R6 respectively after
;   the sequence is complete. Test by applying voltages to pins VeREF+ for A8
;   and VREF/VeREF- for A9, then setting and running to a break point at
;   "jmp Mainloop."  To view the conversion results, open a register window in
;   debugger and view the contents of R5 and R6.
;
;   *NOTE*  When using channels A8 and A9 for external signals, internal
;   references must be used for the conversions (see MSP430x4xx Family
;   User's Guide).
;
;
;               MSP430xG461x
;            -------------------
;           |                XIN|-
;   Vin1 -->|VeREF+             | 32kHz
;   Vin2 -->|VREF-/VeREF-   XOUT|-
;
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
SetupADC12  mov.w   #ADC12ON+MSC+SHT0_15,&ADC12CTL0
                                            ; Turn on ADC12, set MSC bit
            mov.w   #SHP+CONSEQ_1,&ADC12CTL1; Use samp. timer, single sequence
            bis.b   #INCH_8,&ADC12MCTL0     ; AVcc=ref+, channel=A8
            bis.b   #INCH_9+EOS,&ADC12MCTL1 ; AVcc=ref+, channel=A9, end seq.
                                            ;
            mov.w   #02h,&ADC12IE           ; Enable ADC12IFG.1 for ADC12MEM1
            bis.w   #ENC,&ADC12CTL0         ; Enable conversions
                                            ;
Mainloop    bis.w   #ADC12SC,&ADC12CTL0     ; Start conversions
            bis.w   #CPUOFF+GIE,SR          ; Hold in LPM0 for seq to complete
                                            ; Enable interrupts
            nop                             ; Only required for debug.
            jmp     Mainloop                ; SET BREAKPOINT HERE
                                            ;
;-------------------------------------------------------------------------------
ADC12_ISR   ; Interrupt Service Routine for ADC12
;-------------------------------------------------------------------------------
            mov.w   &ADC12MEM0,R5           ; Move A8 result
            mov.w   &ADC12MEM1,R6           ; Move A9 result
            bic.w   #CPUOFF,0(SP)
            reti                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect	".int23"            ; ADC12 Vector
            .short   ADC12_ISR
            .sect 	".reset"	           ; MSP430 RESET Vector
            .short   RESET                   ;
            .end
