;*******************************************************************************
;   MSP430x261x Demo - DAC12_0, Output Voltage Ramp on DAC0
;
;   Description: Using DAC12_0 and 2.5V ADC12REF reference with a gain of 1,
;   output positive ramp on P6.6. Normal mode is LPM0 with CPU off.  WDT used
;   to provide ~0.5ms interrupt used to wake up the CPU and update the DAC
;   with software. Use internal 2.5V Vref.
;   ACLK = 32kHz, SMCLK = MCLK = WDTCLK = default DCO 1048576Hz
;
;                
;                MSP430F261x
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |        DAC0/P6.6|--> Ramp_positive
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
SetupWDT    mov.w   #WDT_MDLY_0_064,&WDTCTL   ; WDT ~0.064ms interval timer
            bis.b   #WDTIE,&IE1             ; Enable WDT interrupt
SetupADC12  mov.w   #REF2_5V+REFON,&ADC12CTL0 ; Internal 2.5V ref on
            mov.w   #13600,&TACCR0          ; Delay to allow Ref to settle
            bis.w   #CCIE,&TACCTL0          ; Compare-mode interrupt.
            mov.w   #TACLR+MC_1+TASSEL_2,&TACTL; up mode, SMCLK
            bis.w   #LPM0+GIE,SR            ; Enter LPM0, enable interrupts
            bic.w   #CCIE,&TACCTL0          ; Disable timer interrupt
            dint                            ; Disable Interrupts
SetupDAC120 mov.w   #DAC12IR+DAC12AMP_5+DAC12ENC,&DAC12_0CTL ; Int ref gain 1
                                            ;
Mainloop    bis.w   #CPUOFF+GIE,SR          ; Enter LPM0, interrupts enabled
            inc.w   &DAC12_0DAT             ; Positive ramp
            and.w   #0FFFh,&DAC12_0DAT      ;
            jmp     Mainloop                ;
                                            ;
;-------------------------------------------------------------------------------
TIMERA0_ISR;
;-------------------------------------------------------------------------------
            clr.w   &TACTL                  ; Clear Timer_A control registers
            bic.w   #LPM0,0(SP)             ; Exit LPMx, interrupts enabled
            reti                            ;
;-------------------------------------------------------------------------------
WDT_ISR;    Exit LPM0 on reti
;-------------------------------------------------------------------------------
            bic.w   #CPUOFF,0(SP)           ; TOS = clear LPM0
            reti                            ;
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".int25"          ; Timer_A0 Vector
            .short	TIMERA0_ISR
            .sect	".int26"              ; WDT Vector
            .short   WDT_ISR
            .sect	".reset"            ; POR, ext. Reset
            .short	RESET
            .end
 