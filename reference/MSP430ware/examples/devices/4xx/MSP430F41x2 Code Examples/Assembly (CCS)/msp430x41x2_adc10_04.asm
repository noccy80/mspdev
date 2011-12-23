;*******************************************************************************
;   MSP430F41x2 Demo - ADC10, Sample A0, Signed, Set P5.1 if A0 > 0.5*AVcc
;
;   Description: A single sample is made on A0 with SIGNED reference to AVcc.
;   Software sets ADC10SC to start sample and conversion - ADC10SC
;   automatically cleared at EOC. ADC10 internal oscillator times sample (16x)
;   and conversion. In Mainloop MSP430 waits in LPM0 to save power until ADC10
;   conversion complete, ADC10_ISR will force exit from LPM0 in Mainloop on
;   reti. If A0 > 0.5*AVcc, P5.1 set, else reset.
;
;                MSP430F41x2
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;        >---|P7.4/A0      P5.1|--> LED
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
SetupADC10  mov.w   #ADC10DF,&ADC10CTL1     ; Conversion code singed format
            mov.w   #ADC10SHT_2+ADC10ON+ADC10IE,&ADC10CTL0 ; 16x, enable int.
            bis.b   #01h,&ADC10AE0          ; P2.0 ADC10 option select
SetupP5     bis.b   #002h,&P5DIR            ; P5.1 output
                                            ;
Mainloop    bis.w   #ENC+ADC10SC,&ADC10CTL0 ; Sampling and conversion start
            bis.w   #CPUOFF+GIE,SR          ; LPM0, ADC10_ISR will force exit
            bic.b   #02h,&P5OUT             ; P5.1 = 0
            tst.w   &ADC10MEM               ; ADC10MEM = A0 > 0.5AVcc?
            jl      Mainloop                ; Again
            bis.b   #02h,&P5OUT             ; P5.0 = 1
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
            .sect	".reset"				; POR, ext. Reset
            .short	RESET
            .end
