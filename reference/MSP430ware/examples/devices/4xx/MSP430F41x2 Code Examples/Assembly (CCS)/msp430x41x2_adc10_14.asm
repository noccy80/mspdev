;*******************************************************************************
;   MSP430F41x2 Demo - ADC10, DTC Sample A1-0 32x, AVcc, Repeat Seq, DCO
;
;   Description: Use DTC to sample A1/A0 repeat sequence 32x(64 total samples)
;   with reference to AVcc.  Software sets ADC10SC to trigger sample burst.
;   In Mainloop MSP430 waits in LPM0 to save power until ADC10 conversion
;   complete, ADC10_ISR will force exit from LPM0 in Mainloop on reti.
;   ADC10 internal oscillator times sample period (16x) and conversion (13x).
;   DTC transfers conversion code to RAM 200h - 280h.  ADC10(DTC) interrupt
;   will return system active. P5.1 set at start of conversion burst, reset
;   on completion.
;
;                MSP430F41x2
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;        >---|P7.5/A1      P5.1|-->LED
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
SetupADC10  mov.w   #INCH_1+CONSEQ_3,&ADC10CTL1 ; A1/A0, repeat multi channel
            mov.w   #ADC10SHT_2+MSC+ADC10ON+ADC10IE,&ADC10CTL0 ;
            bis.b   #03h,&ADC10AE0          ; P7.4,5 ADC option select
            mov.b   #040h,&ADC10DTC1        ; 64 conversions
SetupP1     bis.b   #002h,&P5DIR            ; P5.1 output
                                            ;
Mainloop    bis.b   #002h,&P5OUT            ; P5.1 = 1
busy_test   bit     #BUSY,&ADC10CTL1        ; ADC10 core inactive?
            jnz     busy_test               ;
            mov.w   #0200h,&ADC10SA         ; Data buffer start
            bis.w   #ENC+ADC10SC,&ADC10CTL0 ; Start sampling
            bis.w   #CPUOFF+GIE,SR          ; CPU off, Enable interrupts
            bic.b   #002h,&P5OUT            ; P5.1 = 0
            jmp     Mainloop                ; Again
                                            ;
;-------------------------------------------------------------------------------
ADC10_ISR;
;-------------------------------------------------------------------------------
            bic.w   #ENC,&ADC10CTL0         ; ADC10 disabled
            bic.w   #LPM0,0(SP)             ; Exit LPM0 on reti
            reti                            ;
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int07"            	; ADC10 Vector
            .short  ADC10_ISR
            .sect	".reset"	            ; POR, ext. Reset
            .short	RESET
            .end
