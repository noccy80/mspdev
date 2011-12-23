;******************************************************************************
;   MSP-FET430P140 Demo - DAC12_0, Output Voltage Ramp on DAC0
;
;   Description: Using DAC12_0 and 2.5V ADC12REF reference with a gain of 1,
;   output positive ramp on P6.6. Normal mode is LPM0 with CPU off.  WDT used
;   to provide ~0.5ms interrupt used to wake up the CPU and update the DAC
;   with software. Use internal 2.5V Vref.
;   ACLK = n/a, SMCLK = MCLK = WDTCLK = default DCO ~ 800kHz.
;   ;* MSP430F169 Device Required *//
;
;                MSP430F169
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |        DAC0/P6.6|--> Ramp_positive
;            |                 |
;
;   M. Buccini / L. Westlund
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x16x.h"
;------------------------------------------------------------------------------
            .text                  ; Progam Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stackpointer
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
;------------------------------------------------------------------------------
TAX_ISR;    Common ISR for CCR0-4 and overflow
;------------------------------------------------------------------------------
            add.w   &TAIV,PC                ; Add TA interrupt offset to PC
            jmp     TACCR0_ISR              ; CCR0
            reti                            ; CCR1
            reti                            ; CCR2
            reti                            ; CCR3
            reti                            ; CCR4
TA_over     reti                            ; Timer_A overflow

TACCR0_ISR  clr     &TACTL                  ; clear Timer_A control registers
            bic     #LPM0,0(SP)             ; Exit LPMx, interrupts enabled
            reti                            ;
;------------------------------------------------------------------------------
;------------------------------------------------------------------------------
WDT_ISR  ;  Exit LPM0 on reti
;------------------------------------------------------------------------------
            bic.w   #CPUOFF,0(SP)           ; TOS = clear LPM0
            reti                            ;
                                            ;
;-----------------------------------------------------------------------------
;           Interrupt Vectors Used MSP430x15x/16x
;-----------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int10"                ; WDT Vector
            .short  WDT_ISR                 ;
            .sect   ".int06"                ; Timer_A0 Vector
            .short  TAX_ISR                 ;
            .end
