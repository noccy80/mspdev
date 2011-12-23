;*******************************************************************************
;   MSP430xG461x Demo - DAC12_0, Output 1.0V on DAC0
;
;   Description: Using DAC12_0 and 2.5V ADC12REF reference with a gain of 1,
;   output 1V on P6.6.
;
;
;                MSP430xG461x
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |        DAC0/P6.6|--> 1V
;            |                 |
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
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupADC12  mov.w   #REF2_5V+REFON,&ADC12CTL0 ; Internal 2.5V ref on
            mov.w   #13600,&TACCR0          ; Delay to allow Ref to settle
            bis.w   #CCIE,&TACCTL0          ; Compare-mode interrupt.
            mov.w   #TACLR+MC_1+TASSEL_2,&TACTL; up mode, SMCLK
            bis.w   #LPM0+GIE,SR            ; Enter LPM0, enable interrupts
            bic.w   #CCIE,&TACCTL0          ; Disable timer interrupt
            dint                            ; Disable Interrupts
SetupDAC120 mov.w   #DAC12IR+DAC12AMP_5+DAC12ENC,&DAC12_0CTL  ; Int ref gain 1
            mov.w   #0666h,&DAC12_0DAT      ; 1.0V
                                            ;
Mainloop    bis.w   #LPM0,SR                ; Enter LPM0
            nop                             ; Required only for debugger
                                            ;
;-------------------------------------------------------------------------------
TIMERA0_ISR;
;-------------------------------------------------------------------------------
            clr.w   &TACTL                  ; Clear Timer_A control registers
            bic.w   #LPM0,0(SP)             ; Exit LPMx, interrupts enabled
            reti                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".int22"          ; Timer_A0 Vector
            .short  TIMERA0_ISR
            .sect 	".reset"	           ; MSP430 RESET Vector
            .short   RESET                   ;
            .end