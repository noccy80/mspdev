;*******************************************************************************
;   MSP430x261x Demo - DAC12_1, Output 2.0V on DAC1
;
;   Description: Using DAC12_1 and 2.5V ADC12REF reference with a gain of 1,
;   output 2V on P6.7.
;
;                
;                MSP430F261x
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |        DAC1/P6.7|--> 2V
;            |                 |
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
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupADC12  mov.w   #REF2_5V+REFON,&ADC12CTL0  ; Internal 2.5V ref on
            mov.w   #13600,&TACCR0          ; Delay to allow Ref to settle
            bis.w   #CCIE,&TACCTL0          ; Compare-mode interrupt.
            mov.w   #TACLR+MC_1+TASSEL_2,&TACTL; up mode, SMCLK
            bis.w   #LPM0+GIE,SR            ; Enter LPM0, enable interrupts
            bic.w   #CCIE,&TACCTL0          ; Disable timer interrupt
            dint                            ; Disable Interrupts
SetupDAC12  mov.w   #DAC12IR+DAC12AMP_5+DAC12ENC,&DAC12_1CTL ; Int ref gain 1
            mov.w   #0CCCh,&DAC12_1DAT      ; 2.0V
                                            ;
Mainloop    bis.w   #CPUOFF,SR              ; Enter LPM0
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
            .sect	".int25"          ; Timer_A0 Vector
            .short	TIMERA0_ISR
            .sect	".reset"            ; POR, ext. Reset
            .short	RESET
            .end
