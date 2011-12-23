;******************************************************************************
;   MSP-FET430P430 Demo - OA1, Unity-Gain Buffer Mode
;
;   Description: Configure OA1 for Unity-Gain Buffer mode.
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;                 MSP430FG439
;              -------------------
;          /|\|                XIN|-
;           | |                   |
;           --|RST            XOUT|-
;             |                   |
;      "+" -->|P6.4/OA1I0         |
;             |                   |
;             |          P6.3/OA1O|--> OA1 Output
;             |                   |
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
RESET       mov.w   #0A00h,SP               ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
                                            ;
SetupOA     mov.b   #OAPM_1+OAADC1,&OA1CTL0 ; Slow slew rate,
                                            ; "+" connected to OA1IO (default),
                                            ; output connected to A3
            mov.b   #OAFC_1,&OA1CTL1        ; Unity gain buffer w/ r-to-r input
                                            ;						
Mainloop    bis.w   #LPM3,SR                ; Enter LPM3
            nop                             ; Required only for debug
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; RESET Vector
            .short  RESET                   ;
            .end