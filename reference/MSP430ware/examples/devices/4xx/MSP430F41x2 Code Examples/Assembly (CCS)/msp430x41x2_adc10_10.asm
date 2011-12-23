;*******************************************************************************
;   MSP430F41x2 Demo - ADC10, DTC Sample A2-0, AVcc, Single Sequence, DCO
;
;   Description: Sample A2/A1/A0 as single sequence with reference to AVcc.
;   Software sets ADC10SC to trigger sample sequence. In Mainloop MSP430 waits
;   in LPM0 to save power until ADC10 conversion complete, ADC10_ISR(DTC) will
;   force exit from any LPMx in Mainloop on reti. ADC10 internal oscillator 
;   times sample period (16x) and conversion(13x). 
;   DTC transfers conversion code to RAM 200h - 206h. P5.1 set at start
;   of conversion burst, reset on completion.
;
;                MSP430F41x2
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;        >---|P6.0/A2      P5.1|-->LED
;        >---|P7.5/A1          |
;        >---|P7.4/A0          |
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
SetupADC10  mov.w   #INCH_2+CONSEQ_1,&ADC10CTL1 ; A2/A1/A0, single sequence
            mov.w   #ADC10SHT_2+MSC+ADC10ON+ADC10IE,&ADC10CTL0 ;
            bis.b   #07h,&ADC10AE0          ; P6.0,7.5,7.4 ADC10 option selects
            mov.b   #03h,&ADC10DTC1         ; 3 conversions
SetupP5     bis.b   #002h,&P5DIR            ; P5.1 output
                                            ;
Mainloop    bic.w   #ENC,&ADC10CTL0         ; Enable ADC conversion
busy_test   bit     #BUSY,&ADC10CTL1        ; ADC10 core inactive?
            jnz     busy_test               ;
            mov.w   #0200h,&ADC10SA         ; Data buffer start
            bis.b   #002h,&P5OUT            ; P5.1 = 0
            bis.w   #ENC+ADC10SC,&ADC10CTL0 ; Start sampling
            bis.w   #CPUOFF+GIE,SR          ; LPM0, ADC10_ISR will force exit
            bic.b   #002h,&P5OUT            ; P5.1 = 1
            jmp     Mainloop                ; Again
                                            ;
;-------------------------------------------------------------------------------
ADC10_ISR;  Exit LPM0 on reti
;-------------------------------------------------------------------------------
            bic.w   #CPUOFF,0(SP)           ; Exit LPM0 on reti
            reti                            ;
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int07"            	; ADC10 Vector
            .short  ADC10_ISR
            .sect	".reset"	            ; POR, ext. Reset
            .short      RESET
            .end
