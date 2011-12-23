;******************************************************************************
;   MSP-FET430P140 Demo - DAC12_0, Output 1.0V on DAC0
;
;   Description: Using DAC12_0 and 2.5V ADC12REF reference with a gain of 1,
;   ouput 1V on P6.6.
;   ;* MSP430F169 Device Required *//
;
;                MSP430F169
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |        DAC0/P6.6|--> 1V
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
Mainloop    bis.w   #CPUOFF,SR              ; Enter LPM0
            nop                             ; Required only for debugger
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
;           Interrupt Vectors Used MSP430x15x/16x
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int06"                ; Timer_A0 Vector
            .short  TAX_ISR                 ;
            .end
