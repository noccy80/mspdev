;******************************************************************************
;   MSP-FET430P430 Demo - ADC12, Using 10 External Channels of Conversion
;
;   Description: This program will show how to obtain 10 external channels of
;                conversion.
;
;   This example shows how to perform A/D conversion on up to 10 external
;   channels by showing that channels A8 and A9 can be used for conversion
;   of external signals. A single sequence of conversions is performed - one
;   conversion on A8 and then one conversion on A9. Each conversion uses AVcc
;   and AVss for the references. The conversion results are stored in ADC12MEM0
;   and ADC12MEM1 respectively and are moved to R5 and R6 respectively after
;   the sequence is complete. Test by applying voltages to pins VeREF+ for A8
;   and VREF/VeREF- for A9, then setting and running to a break point at
;   "jmp Mainloop."  To view the conversion results, open a register window
;   with the debugger and view the contents of R5 and R6.
;   ACLK = n/a, MCLK = SMCLK = default DCO, ADC12CLK = ADC12OSC
;
;   *NOTE*  When using channels A8 and A9 for external signals, internal
;   references must be used for the conversions. Refer to figure 17-1 in the
;   MSP430x4xx Family User's Guide.
;
;
;               MSP430FG439
;            -----------------
;           |                 |
;   Vin1 -->|VeREF+           |
;   Vin2 -->|VREF-/VeREF-     |
;
;
;   M. Mitchell / M. Mitchell
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430xG43x.h"
;------------------------------------------------------------------------------
            .text                  ; Program Start
;------------------------------------------------------------------------------
RESET       mov     #0A00h,SP                ; Initialize stack pointer
StopWDT     mov     #WDTPW+WDTHOLD,&WDTCTL   ; Stop watchdog
                                             ;
SetupADC12  mov     #ADC12ON+MSC+SHT0_15,&ADC12CTL0
                                             ; Turn on ADC12, set MSC bit
            mov     #SHP+CONSEQ_1,&ADC12CTL1 ; Use samp. timer, single sequence
            bis.b   #INCH_8,&ADC12MCTL0      ; AVcc=ref+, channel=A8
            bis.b   #INCH_9+EOS,&ADC12MCTL1  ; AVcc=ref+, channel=A9, .end seq.
                                             ;
            mov     #BIT1,&ADC12IE           ; Enable ADC12IFG.1 for ADC12MEM1
            bis     #ENC,&ADC12CTL0          ; Enable conversions
            eint                             ; Enable interrupts
                                             ;
Mainloop    bis     #ADC12SC,&ADC12CTL0      ; Start conversions
            bis     #CPUOFF,SR               ; Hold in LPM0 for seq to complete
            nop                              ; Required only for debugger
            jmp     Mainloop                 ; Set BREAKPOINT HERE
                                             ;
;------------------------------------------------------------------------------
ADC12ISR    ; Interrupt Service Routine for ADC12
;------------------------------------------------------------------------------
            mov     &ADC12MEM0,R5            ; Move A8 result
            mov     &ADC12MEM1,R6            ; Move A9 result
            bic     #CPUOFF,0(SP)
            reti                             ;
                                             ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                 ; RESET Vector
            .short  RESET                    ;
            .sect   ".int07"                 ; ADC12 Vector
            .short  ADC12ISR                 ;
            .end