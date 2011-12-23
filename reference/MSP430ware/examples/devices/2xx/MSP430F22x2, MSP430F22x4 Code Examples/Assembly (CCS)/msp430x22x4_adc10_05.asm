;*******************************************************************************
;   MSP430F22x4 Demo - ADC10, Sample A11, Lo_Batt, Set P1.0 if AVcc < 2.3V
;
;   Description: A single sample is made on A11 (AVcc/2) with reference to
;   internal 1.5V Vref. Software sets ADC10SC to start sample and conversion
;   - ADC10SC automatically cleared at EOC. ADC10 internal oscillator times
;   sample (16x) and conversion. ADC10BUSY flag is polled for EOC. If A11
;   (AVcc/2) < 0311h (1.15V) indicating AVcc is less 2.3V, P1.0 set indicating
;   a lo_Batt condition, else reset.
;
;                  MSP430F22x4
;             --------------------
;         /|\|                 XIN|-
;          | |                    |
;          --|RST             XOUT|-
;            |                    |
;            |A11 (AVcc/2)   P1.0 |--> LED
;
;  P.Thanigai
;  Texas Instruments Inc.
;  August 2007
;  Built with Code Composer Essentials Version: 2.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430x22x4.h"
                              
;------------------------------------------------------------------------------
            .text                  			; Program reset
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupADC10  mov.w   #INCH_11,&ADC10CTL1     ; AVcc/2
            mov.w   #SREF_1+ADC10SHT_2+REFON+ADC10ON,&ADC10CTL0;
            mov.w   #30,&TACCR0             ; Delay to allow Ref to settle
            bis.w   #CCIE,&TACCTL0          ; Compare-mode interrupt.
            mov.w   #TACLR+MC_1+TASSEL_2,&TACTL; up mode, SMCLK
            bis.w   #LPM0+GIE,SR            ; Enter LPM0, enable interrupts
            bic.w   #CCIE,&TACCTL0          ; Disable timer interrupt
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 output
                                            ;
Mainloop    bis.w   #ENC+ADC10SC,&ADC10CTL0 ; Start sampling/conversion
L1          bit.w   #ADC10BUSY,&ADC10CTL1   ; ADC10BUSY?
            jnz     L1                      ;
            cmp.w   #0311h,&ADC10MEM        ; ADC10MEM = A11 (AVcc/2) > 1.15V?
            jlo     lo_Batt                 ;
            bic.b   #01h,&P1OUT             ; P1.0 = 0
            jmp     Mainloop                ; Again
lo_Batt     bis.b   #01h,&P1OUT             ; P1.0 = 1
            jmp     Mainloop                ; Again
                                            ;
;-------------------------------------------------------------------------------
TA0_ISR;    ISR for TACCR0
;-------------------------------------------------------------------------------
            clr.w   &TACTL                  ; Clear Timer_A control registers
            bic.w   #LPM0,0(SP)             ; Exit LPM0 on reti
            reti                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int09"                ; Timer_A0 Vector
            .short  TA0_ISR                 ;
            .end
