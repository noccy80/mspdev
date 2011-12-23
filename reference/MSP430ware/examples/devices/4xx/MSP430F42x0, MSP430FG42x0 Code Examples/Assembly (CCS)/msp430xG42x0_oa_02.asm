;*****************************************************************************
;  MSP430xG42x0 Demo - OA0, Comparator in General-Purpose Mode
;
;  Description: Use OA0 as a comparator in general-purpose mode. In this
;  example, OA0 is configured for general-purpose mode, but used as a
;  comparator. The reference is supplied by DAC12_0 on the "-" input.
;  The "+" terminal is connected to OA0I0.
;  ACLK = 32.768kHz, MCLK = SMCLK = default DCO
;
;                MSP430xG42x0
;             -------------------
;         /|\|                XIN|-
;          | |                   |
;          --|RST            XOUT|-
;            |                   |
;     "+" -->|P1.6/OA0I0         |
;            |                   |
;            |          P6.0/OAOO|--> OA0 Output
;            |                   |    Output goes high when
;            |                   |    Input > 1V
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430xG42x0.h"
;-------------------------------------------------------------------------------
            .text                 ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stackpointer

StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT

DAC12_0     mov.w   #DAC12IR+DAC12AMP_2+DAC12ENC,&DAC12_0CTL
                                            ; 1x input range, enable DAC120,
                                            ; low speed/current
            mov.w   #0555h,&DAC12_0DAT      ; Set DAC120 to output 1V
                                            ;
SetupOA     mov.b   #OAN_2+OAPM_1,&OA0CTL0  ; "-" connected to DAC120,
                                            ; "+" connected to OA0I0 (default),
                                            ; slow slew rate						
Mainloop    bis.w   #LPM3,SR                ; Enter LPM3
            nop                             ; Required only for debug
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect	".reset"            ; MSP430 RESET Vector
            .short   RESET                   ;
            .end
   