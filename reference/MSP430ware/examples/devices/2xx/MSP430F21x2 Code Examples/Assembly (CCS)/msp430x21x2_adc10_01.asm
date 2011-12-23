;*******************************************************************************
;   MSP430F21x2 Demo - ADC10, Sample A0, AVcc Ref, Set P1.0 if A0 > 0.5*AVcc
;
;   Description: A single sample is made on A0 with reference to AVcc.
;   Software sets ADC10SC to start sample and conversion - ADC10SC
;   automatically cleared at EOC. ADC10 internal oscillator times sample (16x)
;   and conversion. In Mainloop MSP430 waits in LPM0 to save power until ADC10
;   conversion complete, ADC10_ISR will force exit from LPM0 in Mainloop on
;   reti. If A0 > 0.5*AVcc, P1.0 set, else reset.
;
;                MSP430F21x2
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;        >---|P2.0/A0      P1.0|--> LED
;
;  JL Bile
;  Texas Instruments Inc.
;  May 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x21x2.h"
;-------------------------------------------------------------------------------
	.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #025Fh,SP         ; Initialize stackpointer (allocate 160B) 
									  ; min RAM for device 256B (02FFh-200h)
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupADC10  mov.w   #ADC10SHT_2+ADC10ON+ADC10IE,&ADC10CTL0 ; 16x, enable int.
            bis.b   #01h,&ADC10AE0          ; P2.0 ADC10 option select

SetupP2     bis.b   #01h,&P2SEL             ; P2.0 ADC10 option select *M:Seaman*

SetupP1     bis.b   #001h,&P1DIR            ; P1.0 output
                                            ;
Mainloop    bis.w   #ENC+ADC10SC,&ADC10CTL0 ; Start sampling/conversion
            bis.w   #CPUOFF+GIE,SR          ; LPM0, ADC10_ISR will force exit
            bic.b   #01h,&P1OUT             ; P1.0 = 0
            cmp.w   #01FFh,&ADC10MEM        ; ADC10MEM = A0 > 0.5AVcc?
            jlo     Mainloop                ; Again
            bis.b   #01h,&P1OUT             ; P1.0 = 1
            jmp     Mainloop                ; Again
                                            ;
;-------------------------------------------------------------------------------
ADC10_ISR;  Exit LPM0 on reti
;-------------------------------------------------------------------------------
            bic.w   #CPUOFF,0(SP)           ; Exit LPM0 on reti
            reti                            ;
                                            ;
;-------------------------------------------------------------------------------
; 			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect     ".int05"            ; ADC10 Vector
            .short   ADC10_ISR
            .sect    ".reset"            ; POR, ext. Reset
            .short   RESET
            .end
