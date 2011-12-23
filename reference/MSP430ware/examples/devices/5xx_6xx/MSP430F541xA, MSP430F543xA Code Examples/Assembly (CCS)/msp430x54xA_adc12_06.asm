;******************************************************************************
;  MSP430F543xA Demo - ADC12_A, Repeated Sequence of Conversions
;
;  Description: This example shows how to perform a repeated sequence of
;  conversions using "repeat sequence-of-channels" mode.  AVcc is used for the
;  reference and repeated sequence of conversions is performed on Channels A0,
;  A1, A2, and A3. Each conversion result is stored in ADC12MEM0, ADC12MEM1,
;  ADC12MEM2, and ADC12MEM3 respectively. After each sequence, the 4 conversion
;  results are moved to A0results[], A1results[], A2results[], and A3results[].
;  Test by applying voltages to channels A0 - A3. Open a watch window in
;  debugger and view the results. Set Breakpoint1 in the index increment line
;  to see the array values change sequentially and Breakpoint2 to see the entire
;  array of conversion results in A0results[], A1results[], A2results[], and
;  A3results[]for the specified Num_of_Results.
;
;  Note that a sequence has no restrictions on which channels are converted.
;  For example, a valid sequence could be A0, A3, A2, A4, A2, A1, A0, and A7.
;  See the 5xx User's Guide for instructions on using the ADC12_A.
;
;               MSP430F5438A
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

            .bss    A0results,16 
            .bss    A1results,16 
            .bss    A2results,16 
            .bss    A3results,16 

;-------------------------------------------------------------------------------
            .global _main 
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x5C00,SP              ; Initialize stackpointer
            mov.w   #WDTPW + WDTHOLD,&WDTCTL; Stop WDT    
            clr.w   R4                      ; Clear the array index 
            mov.b   #0x0F,&P6SEL            ; Enable A/D channel inputs
            mov.w   #ADC12ON + ADC12MSC + ADC12SHT0_8,&ADC12CTL0
                                            ; Turn on ADC12, extend sampling time
                                            ;  to avoid overflow of results
            mov.w   #ADC12SHP + ADC12CONSEQ_3,&ADC12CTL1  
                                            ; Use sampling timer, repeated sequence
            mov.b   #ADC12INCH_0,&ADC12MCTL0; ref+=AVcc, channel = A0
            mov.b   #ADC12INCH_1,&ADC12MCTL1; ref+=AVcc, channel = A1
            mov.b   #ADC12INCH_2,&ADC12MCTL2; ref+=AVcc, channel = A2
            mov.b   #ADC12INCH_3 + ADC12EOS,&ADC12MCTL3
                                            ; ref+=AVcc, channel = A3, end seq.
            mov.w   #0x0008,&ADC12IE        ; Enabled ADC12IFG.3
            bis.w   #ADC12ENC,&ADC12CTL0    ; Enable conversions
            bis.w   #ADC12SC,&ADC12CTL0     ; Start conversion - sw trigger
            
            bis.w   #LPM0 + GIE,SR          ; Enter LPM0, enable interrupts
            nop                             ; Only for debugging purposes
                        
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
            rla.w   R4                      ; Index * 2 > indirect offset
            mov.w   &ADC12MEM0,0x1C00(R4)   ; Move A0 results, IFG is cleared
            mov.w   &ADC12MEM1,0x1C10(R4)   ; Move A1 results, IFG is cleared
            mov.w   &ADC12MEM2,0x1C20(R4)   ; Move A2 results, IFG is cleared
            mov.w   &ADC12MEM3,0x1C30(R4)   ; Move A3 results, IFG is cleared
            rra.w   R4                      ; Indirect offset / 2 > index 
            inc.w   R4                      ; Increment arr_index
            cmp.b   #0x08,R4                ; Is arr_index < 8 ? 
            jne     exit_isr                ;   yes -> Jump to exit_isr
            clr     R4                      ;   no  -> Clear arr_index
            nop                             ; Set breakpoint here 
exit_isr    reti                            ; Return from interrupt 
            
;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int55"                ; ADC12 isr vector
            .short  ADC12_ISR
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end