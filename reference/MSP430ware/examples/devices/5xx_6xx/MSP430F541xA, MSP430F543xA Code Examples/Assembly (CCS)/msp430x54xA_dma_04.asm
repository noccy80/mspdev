;******************************************************************************
;  MSP430F543xA Demo - DMA0, Single transfer using ADC12 triggered by TimerB
;
;  Description: This software uses TBCCR1 as a sample and convert input into
;  the A0 of ADC12. ADC12IFG is used to trigger a DMA transfer and DMA
;  interrupt triggers when DMA transfer is done. TB1 is set as an output and
;  P1.0 is toggled when DMA ISR is serviced.
;  ACLK = REFO = 32kHz, MCLK = SMCLK = default DCO 1048576Hz
;
;                 MSP430F5438A
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |             P1.0|-->LED
;            |             P4.1|-->TB1 output
;            |                 |
;            |             P6.0|<--A0
;
;   D. Dang
;   Texas Instruments Inc.
;   December 2009
;   Built with CCS Version: 4.0.2 and IAR Embedded Workbench Version: 4.11B
;******************************************************************************

    .cdecls C,LIST,"msp430x54xA.h"

;-------------------------------------------------------------------------------
            .bss    DMA_DST,2 
;-------------------------------------------------------------------------------
            .global _main 
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x5C00,SP              ; Initialize SP
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Hold WDT

SetupP1     bic.b   #BIT0,&P1OUT            ; P1.0 clear
            bis.b   #BIT0,&P1DIR            ; P1.0 output
SetupP4     bis.b   #BIT1,&P4DIR            ; P4.1 output
            bis.b   #BIT1,&P4SEL            ; P4.1 select

SetupTimerB mov.w   #0xFFFE,TBCCR0
            mov.w   #0x8000,&TBCCR1
            mov.w   #OUTMOD_3,&TBCCTL1      ; CCR1 set/reset mode
            mov.w   #TBSSEL_2+MC_1+TBCLR,&TBCTL ; SMCLK, Up-Mode

SetupADC12  mov.w   #ADC12SHT0_15+ADC12MSC+ADC12ON,&ADC12CTL0
                                            ; Sampling time, MSC, ADC12 on
            mov.w   #ADC12SHS_3+ADC12CONSEQ_2,&ADC12CTL1
                                            ; Use sampling timer; ADC12MEM0
                                            ; Sample-and-hold source = CCI0B =
                                            ; TBCCR1 output
                                            ; Repeated-single-channel
            mov.b   #ADC12SREF_0+ADC12INCH_0,&ADC12MCTL0
                                            ; V+=AVcc V-=AVss, A0 channel
            bis.w   #ADC12ENC,&ADC12CTL0

SetupDMA0   mov.w   #DMA0TSEL_24,&DMACTL0   ; ADC12IFGx triggered
            mov.w   #DMARMWDIS,&DMACTL4     ; Read-modify-write disable
            bic.w	#DMAIFG,&DMA0CTL
;           
            mov.w   #DMADT_4+DMAEN+DMADSTINCR_3+DMAIE,&DMA0CTL
                                            ; Rpt single tranfer, inc dst, Int
            mov.w   #0x0001,&DMA0SZ         ; DMA0 size = 1
            movx.a  #ADC12MEM0,&DMA0SA      ; ... from ADC12MEM0
            movx.a  #DMA_DST,&DMA0DA        ; ... to destination in RAM 

            bis.w   #LPM0 + GIE,SR          ; LPM0 w/ interrupts
            nop                             ; used for debugging

;-------------------------------------------------------------------------------
DMA_ISR ;   DMA Interrupt Service Routine
;-------------------------------------------------------------------------------
            add     &DMAIV,PC
            reti
            jmp     DMA0_HND
            reti
            reti
            reti
            reti
            reti
            reti
            reti
DMA0_HND
            xor.b   #BIT0,&P1OUT            ; Toggle P1.0
            reti
;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int50"                  ; DMA isr vector
            .short  DMA_ISR
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end