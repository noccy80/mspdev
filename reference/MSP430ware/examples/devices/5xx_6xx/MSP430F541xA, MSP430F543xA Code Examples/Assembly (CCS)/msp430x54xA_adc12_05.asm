;******************************************************************************
;  MSP430F543xA Demo - ADC12_A, Using an External Reference
;
;  Description: This example shows how to use an external positive reference for
;  the ADC12.The external reference is applied to the VeREF+ pin. AVss is used
;  for the negative reference. A single conversion is performed on channel A0.
;  The conversion results are stored in ADC12MEM0 and Test by applying a voltage
;  to channel A0, then setting and running to a break point at the "_NOP()"
;  instruction. To view the conversion results, open the register window in 
;  the debugger and view the contents of ADC12MEM0.
;
;
;                MSP430F5438A
;             -----------------
;         /|\|                 |
;          | |                 |
;          --|RST              |
;            |                 |
;     Vin -->|P6.0/A0          |
;            |                 |
;     REF -->|P5.0/VeREF+      |
;            |                 |
;
;   D. Dang
;   Texas Instruments Inc.
;   December 2009
;   Built with CCS Version: 4.0.2 and IAR Embedded Workbench Version: 4.11B
;******************************************************************************

    .cdecls C,LIST,"msp430x54xA.h"

;-------------------------------------------------------------------------------
            .global _main 
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x5C00,SP              ; Initialize stackpointer
            mov.w   #WDTPW + WDTHOLD,&WDTCTL; Stop WDT    
            bis.b   #0x01,&P6SEL            ; Enable A/D channel A0
            mov.w   #ADC12ON + ADC12SHT0_2,&ADC12CTL0 
                                            ; Turn on ADC12, set sampling time
            mov.w   #ADC12SHP,&ADC12CTL1    ; Use sampling timer
            mov.b   #ADC12SREF_2,&ADC12MCTL0; Vr+ = VeREF+ (ext) and Vr-=AVss
            bis.w   #ADC12ENC,&ADC12CTL0    ; Enable conversions
            

while_loop  bis.w   #ADC12SC,&ADC12CTL0     ; Start conversion
poll_ifg    bit.w   #BIT0,&ADC12IFG
            jnc     poll_ifg
            nop                             ; SET BREAKPOINT HERE
            jmp     while_loop 
            
;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end
