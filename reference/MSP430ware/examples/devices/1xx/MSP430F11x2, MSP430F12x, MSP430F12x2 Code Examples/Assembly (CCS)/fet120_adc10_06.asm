;******************************************************************************
;   MSP-FET430P120 Demo - ADC10, Output Internal Vref on P2.4 & ADCCLK on P1.0
;
;   Description: Output ADC10 internal VRef on P2.4, toggling between two
;   available options, 2.5V and 1.5V. ADC10OSC also output on P1.0.
;   //* MSP430F1232 or MSP430F1132 Device Required *//
;
;                MSP430F1232
;             ----------------
;         /|\|             XIN|-
;          | |                |
;          --|RST         XOUT|-
;            |                |
;            |   P1.0/ADC10CLK|--> ADC10OSC ~ 3.5MHz - 6.5MHz
;            |         P2.4/A4|--> Vref
;
;   M. Buccini / M. Raju
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x12x2.h"
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0300h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupADC10  mov.w   #CONSEQ_2,&ADC10CTL1    ; Repeat single channel
            mov.w   #REFOUT+REFON+MSC+ADC10ON,&ADC10CTL0; ADC10 and VRef
            mov.w   #30,&TACCR0             ; Delay to allow Ref to settle
            bis.w   #CCIE,&TACCTL0          ; Compare-mode interrupt.
            mov.w   #TACLR+MC_1+TASSEL_2,&TACTL; up mode, SMCLK
            bis.w   #LPM0+GIE,SR            ; Enter LPM0, enable interrupts
            bic.w   #CCIE,&TACCTL0          ; Disable timer interrupt
            dint                            ; Disable Interrupts
            bis.b   #010h,&ADC10AE          ; P2.4 = ADC10 option select
            bis.b   #001h,&P1DIR            ; P1.0 = output directon
            bis.b   #001h,&P1SEL            ; P1.0 = ADC10OSC option select
                                            ;
Mainloop    bic.w   #ENC,&ADC10CTL0         ; ADC10 disable
            xor.w   #REF2_5V,&ADC10CTL0     ; Toggle Vref 1.5/2.5V
            bis.w   #ENC+ADC10SC,&ADC10CTL0 ; ADC10 enable, start conversion
Delay       mov.w   #00Fh,R15               ; Long Delay
            mov.w   #0,R14                  ;
Delay_1     dec.w   R14                     ;
            sbc.w   R15                     ;
            jnz     Delay_1                 ;
            jmp     Mainloop                ;
                                            ;
;------------------------------------------------------------------------------
TA0_ISR;    ISR for CCR0
;------------------------------------------------------------------------------
            clr     &TACTL                  ; clear Timer_A control registers
            bic     #LPM0,0(SP)             ; Exit LPMx, interrupts enabled
            reti                            ;
;------------------------------------------------------------------------------
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int09"                ; Timer_A0 Vector
            .short  TA0_ISR                 ;
            .end