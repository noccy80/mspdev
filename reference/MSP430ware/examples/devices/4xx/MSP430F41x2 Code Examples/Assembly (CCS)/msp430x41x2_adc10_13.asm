;*******************************************************************************
;   MSP430F41x2 Demo - ADC10, DTC Sample A1 32x, AVcc, TA0 Trig, DCO
;
;   Description; A1 is sampled in 32x burst using DTC 16 times per second
;   (ACLK/2048) with reference to AVcc. Activity is interrupt driven.
;   Timer_A in upmode uses TA1 toggle to drive ADC10 conversion. Sample burst
;   is automatically triggered by TA1.OUT0 rising edge every 2048 ACLK cycles.
;   ADC10_ISR will exit from LPM3 mode and return CPU active. Internal ADC10OSC
;   times sample (16x) and conversion (13x). DTC transfers conversion code to
;   RAM 200h - 240h. In the Mainloop P5.1 is toggled. Normal Mode is LPM3.
;   //* An external watch crystal on XIN XOUT is required for ACLK *//
;
;                MSP430F41x2
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;        >---|P7.5/A1     P5.1 |--> LED
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
SetupADC10  mov.w   #INCH_1+SHS_2+CONSEQ_2,&ADC10CTL1 ; TA0 trigger
            mov.w   #ADC10SHT_2+MSC+ADC10ON+ADC10IE,&ADC10CTL0;
            mov.b   #020h,&ADC10DTC1        ; 32 conversions
SetupP1     bis.b   #002h,&P5DIR            ; P5.1 output
            bis.b   #002h,&ADC10AE0         ; P7.5 ADC10 option select
            mov.w   #1024-1,&TA1CCR0        ; PWM Period
SetupC0     mov.w   #OUTMOD_4,&TA1CCTL0     ; TA1CCR0 toggle
SetupTA     mov.w   #TASSEL_1+MC_1,TA1CTL   ; ACLK, up mode
                                            ;
Mainloop    bic.w   #ENC,&ADC10CTL0         ;
busy_test   bit     #BUSY,&ADC10CTL1        ; ADC10 core inactive?
            jnz     busy_test               ;
            mov.w   #0200h,&ADC10SA         ; Data buffer start
            bis.w   #ENC,&ADC10CTL0         ; Sampling and conversion ready
            bis.w   #LPM3+GIE,SR            ; LPM3, ADC10_ISR will force exit
            xor.b   #002h,&P5OUT            ; P1.0 = toggle
            jmp     Mainloop                ; Again
                                            ;
;-------------------------------------------------------------------------------
ADC10_ISR;  Exit LPM3 on reti
;-------------------------------------------------------------------------------
            bic.w   #LPM3,0(SP)             ; Exit LPM3 on reti
            reti                            ;
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int07"            	; ADC10 Vector
            .short  ADC10_ISR
            .sect   ".reset"	            ; POR, ext. Reset
            .short  RESET
            .end                        

