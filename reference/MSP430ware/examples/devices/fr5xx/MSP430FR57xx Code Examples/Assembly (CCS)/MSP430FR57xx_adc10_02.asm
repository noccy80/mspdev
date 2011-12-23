;*******************************************************************************
;   MSP430FR57xx Demo - ADC10, Sample A1, 1.5V Ref, Set P1.0 if A1 > 0.5V
;
;   Description: A single sample is made on A1 with reference to internal
;   1.5V Vref. Software sets ADC10SC to start sample and conversion - ADC10SC
;   automatically cleared at EOC. ADC10 internal oscillator times sample (16x)
;   and conversion. In Mainloop MSP430 waits in LPM0 to save power until ADC10
;   conversion complete, ADC10_ISR will force exit from LPM0 in Mainloop on
;   reti. If A1 > 0.5V, P1.0 set, else reset.
;
;                MSP430FR5739
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;        >---|P1.1/A1      P1.0|--> LED
;
;  T. Witt
;  Texas Instruments Inc.
;  September 2011
;  Built with Code Composer Studio v4.2
;*******************************************************************************
 .cdecls C,LIST,  "msp430fr5739.h"
ADC_Result	.set	R5
;------------------------------------------------------------------------------
			.global _main
            .text                  			; Program reset
;------------------------------------------------------------------------------
_main
RESET       mov.w   #1DFEh,SP               ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 output
SetVREF		bit.b	#REFGENBUSY,&REFCTL0    ; Is ref gen busy?
			jnz		SetVREF					; Yes, wait. No, set ref
			mov.w	#REFVSEL_0+REFON,&REFCTL0 ; Select internal ref = 1.5V
											; Internal Reference ON
SetupADC10  bis.b	#002h,&P1SEL1			; Configure ADC Pins
			bis.b	#002h,&P1SEL0			;
			mov.w   #ADC10SHT_2+ADC10ON,&ADC10CTL0;
			bis.w	#ADC10SHP,&ADC10CTL1	; ADCCLK = MODOSC; sampling timer
			bis.w	#ADC10RES,&ADC10CTL2	; 10-bit conversion results
			bis.w	#ADC10IE0,&ADC10IE		; Enable ADC conv complete interrupt
			bis.b	#ADC10INCH_1+ADC10SREF_1,&ADC10MCTL0 ; A1 ADC input select; Vref = 1.5V
            mov.w   #80,&TA0CCR0            ; Delay to allow Ref to settle
            bis.w   #CCIE,&TA0CCTL0         ; Compare-mode interrupt.
            mov.w   #MC_1+TASSEL_2,&TA0CTL	; up mode, SMCLK
            bis.w   #LPM0+GIE,SR            ; Enter LPM0, enable interrupts
            bic.w   #CCIE,&TA0CCTL0         ; Disable timer interrupt

Mainloop    mov.w   #2500,R15               ; Delay ~5000 cycles between conversions
L1          dec.w   R15                     ; Decrement R15
            jnz     L1                      ; Delay over?
            bis.w   #ADC10ENC+ADC10SC,&ADC10CTL0 ; Start sampling/conversion
            bis.w   #CPUOFF+GIE,SR          ; LPM0, ADC10 ISR will force exit
            bic.b   #01h,&P1OUT             ; P1.0 = 0
            cmp.w   #145h,&ADC10MEM0        ; ADC10MEM = A1 > 0.5V?
            jlo     Mainloop                ; Again
            bis.b   #01h,&P1OUT             ; P1.0 = 1
            jmp     Mainloop                ; Again

;-------------------------------------------------------------------------------
TA0_ISR;    ISR for TA0CCR0
;-------------------------------------------------------------------------------
            clr.w   &TA0CTL                 ; Clear Timer_A control registers
            bic.w   #LPM0,0(SP)             ; Exit LPM0, interrupts enabled
            reti                            ;
;-------------------------------------------------------------------------------
ADC10_ISR;  ADC10 interrupt service routine
;-------------------------------------------------------------------------------
            add.w   &ADC10IV,PC             ; add offset to PC
            reti                            ; No Interrupt
	    	reti		            		; Conversion result overflow
	    	reti		            		; Conversion time overflow
            reti                            ; ADHI
            reti                            ; ADLO
            reti          		    		; ADIN
            mov.w   &ADC10MEM0,ADC_Result   ; ADC10IFG0
            bic.w   #CPUOFF,0(SP)           ; Exit LPM0 on reti
            reti
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int54"                ; ADC10 Vector
            .short  ADC10_ISR               ;
            .sect   ".int53"                ; Timer_A0 Vector
            .short  TA0_ISR                 ;
            .end
