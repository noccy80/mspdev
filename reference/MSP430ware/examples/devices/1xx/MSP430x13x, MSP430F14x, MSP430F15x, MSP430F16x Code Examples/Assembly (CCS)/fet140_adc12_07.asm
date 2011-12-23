;******************************************************************************
;   MSP-FET430P140 Demo - ADC12, Repeated Single Channel Conversions
;
;   Description: This program will show how to perform repeated conversions
;                on a single channel, using the "repeat-single-channel" mode.
;
;   This example shows how to perform repeated conversions on a single channel
;   using "repeat-single-channel" mode.  AVcc is used for the reference and
;   repeated conversions are performed on Channel A0. Each conversion result
;   is stored in ADC12MEM0 and is moved to a RAM location.  The conversion
;   results are moved to RAM addresses 0x200 - 0x20E.  Test by applying a
;   voltage to channel A0, then running. To view the conversion results, open a
;   memory window in debugger and view the contents of addresses 0x200 - 0x20E
;   after stopping program execution. Remember the conversion results are
;   12-bits so you must .set the memory window to 16-bit mode.
;
;   *Note*  This example only functions on MSP production silicon, not PMS
;   pre-production silicon.  Production silicon will be noted on the chip as
;   "M430F149" whereas pre-production silicon will be marked "P430F149."
;
;
;                MSP430F149
;              ---------------
;             |               |
;      Vin -->|P6.0/A0        |
;             |               |
;
;
;   M. Mitchell / G. Morton
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x14x.h"
;
Results     .equ    0200h                   ; Begining of Results table
;
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov     #0A00h,SP               ; Initialize stackpointer
StopWDT     mov     #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog
            bis.b   #BIT0,&P6SEL            ; Enable A/D channel A0
                                            ;
SetupADC12  mov     #SHT0_8+MSC+ADC12ON,&ADC12CTL0
                                            ; Turn on ADC12, use int. osc.
                                            ; Extend sampling period to avoid
                                            ; overflow
                                            ; .set MSC so conversions triggered
                                            ; automatically
            mov     #SHP+CONSEQ_2,&ADC12CTL1
                                            ; Use sampling timer, .set mode
            mov     #BIT0,&ADC12IE          ; Enable ADC12IFG.0 for ADC12MEM0
            clr     R5                      ; Clear results table pointer
                                            ;
Mainloop    bis     #ENC,&ADC12CTL0         ; Enable conversions
            bis     #ADC12SC,&ADC12CTL0     ; Start conversions
            bis     #CPUOFF+GIE,SR          ; Hold in LPM0, Enable interrupts
                    nop                     ; Need only for debug
                                            ;
;------------------------------------------------------------------------------
ADC12ISR    ; Interrupt Service Routine for ADC12
;------------------------------------------------------------------------------
            mov     &ADC12MEM0,Results(R5)  ; Move result, IFG is reset
            incd    R5                      ; Increment results table pointer
            and     #0Eh,R5                 ; Modulo pointer
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