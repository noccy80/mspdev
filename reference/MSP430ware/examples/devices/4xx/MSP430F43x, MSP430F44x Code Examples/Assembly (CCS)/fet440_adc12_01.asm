;******************************************************************************
;   MSP-FET430P440 Demo - ADC12, Sample A0, .set P5.1 if A0 > 0.5*AVcc
;
;   Description: A single sample is made on A0 with reference to AVcc.
;   Software sets ADC12SC to start sample and conversion - ADC12SC
;   automatically cleared at EOC. ADC12 internal oscillator times sample (16x)
;   and conversion. In Mainloop MSP430 waits in LPM0 to save power until ADC12
;   conversion complete, ADC12_ISR will force exit from LPM0 in Mainloop on
;   reti. If A0 > 0.5*AVcc P5.1 set, else reset.
;   ACLK = n/a, MCLK = SMCLK = default DCO, ADC12CLK = ADC12OSC
;
;
;                 MSP430F449
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;     Vin -->|P6.0/A0      P5.1|--> LED
;
;   M. Buccini / A. Dannenberg
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x44x.h"
;------------------------------------------------------------------------------
            .text              			    ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupADC12  mov.w   #SHT0_2+ADC12ON,&ADC12CTL0     ; Sampling time, ADC12 on
            mov.w   #SHP,&ADC12CTL1         ; Use sampling timer
            mov.w   #01h,&ADC12IE           ; Enable interrupt
            bis.w   #ENC,&ADC12CTL0         ;
            bis.b   #01h,&P6SEL             ; P6.0 ADC option select
            bis.b   #02h,&P5DIR             ; P5.1 output
                                            ;
Mainloop    bis.w   #ADC12SC,&ADC12CTL0     ; Start sampling/conversion
            bis.w   #CPUOFF+GIE,SR          ; LPM0, ADC12_ISR will force exit
            jmp     Mainloop                ; Again
                                            ;
;------------------------------------------------------------------------------
ADC12_ISR;  Exit any LPMx on reti
;------------------------------------------------------------------------------
            bic.b   #02h,&P5OUT             ; P5.1 = 0
            cmp.w   #07FFh,&ADC12MEM0       ; ADC12MEM = A0 > 0.5AVcc?
            jlo     ADC12_ISR_1             ;
            bis.b   #02h,&P5OUT             ; P5.1 = 1
ADC12_ISR_1 bic.w   #CPUOFF,0(SP)           ; Exit any LPM0 on reti
            reti                            ;		
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; RESET Vector
            .short  RESET                   ;
            .sect   ".int07"                ; ADC12 Vector
            .short  ADC12_ISR               ;
            .end
