;*******************************************************************************
;   MSP430F41x2 Demo - ADC10, Sample A7, 1.5V, TA1 Trig, Ultra-Low Pwr
;
;   Description: A7 is sampled 1024/second (32xACLK) with reference to 1.5V.
;   All activity is interrupt driven with proper usage of MSP430 low-power
;   modes, ADC10 and Vref demonstrated. Timer_A with both TA1/TA0 used in
;   upmode to drive ADC10 conversion (continuous mode can also be used).
;   Inside of TA0_ISR software will enable ADC10 and internal reference and
;   allow > 30us delay for Vref to stabilize prior to sample start. Sample
;   start is automatically triggered by TA1 every 32 ACLK cycles. ADC10_ISR
;   will disable ADC10 and Vref and compare ADC10 conversion code. Internal
;   oscillator times sample (16x) and conversion (13x). If A7 > 0.2Vcc,
;   P5.1 is set, else reset. Normal Mode is LPM3.
;   //* An external watch crystal on XIN XOUT is required for ACLK *//
;
;                     +-----(0.9766us)---------\\------------------>+
;     TA0_ISR        TA1      ADC10_ISR             TA0_ISR        TA1
;   -----+------------+------------+-----------\\------+------------+----->
;    Enable ADC    Trigger ADC  Disable ADC
;    and Vref                   Compare
;        +-( >30us--->+
;
;
;                MSP430F41x2
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;        >---|P6.7/A7     P5.1 |--> LED
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
SetupP1     mov.b   #0FFh,&P1DIR            ; All P1.x outputs
            clr.b   &P1OUT                  ; All P1.x reset
SetupP2     mov.b   #0FFh,&P2DIR            ; All P2.x outputs-------
            clr.b   &P2OUT                  ; All P2.x reset
SetupP3     mov.b   #0FFh,&P3DIR            ; All P3.x outputs
            clr.b   &P3OUT                  ; All P3.x reset
SetupP4     mov.b   #0FFh,&P4DIR            ; All P4.x outputs
            clr.b   &P4OUT                  ; All P4.x reset
SetupP5     mov.b   #0FFh,&P5DIR            ; All P5.x outputs
            clr.b   &P5OUT                  ; All P5.x reset
SetupP6     mov.b   #0FFh,&P6DIR            ; All P6.x outputs
            clr.b   &P6OUT                  ; All P6.x reset
SetupP7     mov.b   #0FFh,&P7DIR            ; All P7.x outputs
            clr.b   &P7OUT                  ; All P7.x reset
            
SetupADC10  mov.w   #INCH_7+SHS_1,&ADC10CTL1  ; P6.7, TA0.OUT1 trigger sample start
            bis.b   #080h,&ADC10AE0         ; P6.7 ADC10 option select
SetupC0     mov.w   #CCIE,&TACCTL0          ; Enable interrupt
            mov.w   #32-1,&TACCR0           ; PWM Period
SetupC1     mov.w   #OUTMOD_3,&TACCTL1      ; TACCR1 set/reset
            mov.w   #2,&TACCR1              ; TACCR1 PWM Duty Cycle
SetupTA     mov.w   #TASSEL_1+MC_1,TACTL    ; ACLK, up mode
                                            ;
Mainloop    bis.w   #LPM3+GIE,SR            ; Enter LPM3
            nop                             ; Required only for debugger
                                            ;
;-------------------------------------------------------------------------------
ADC10_ISR;
;-------------------------------------------------------------------------------
            bic.w   #ENC,&ADC10CTL0         ; ADC10 disabled
            clr.w   &ADC10CTL0              ; ADC10, Vref disabled completely            
            cmp.w   #088h,&ADC10MEM         ; ADC10MEM = A7 > 0.2V?
            jlo     ADC10_Exit              ; Again
            bis.b   #02h,&P5OUT             ; P5.1 = 1
            reti
ADC10_Exit  bic.b   #02h,&P5OUT             ; P5.1 = 0
			reti                            ;
                                            ;
;-------------------------------------------------------------------------------
TA0_ISR;    ISR for TACCR0
;-------------------------------------------------------------------------------
            mov.w   #SREF_1+ADC10SHT_2+REFON+ADC10ON+ADC10IE,&ADC10CTL0;
            bis.w   #ENC,&ADC10CTL0         ; ADC10 enable set
            reti                            ;
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int07"            	; ADC10 Vector
            .short  ADC10_ISR
            .sect   ".int06"          		; Timer_A0 Vector
            .short  TA0_ISR
            .sect   ".reset"	            ; POR, ext. Reset
            .short  RESET
            .end
            