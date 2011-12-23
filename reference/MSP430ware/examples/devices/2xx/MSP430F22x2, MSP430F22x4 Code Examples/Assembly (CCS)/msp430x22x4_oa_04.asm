;*******************************************************************************
;   MSP430F22x4 Demo - OA0, Non-Inverting PGA Mode
;
;   Description: Configure OA0 for Non-Inverting PGA mode. In this mode,
;   the "-" terminal is connected to the R ladder tap and the OAFBRx bits
;   select the gain.
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;                 MSP430F22x4
;              -------------------
;          /|\|                XIN|-
;           | |                   |
;           --|RST            XOUT|-
;             |                   |
;      "+" -->|P2.0/A0/OA0I0      |
;             |                   |
;             |       P2.1/A1/OA0O|--> OA0 Output
;             |                   |    Gain is 8
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
SetupOA0    mov.b   #OAPM_1+OAADC1,&OA0CTL0 ; "+" connected to OA0IO (default),
                                            ; Slow slew rate,
                                            ; Output connected to A1/OA0O
            mov.b   #OAFBR_6+OAFC_4,&OA0CTL1
                                            ; Gain is 8,
                                            ; Non-inverting PGA mode
            mov.b   #03h,&ADC10AE0          ; P2.1/0 analog function select

Mainloop    bis.w   #LPM3,SR                ; Enter LPM3
            nop                             ; Required only for debug
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end

