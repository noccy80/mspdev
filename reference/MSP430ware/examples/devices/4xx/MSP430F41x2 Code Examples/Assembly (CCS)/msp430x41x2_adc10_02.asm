;*******************************************************************************
;   MSP430F41x2 Demo - ADC10, Sample A0, 1.5V Ref, Set P5.1 if A0 > 0.2V
;
;   Description: A single sample is made on A0 with reference to internal
;   1.5V Vref. Software sets ADC10SC to start sample and conversion - ADC10SC
;   automatically cleared at EOC. ADC10 internal oscillator times sample (16x)
;   and conversion. In Mainloop MSP430 waits in LPM0 to save power until ADC10
;   conversion complete, ADC10_ISR will force exit from LPM0 in Mainloop on
;   reti. If A0 > 0.2V, P5.1 set, else reset.
;
;                MSP430F41x2
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;        >---|P7.4/A0      P5.1|--> LED
;
;  P. Thanigai
;  Texas Instruments Inc.
;  January 2009
;  Built with CCE Version: 3.1   
;******************************************************************************
 .cdecls C,LIST, "msp430x41x2.h" 

            .global _main
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
_main
RESET       mov.w   #0400h,SP               ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupADC10  mov.w   #SREF_1+ADC10SHT_2+REFON+ADC10ON+ADC10IE,&ADC10CTL0;
            mov.w   #30,&TACCR0             ; Delay to allow Ref to settle
            bis.w   #CCIE,&TACCTL0          ; Compare-mode interrupt.
            mov.w   #TACLR+MC_1+TASSEL_2,&TACTL; up mode, SMCLK
            bis.w   #LPM0+GIE,SR            ; Enter LPM0, enable interrupts
            bic.w   #CCIE,&TACCTL0          ; Disable timer interrupt
            bis.b   #01h,&ADC10AE0          ; P7.4 ADC10 option select
SetupP5     bis.b   #002h,&P5DIR            ; P5.1 output

Mainloop    bis.w   #ENC+ADC10SC,&ADC10CTL0 ; Start sampling/conversion
            bis.w   #CPUOFF+GIE,SR          ; LPM0, ADC12 ISR will force exit
            bic.b   #02h,&P5OUT             ; P5.1 = 0
            cmp.w   #088h,&ADC10MEM         ; ADC10MEM = A0 > 0.2V?
            jlo     Mainloop                ; Again
            bis.b   #02h,&P5OUT             ; P5.1 = 1
            jmp     Mainloop                ; Again

;-------------------------------------------------------------------------------
TA0_ISR;    ISR for TACCR0
;-------------------------------------------------------------------------------
            clr.w   &TACTL                  ; Clear Timer_A control registers
            bic.w   #LPM0,0(SP)             ; Exit LPM0, interrupts enabled
            reti                            ;
;-------------------------------------------------------------------------------
ADC10_ISR;  Exit LPM0 on reti
;-------------------------------------------------------------------------------
            bic.w   #LPM0,0(SP)             ; Exit LPM0, interrupts enabled
            reti                            ;
;-------------------------------------------------------------------------------
; 			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int07"            	; ADC10 Vector
            .short  ADC10_ISR
            .sect   ".int06"          		; Timer_A0 Vector 
            .short  TA0_ISR
            .sect   ".reset"	            ; POR, ext. Reset
            .short  RESET
            .end
