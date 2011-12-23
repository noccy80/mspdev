;******************************************************************************
;  MSP430F543xA Demo - ADC12_A, Repeated Single Channel Conversions
;
;  Description: This example shows how to perform repeated conversions on a
;  single channel using "repeat-single-channel" mode.  AVcc is used for the
;  reference and repeated conversions are performed on Channel A0. Each
;  conversion result is moved to an 8-element array called results[].  Test by
;  applying a voltage to channel A0, then running. Open a watch window in
;  debugger and view the results. Set Breakpoint1 in the index increment line
;  to see the array value change sequentially and Breakpoint to see the entire
;  array of conversion results in "results[]" for the specified Num_of_Results.
;  This can run even in LPM4 mode as ADC has its own clock (MODOSC)
;
;                MSP430F5438A
;             -----------------
;         /|\|                 |
;          | |                 |
;          --|RST              |
;            |                 |
;     Vin -->|P6.0/A0          |
;            |                 |
;
;
;   D. Dang
;   Texas Instruments Inc.
;   December 2009
;   Built with CCS Version: 4.0.2 
;******************************************************************************

    .cdecls C,LIST,"msp430x54xA.h"

;-------------------------------------------------------------------------------
;-------------------------------------------------------------------------------
            .bss    results,16 

;-------------------------------------------------------------------------------
            .global _main 
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x5C00,SP              ; Initialize stackpointer
            mov.w   #WDTPW + WDTHOLD,&WDTCTL; Stop WDT    
            clr.w   R4                      ; Clear the array index             
            bis.b   #0x01,&P6SEL            ; Enable A/D channel inputs            
            mov.w   #ADC12ON + ADC12MSC + ADC12SHT0_8,&ADC12CTL0
                                            ; Turn on ADC12, set sampling time
                                            ;  set multiple sample conversion
            mov.w   #ADC12SHP + ADC12CONSEQ_2,&ADC12CTL1  
                                            ; Use sampling timer, set mode
            mov.w   #0x01,&ADC12IE          ; Enabled ADC12IFG.0
            bis.w   #ADC12ENC,&ADC12CTL0    ; Enable conversions
            bis.w   #ADC12SC,&ADC12CTL0     ; Start conversion - sw trigger
            
            bis.w   #LPM4 + GIE,SR          ; Enter LPM0, enable interrupts
            nop                             ; Only for debugging purposes
                        
;-------------------------------------------------------------------------------
ADC12_ISR
;-------------------------------------------------------------------------------
            add.w   &ADC12IV,PC             ; Add offset to PC
            reti                            ; Vector 0:  No interrupt
            reti                            ; Vector 2:  ADC overflow
            reti                            ; Vector 4:  ADC timing overflow
            jmp     ADC12IFG0_HND           ; Vector 6:  ADC12IFG0
            reti                            ; Vector 8:  ADC12IFG1
            reti                            ; Vector 10: ADC12IFG2
            reti                            ; Vector 12: ADC12IFG3
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

ADC12IFG0_HND           
            rla.w   R4                      ; Index * 2 > indirect offset
            mov.w   &ADC12MEM0,0x1C00(R4)   ; Move A0 results, IFG is cleared
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