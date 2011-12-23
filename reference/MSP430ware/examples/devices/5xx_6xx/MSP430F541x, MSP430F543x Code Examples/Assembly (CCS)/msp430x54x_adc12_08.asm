;******************************************************************************
;  MSP430F54x Demo - ADC12, Using A8 and A9 Ext Channels for Conversion
;
;  Description: This example shows how to perform A/D conversion on up to 10
;  external channels by showing that channels A8 and A9 can be used for
;  conversion of external signals when not using these channels as external
;  reference inputs. A single sequence of conversions is performed - one
;  conversion on A8 and then one conversion on A9. Each conversion uses AVcc
;  and AVss for the references. The conversion results are stored in ADC12MEM0
;  and ADC12MEM1 respectively and are moved to 'results[]' upon completion of
;  the sequence.
;  Test by applying voltages to pins VeREF+ for A8 and VREF-/VeREF- for A9,
;  then setting and running to a break point at the "_BIC..." instruction in
;  the ISR. To view the conversion results, open a watch window in debugger and
;  view 'results' or view ADC12MEM0 and ADC12MEM1 in an ADC12 SFR window.
;  This can run even in LPM4 mode as ADC has its own clock
;  *NOTE*  When using channels A8 and A9 for external signals, internal
;  references must be used for the conversions. Refer to figure 18-1 in the
;  MSP430x5xx Family User's Guide.
;
;                MSP430F5438
;             -----------------
;         /|\|                 |
;          | |                 |
;          --|RST              |
;            |                 |
;    Vin1 -->|VeREF+           |
;    Vin2 -->|VREF-/VeREF-     |
;
;   R4 - array index  
; 
;   M. Morales
;   Texas Instruments Inc.
;   September 2008
;   Built with Code Composer Essentials v3.x
;******************************************************************************

    .cdecls C,LIST,"msp430x54x.h"

;-------------------------------------------------------------------------------
;-------------------------------------------------------------------------------
            .bss    results,4 

;-------------------------------------------------------------------------------
            .global _main 
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x5C00,SP              ; Initialize stackpointer
            mov.w   #WDTPW + WDTHOLD,&WDTCTL; Stop WDT    
            mov.w   #ADC12ON + ADC12MSC + ADC12SHT0_15,&ADC12CTL0
                                            ; Turn on ADC12, set sampling time
                                            ;  set multiple sample conversion
            mov.w   #ADC12SHP + ADC12CONSEQ_1,&ADC12CTL1  
                                            ; Use sampling timer, single sequence
            mov.b   #ADC12INCH_8,&ADC12MCTL0; ref+=AVcc, Channel = A8
            mov.b   #ADC12INCH_9 + ADC12EOS,&ADC12MCTL1
                                            ; ref+=AVcc, channel = A9, end seq.
            mov.w   #0x0002,&ADC12IE        ; Enable ADC12IFG.1
            bis.w   #ADC12ENC,&ADC12CTL0    ; Enable conversions

while_loop  bis.w   #ADC12SC,&ADC12CTL0     ; Start conversion
            
            bis.w   #LPM4 + GIE,SR          ; Enter LPM4, enable interrupts
            nop                             ; For debugger
            
            jmp     while_loop 


;-------------------------------------------------------------------------------
ADC12_ISR
;-------------------------------------------------------------------------------
            add.w   &ADC12IV,PC             ; Add offset to PC
            reti                            ; Vector 0:  No interrupt
            reti                            ; Vector 2:  ADC overflow
            reti                            ; Vector 4:  ADC timing overflow
            reti                            ; Vector 6:  ADC12IFG0
            jmp     ADC12IFG1_HND           ; Vector 8:  ADC12IFG1
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

ADC12IFG1_HND           
            clr.w   R4                      ; Array_index = 0
            mov.w   &ADC12MEM0,0x1C00(R4)   ; Move A0 results, IFG is cleared
            incd.w  R4                      ; Point to next integer in array
            mov.w   &ADC12MEM1,0x1C00(R4)   ; Move A1 results, IFG is cleared
            bic.w   #LPM4,0(SP)             ; Exit active from ISR, SET BKPT HERE 
            reti                            ; Return from interrupt 
            
;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int55"                ; ADC12 isr vector
            .short  ADC12_ISR
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end