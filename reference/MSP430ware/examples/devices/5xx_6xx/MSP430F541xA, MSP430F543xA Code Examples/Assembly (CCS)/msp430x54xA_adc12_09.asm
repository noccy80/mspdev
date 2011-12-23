;******************************************************************************
;  MSP430F543xA Demo - ADC12_A, Sequence of Conversions (non-repeated)
;
;  Description: This example shows how to perform A/D conversions on a sequence
;  of channels. A single sequence of conversions is performed - one conversion
;  each on channels A0, A1, A2, and A3. Each conversion uses AVcc and AVss for
;  the references. The conversion results are stored in ADC12MEM0, ADC12MEM1,
;  ADC12MEM2, and ADC12MEM3 respectively and are moved to 'results[]' upon
;  completion of the sequence. Test by applying voltages to pins A0, A1, A2,
;  and A3, then setting and running to a break point at the nop
;  instruction in the while_loop. To view the conversion results, open a watch window
;  in debugger and view 'results' or view ADC12MEM0, ADC12MEM1, ADC12MEM2, and
;  ADC12MEM3 in an ADC12 SFR window.
;  This can run even in LPM4 mode as ADC has its own clock
;  Note that a sequence has no restrictions on which channels are converted.
;  For example, a valid sequence could be A0, A3, A2, A4, A2, A1, A0, and A7.
;  See the 5xx User's Guide for instructions on using the ADC12.
;
;                MSP430F5438A
;             -----------------
;         /|\|                 |
;          | |                 |
;          --|RST              |
;            |                 |
;    Vin0 -->|P6.0/A0          |
;    Vin1 -->|P6.1/A1          |
;    Vin2 -->|P6.2/A2          |
;    Vin3 -->|P6.3/A3          |
;            |                 |
;
;   D. Dang
;   Texas Instruments Inc.
;   December 2009
;   Built with CCS Version: 4.0.2 and IAR Embedded Workbench Version: 4.11B
;******************************************************************************
    .cdecls C,LIST,"msp430x54xA.h"

;-------------------------------------------------------------------------------
;-------------------------------------------------------------------------------
            .bss    results,8 

;-------------------------------------------------------------------------------
            .global _main 
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x5C00,SP              ; Initialize stackpointer
            mov.w   #WDTPW + WDTHOLD,&WDTCTL; Stop WDT    
            mov.b   #0x0F,&P6SEL            ; Enable A/D channel inputs
            mov.w   #ADC12ON + ADC12MSC + ADC12SHT0_2,&ADC12CTL0
                                            ; Turn on ADC12, extend sampling time
            mov.w   #ADC12SHP + ADC12CONSEQ_1,&ADC12CTL1  
                                            ; Use sampling timer, single sequence
            mov.b   #ADC12INCH_0,&ADC12MCTL0; ref+=AVcc, channel = A0
            mov.b   #ADC12INCH_1,&ADC12MCTL1; ref+=AVcc, channel = A1
            mov.b   #ADC12INCH_2,&ADC12MCTL2; ref+=AVcc, channel = A2
            mov.b   #ADC12INCH_3 + ADC12EOS,&ADC12MCTL3
                                            ; ref+=AVcc, channel = A3, end seq.
            mov.w   #0x0008,&ADC12IE        ; Enabled ADC12IFG.3
            bis.w   #ADC12ENC,&ADC12CTL0    ; Enable conversions

while_loop  bis.w   #ADC12SC,&ADC12CTL0     ; Start conversion - sw trigger
            
            bis.w   #LPM4 + GIE,SR          ; Enter low power mode, enable interrupts
            nop                             ; Only for debugging purposes
            
            jmp     while_loop
            
;-------------------------------------------------------------------------------
ADC12_ISR
;-------------------------------------------------------------------------------
            add.w   &ADC12IV,PC             ; Add offset to PC
            reti                            ; Vector 0:  No interrupt
            reti                            ; Vector 2:  ADC overflow
            reti                            ; Vector 4:  ADC timing overflow
            reti                            ; Vector 6:  ADC12IFG0
            reti                            ; Vector 8:  ADC12IFG1
            reti                            ; Vector 10: ADC12IFG2
            jmp     ADC12IFG3_HND           ; Vector 12: ADC12IFG3
            reti                            ; Vector 14: ADC12IFG4
            reti                            ; Vector 16: ADC12IFG5
            reti                            ; Vector 18: ADC12IFG6
            reti                            ; Vector 20: ADC12IFG7
            reti                            ; Vector 22: ADC12IFG8
            reti                            ; Vector 24: ADC12IFG9
            reti                            ; Vector 26: ADC12IFG10
            reti                            ; Vector 28: ADC12IFG11
            reti                            ; Vector 30: ADC12IFG12
            reti                            ; Vector 32: ADC12IFG13
            reti                            ; Vector 34: ADC12IFG14

ADC12IFG3_HND           
            clr.w   R4                      ; Clear array index 
            mov.w   &ADC12MEM0,0x1C00(R4)   ; Move A0 results, IFG is cleared
            incd.w  R4                      ;   Array_index += 2
            mov.w   &ADC12MEM1,0x1C00(R4)   ; Move A1 results, IFG is cleared
            incd.w  R4                      ;   Array_index += 2
            mov.w   &ADC12MEM2,0x1C00(R4)   ; Move A2 results, IFG is cleared
            incd.w  R4                      ;   Array_index += 2
            mov.w   &ADC12MEM3,0x1C00(R4)   ; Move A3 results, IFG is cleared
            bic.w   #LPM4,0(SP)             ; Exit active from ISR; SET BKPT HERE
            reti                            ; Return from interrupt 
            
;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int55"                ; ADC12 isr vector
            .short  ADC12_ISR
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end