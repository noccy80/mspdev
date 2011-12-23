;*******************************************************************************
;   MSP430F22x4 Demo - OA0, General-Purpose Mode
;
;   Description: Configure OA0 for General-Purpose mode. In this mode, all
;   OA connections are available externally.
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;                 MSP430F22x4
;              -------------------
;          /|\|                XIN|-
;           | |                   |
;           --|RST            XOUT|-
;             |                   |
;      "+" -->|P2.0/A0/OA0I0      |
;      "-" -->|P2.2/A2/OA0I1      |
;             |                   |
;             |       P2.1/A1/OA0O|--> OA0 Output
;             |                   |
;             |                   |
;
;  P.Thanigai
;  Texas Instruments Inc.
;  August 2007
;  Built with Code Composer Essentials Version: 2.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430x22x4.h"
                              
;------------------------------------------------------------------------------
            .text                  			; Program reset
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
                                            ;
SetupOA0    mov.b   #OAN_1+OAPM_1,&OA0CTL0  ; "+" connected to OA0I0 (default),
                                            ; "-" connected to OA0I1,
                                            ; Slow slew rate
                                            ; Output connected to A1/OA0A
            mov.b   #07h,&ADC10AE0          ; P2.2/1/0 analog function select
                                            ;
Mainloop    bis.w   #LPM3,SR                ; Enter LPM3
            nop                             ; Required only for debug
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end

