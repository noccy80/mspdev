;******************************************************************************
;   MSP-FET430P140 Demo - ADC12, Using 10 External Channels for Conversion
;
;   Description: This program will show how to obtain 10 external channels for
;                conversion.
;
;   This example shows how to perform A/D conversion on up to 10 external
;   channels by showing that channels A8 and A9 can be used for conversion
;   of external signals when not using these channels as external reference 
;   inputs. A single sequence of conversions is performed - one
;   conversion on A8 and then one conversion on A9. Each conversion uses AVcc
;   and AVss for the references. The conversion results are stored in ADC12MEM0
;   and ADC12MEM1 respectively and are moved to R5 and R6 respectively after
;   the sequence is complete. Test by applying voltages to pins VeREF+ for A8
;   and VREF/VeREF- for A9, then setting and running to a break point at
;   "jmp Mainloop."  To view the conversion results, open a register window in
;   debugger and view the contents of R5 and R6.
;
;   *NOTE*  When using channels A8 and A9 for external signals, internal
;   references must be used for the conversions. Refer to figure 17-1 in the
;   MSP430x1xx Family User's Guide.
;
;   *Note*  This example only functions on MSP production silicon, not PMS
;   pre-production silicon.  Production silicon will be noted on the chip as
;   "M430F149" whereas pre-production silicon will be marked "P430F149."
;
;
;
;               MSP430F149
;            -----------------
;           |                 |
;   Vin1 -->|VeREF+           |
;   Vin2 -->|VREF-/VeREF-     |
;
;
;   M. Mitchell / G. Morton
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x14x.h"
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov     #0A00h,SP               ; Initialize stackpointer
StopWDT     mov     #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog
                                            ;
SetupADC12  mov     #ADC12ON+MSC+SHT0_15,&ADC12CTL0
                                            ; Turn on ADC12, set MSC bit
            mov     #SHP+CONSEQ_1,&ADC12CTL1; Use samp. timer, single sequence
            bis.b   #INCH_8,&ADC12MCTL0     ; AVcc=ref+, channel=A8
            bis.b   #INCH_9+EOS,&ADC12MCTL1 ; AVcc=ref+, channel=A9, .end seq.
                                            ;
            mov     #BIT1,&ADC12IE          ; Enable ADC12IFG.1 for ADC12MEM1
            bis     #ENC,&ADC12CTL0         ; Enable conversions
                                            ;
Mainloop    bis     #ADC12SC,&ADC12CTL0     ; Start conversions
            bis     #CPUOFF+GIE,SR          ; Hold in LPM0 for seq to complete
                                            ; Enable interrupts
            nop                             ; Only required for debug.
            jmp     Mainloop                ; SET BREAKPOINT HERE
                                            ;
;------------------------------------------------------------------------------
ADC12ISR    ; Interrupt Service Routine for ADC12
;------------------------------------------------------------------------------
            mov     &ADC12MEM0,R5           ; Move A8 result
            mov     &ADC12MEM1,R6           ; Move A9 result
            bic     #CPUOFF,0(SP)
            reti                            ;
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int07"                ; ADC12 Interrupt Vector
            .short  ADC12ISR                ;
            .end