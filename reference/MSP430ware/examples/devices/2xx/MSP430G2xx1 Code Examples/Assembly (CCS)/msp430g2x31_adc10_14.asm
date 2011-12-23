;*******************************************************************************
;   MSP430G2x31 Demo - ADC10, DTC Sample A1-0 16x, AVcc, Repeat Seq, DCO
;
;   Description: Use DTC to sample A1/A0 repeat sequence 16x(32 total samples)
;   with reference to AVcc.  Software writes to ADC10SC to trigger sample burst.
;   In Mainloop MSP430 waits in LPM0 to save power until ADC10 conversion
;   complete, ADC10_ISR will force exit from any LPMx in Mainloop on reti.
;   ADC10 internal oscillator times sample period (16x) and conversion (13x).
;   DTC transfers conversion code to RAM 200h - 240h.  ADC10(DTC) interrupt
;   will return system active.
;
;                MSP430G2x31
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;        >---|P1.1/A1          |
;        >---|P1.0/A0          |
;
;   D. Dang
;   Texas Instruments Inc.
;   October 2010
;   Built with Code Composer Essentials Version: 4.2.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430g2231.h"

;------------------------------------------------------------------------------
            .text                           ; Progam Start
;------------------------------------------------------------------------------
RESET       mov.w   #0280h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupADC10  mov.w   #INCH_1+CONSEQ_3,&ADC10CTL1 ; A1/A0, repeat multi channel
            mov.w   #ADC10SHT_2+MSC+ADC10ON+ADC10IE,&ADC10CTL0 ;
            bis.b   #03h,&ADC10AE0          ; P1.0,1 ADC option select
            mov.b   #020h,&ADC10DTC1        ; 32 conversions
                                            ;
Mainloop
busy_test   bit     #BUSY,&ADC10CTL1        ; ADC10 core inactive?
            jnz     busy_test               ;
            mov.w   #0200h,&ADC10SA         ; Data buffer start
            bis.w   #ENC+ADC10SC,&ADC10CTL0 ; Start sampling
            bis.w   #CPUOFF+GIE,SR          ; CPU off, Enable interrupts
            nop                             ; space for debugger
            nop                             ; set breakpoint here to read ADC
            jmp     Mainloop                ; Again, set breakpoint here to read ADC
                                            ;
;-------------------------------------------------------------------------------
ADC10_ISR;
;-------------------------------------------------------------------------------
            bic.w   #ENC,&ADC10CTL0         ; ADC10 disabled
            bic.w   #LPM0,0(SP)             ; Exit LPM0 on reti
            reti                            ;
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int05"                ; ADC10 Vector
            .short  ADC10_ISR               ;
            .end
