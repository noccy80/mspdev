;******************************************************************************
;   MSP430x42x0 Demo - DAC0 1V output with 3x reference
;
;   Description: Output 1V on DAC0
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;                MSP430F4270
;             -----------------
;        /|\|              XIN|-
;         | |                 |
;         --|RST          XOUT|-
;           |                 |
;           |        DAC0/P1.4|--> 1V
;           |                 |
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x42x0.h"
;------------------------------------------------------------------------------
			.text							; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT

            mov.w   #SD16REFON, &SD16CTL    ;  1.2V ref
            mov.w   #DAC12OPS + DAC12SREF_2 + DAC12AMP_5 + DAC12ENC, &DAC12_0CTL ;
                                            ; DAC o/p external, Ref Voltage = internal (SD16),
                                            ; Enable conversion

            mov.w   #0471h, &DAC12_0DAT     ; 1V (Full range = 0FFFh = 3.6v)

Mainloop    bis.w   #CPUOFF,SR              ; Enter LPM0
            nop

;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect    ".reset"                  ; RESET Vector
            .short   RESET                   ;
            .end
