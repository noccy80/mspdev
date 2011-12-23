;*******************************************************************************
;   MSP430F22x4 Demo - OA0, Inverting PGA Mode
;
;   Description: Configure OA0 for Inverting PGA mode. In this mode, the
;   "+" terminal must be supplied with an offset, since the OA is a
;   single-supply opamp, and the input must be positive. If an offset is
;   not supplied, the opamp will try to drive its output negative, which
;   cannot be done. In this example, the offset is provided by an external
;   terminal. The "-" terminal is connected to the R ladder tap and the
;   OAFBRx bits select the gain. The input signal is AC coupled.
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;                    MSP430F22x4
;                 -------------------
;             /|\|                XIN|-
;              | |                   |
;              --|RST            XOUT|-
;                |                   |
;     "-" --||-->|P2.0/A0/OA0I0      |
;     offset  -->|P2.2/A2/OA0I1      |
;                |       P2.1/A1/OA0O|-->  OA0 Output
;                |                   |     Gain is -7
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
SetupOA0    mov.b   #OAP_1+OAPM_1+OAADC1,&OA0CTL0
                                            ; "+" connected to OA0I1,
                                            ; "-" connected to OA0I0 (default),
                                            ; Slow slew rate,
                                            ; Output connected to A1/OA0O
            mov.b   #OAFBR_6+OAFC_6,&OA0CTL1
                                            ; Amplifier gain is -7,
                                            ; Inverting PGA mode
            mov.b   #07h,&ADC10AE0          ; P2.2/1/0 analog function select
Mainloop    bis.w   #LPM3,SR                ; Enter LPM3
            nop                             ; Required only for debug
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end

