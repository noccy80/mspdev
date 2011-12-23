;******************************************************************************
;   MSP430x261x Demo - ADC12, Sequence of Conversions (non-repeated)
;
;   This example shows how to perform A/D conversions on a sequence of channels.
;   A single sequence of conversions is performed - one conversion each on
;   channels A0, A1, A2, and A3. Each conversion uses AVcc and AVss for the
;   references. The conversion results are stored in ADC12MEM0, ADC12MEM1,
;   ADC12MEM2, and ADC12MEM3 respectively and are moved to R5, R6, R7, and R8
;   respectively after the sequence is complete. Test by applying voltages to
;   pins A0, A1, A2, and A3, then setting and running to a break point at
;   "jmp Mainloop."  To view the conversion results, open a register window in
;   debugger and view the contents of R5, R6, R7, and R8.
;
;   Note that a sequence has no restrictions on which channels are converted.
;   For example, a valid sequence could be A0, A3, A2, A4, A2, A1, A0, and A7.
;   See the MSP430x2xx User's Guide for instructions on using the ADC12.
;
;                MSP430F241x
;                MSP430F261x
;            -----------------
;           |              XIN|-
;   Vin0 -->|P6.0/A0          | 32kHz
;   Vin1 -->|P6.1/A1      XOUT|-
;   Vin2 -->|P6.2/A2          |
;   Vin3 -->|P6.3/A3          |
;           |                 |
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x26x.h"
;-------------------------------------------------------------------------------
	.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #0850h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog
            bis.b   #0fh,&P6SEL             ; Enable A/D channel inputs
                                            ;
SetupADC12  mov.w   #ADC12ON+MSC+SHT0_2,&ADC12CTL0  ; Turn on ADC12, set MSC
            mov.w   #SHP+CONSEQ_1,&ADC12CTL1; Use samp. timer, single sequence
            bis.b   #INCH_0,&ADC12MCTL0     ; AVcc=ref+, channel=A0
            bis.b   #INCH_1,&ADC12MCTL1     ; AVcc=ref+, channel=A1
            bis.b   #INCH_2,&ADC12MCTL2     ; AVcc=ref+, channel=A2
            bis.b   #INCH_3+EOS,&ADC12MCTL3 ; AVcc=ref+, channel=A3, end seq.
                                            ;
            mov.w   #08h,&ADC12IE           ; Enable ADC12IFG.3 for ADC12MEM3
            bis.w   #ENC,&ADC12CTL0         ; Enable conversions
                                            ;
Mainloop    bis.w   #ADC12SC,&ADC12CTL0     ; Start conversions
            bis.w   #CPUOFF+GIE,SR          ; Wait in LPM0 for seq to complete
                                            ; Enable interrupts
            nop                             ; Only Required for debug
            jmp     Mainloop                ; SET BREAKPOINT HERE
                                            ;
;-------------------------------------------------------------------------------
ADC12_ISR   ; Interrupt Service Routine for ADC12
;-------------------------------------------------------------------------------
            bic.w   #CPUOFF,0(SP)
            mov.w   &ADC12MEM0,R5           ; Move A0 result
            mov.w   &ADC12MEM1,R6           ; Move A1 result
            mov.w   &ADC12MEM2,R7           ; Move A2 result
            mov.w   &ADC12MEM3,R8           ; Move A3 result, IFG is reset
            reti                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".int21"            ; ADC12 Vector
            .short	ADC12_ISR
            .sect	".reset"            ; POR, ext. Reset
            .short  RESET
            .end