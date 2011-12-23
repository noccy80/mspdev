;*******************************************************************************
;   MSP430F41x2 Demo - ADC10, Sample A11, Lo_Batt, Set P5.1 if AVcc < 2.3V
;
;   Description: A single sample is made on A11 (AVcc/2) with reference to
;   internal 1.5V Vref. Software sets ADC10SC to start sample and conversion
;   - ADC10SC automatically cleared at EOC. ADC10 internal oscillator times
;   sample (16x) and conversion. ADC10BUSY flag is polled for EOC. If A11
;   (AVcc/2) < 0311h (1.15V) indicating AVcc is less 2.3V, P5.1 set indicating
;   a lo_Batt condition, else reset.
;
;                  MSP430F41x2
;             --------------------
;         /|\|                 XIN|-
;          | |                    |
;          --|RST             XOUT|-
;            |                    |
;            |A11 (AVcc/2)   P5.1 |--> LED
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
SetupADC10  mov.w   #INCH_11,&ADC10CTL1     ; AVcc/2
            mov.w   #SREF_1+ADC10SHT_2+REFON+ADC10ON,&ADC10CTL0;
            mov.w   #30,&TACCR0             ; Delay to allow Ref to settle
            bis.w   #CCIE,&TACCTL0          ; Compare-mode interrupt.
            mov.w   #TACLR+MC_1+TASSEL_2,&TACTL; up mode, SMCLK
            bis.w   #LPM0+GIE,SR            ; Enter LPM0, enable interrupts
            bic.w   #CCIE,&TACCTL0          ; Disable timer interrupt
SetupP1     bis.b   #002h,&P5DIR            ; P5.1 output
                                            ;
Mainloop    bis.w   #ENC+ADC10SC,&ADC10CTL0 ; Start sampling/conversion
L1          bit.w   #ADC10BUSY,&ADC10CTL1   ; ADC10BUSY?
            jnz     L1                      ;
            cmp.w   #0311h,&ADC10MEM        ; ADC10MEM = A11 (AVcc/2) > 1.15V? 
            jlo     lo_Batt                 ;
            bic.b   #02h,&P5OUT             ; P5.1 = 0
            jmp     Mainloop                ; Again
lo_Batt     bis.b   #02h,&P5OUT             ; P5.1 = 1
            jmp     Mainloop                ; Again
                                            ;
;-------------------------------------------------------------------------------
TA0_ISR;    ISR for TACCR0
;-------------------------------------------------------------------------------
            clr.w   &TACTL                  ; Clear Timer_A control registers
            bic.w   #LPM0,0(SP)             ; Exit LPM0 on reti
            reti                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int06"          		; Timer_A0 Vector
            .short  TA0_ISR
            .sect	".reset"                ; POR, ext. Reset
            .short  RESET
            .end
