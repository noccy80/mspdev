;******************************************************************************
;  MSP-FET430P140 Demo - DMA0/1, ADC12 A10 Block Xfer to MPY/RAM, TBCCR1, DCO
;
;  Description: A 0x20 word block of data is sampled and recorded into RAM
;  from the ADC12 channel 10 the integrated temperature sensor using the
;  Record() function. Timer_B CCR1 begins the ADC12 sample period, CCR0 the hold
;  and conversion start. Timer_B operates in the up mode with CCR0 defining the
;  sample period.
;  DMA0 will automatically transfer each ADC12 conversion code to the HW MPY
;  which will preform MPY x 0x1000 - this will rotate the operand 12-bits to
;  the left. DMA1 uses the multiplier ready trigger to move the lower byte of
;  the upper operand of the multiplier result to a RAM block. At the end of the
;  transfer block, DMA1 issues and interrupt.
;  The purpose of this example is to show how multiple DMA triggers can be
;  combined.
;  P1.0 is toggled durring DMA transfer only for demonstration purposes.
;  ACLK = n/a, MCLK = SMCLK = default DCO ~ 800k
;  ;* Final Production MSP430F16x(x) Device Required *//
;
;               MSP430F169
;            -----------------
;        /|\|              XIN|-
;         | |                 |
;         --|RST          XOUT|-
;           |                 |
;           |A10          P1.0|-->LED
;
;
;   H. Grewal / A. Dannenberg
;   Texas Instruments Inc.
;   November 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x16x.h"
;------------------------------------------------------------------------------
            .text                  ; Progam Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
            bis.b   #01h,&P1DIR             ; Set P1.0 to output direction
Mainloop    call    #record
            nop                             ; Needed only for debugger
            jmp     Mainloop
record      mov.b   #SREF_1+INCH_10,&ADC12MCTL0 ; Channel A10, Vref+
            mov.w   #0h,&ADC12IFG
            mov.w   #SHS_3+CONSEQ_2,&ADC12CTL1 ; S&H TB.OUT1, rep. single chan
            mov.w   #REF2_5V+REFON+ADC12ON+ENC,&ADC12CTL0 ; VRef ADC12 on, enabled
            mov.w   #03600h,R15             ; Delay for needed ref start-up.
L$1         dec.w   R15                     ; See datasheet for details.
            jnz     L$1                     ;
            mov.w   #100,&TBCCR0            ; Init TBCCR0 w/ sample prd
            mov.w   #70,&TBCCR1             ; Trigger for ADC12 SC
            mov.w   #OUTMOD_7,&TBCCTL1      ; Reset OUT1 on EQU1, set on EQU0
SetupDMAx   mov.w   #DMA1TSEL_11+DMA0TSEL_6,&DMACTL0 ; DMA1=MPY Ready, DMA0=ADC12IFGx
            mov.w   #ADC12MEM0, &DMA0SA     ; Src address = ADC12 module
            mov.w   #OP2, &DMA0DA           ; Dst address = multiplier
            mov.w   #01h,&DMA0SZ            ; Size in words
            mov.w   #DMADT_4+DMAEN,&DMA0CTL ; Sng rpt, config
            mov.w   #RESHI, &DMA1SA         ; Src address = multiplier
            mov.w   #0220h,&DMA1DA          ; Dst address = RAM memory
            mov.w   #020h,&DMA1SZ           ; Size in words
            mov.w   #DMADSTINCR_3+DMASBDB+DMAIE+DMAEN,&DMA1CTL ; Sng, config
            mov.w   #1000h,&MPY             ; MPY first operand
            bis.b   #01h,&P1OUT             ; Start recording and enter LPM0
            mov.w   #TBSSEL_2+MC_1+TBCLR,&TBCTL ;SMCLK, clear TBR, up mode
            bis.b   #CPUOFF+GIE,SR          ; Enter LPM0, enable interrupts
            bic.w   #CONSEQ_2,&ADC12CTL1    ; Stop conversion immediately
            bic.w   #ENC,&ADC12CTL0         ; Disable ADC12 conversion
            mov.w   #0h, &ADC12CTL0         ; Switch off ADC12 & ref voltage
            mov.w   #0h, &TBCTL             ; Disable Timer_B
            bic.b   #01h,&P1OUT             ; Clear P1.0 (LED Off)
            ret
;------------------------------------------------------------------------------
DMA_ISR;    Common ISR for DMA/DAC12
;------------------------------------------------------------------------------
            bic.w   #DMAIFG,&DMA1CTL        ; Clear DMA1 interrupt flag
            bic.w   #LPM0,0(SP)             ; Exit LPMx, interrupts enabled
            reti                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; POR, ext. Reset, Watchdog, Flash
            .short  RESET                   ;
            .sect   ".int00"                ; DMA Vector
            .short  DMA_ISR                 ;
            .end

