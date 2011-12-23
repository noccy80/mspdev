;******************************************************************************
;   MSP-FET430P430 Demo - OA0, Comparator Mode
;
;   Description: Configure OA0 for Comparator mode. In this example, OA0 is
;   configured as a comparator. The comparator reference is connected to
;   the "-" input and comes from the integrated R ladder. The reference level
;   is selected with the OAFBR bits. The "+" terminal is connected to OA0I0.
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;                 MSP430FG439
;              -------------------
;          /|\|                XIN|-
;           | |                   |
;           --|RST            XOUT|-
;             |                   |
;      "+" -->|P6.0/OA0I0         |
;             |                   |
;             |          P6.1/OA0O|--> OA0 Output
;             |                   |    Output goes high when
;             |                   |    Input > (0.25 * AVcc)
;
;   M. Mitchell / M. Mitchell
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentals Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430xG43x.h"

;------------------------------------------------------------------------------
            .text                  ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
                                            ;
SetupOA     mov.b   #OAPM_1+OAADC1,&OA0CTL0 ; Slow slew rate,
                                            ; "+" connected to OA0IO (default),
                                            ; output connected to A1
            mov.b   #OAFC_3+OAFBR_1+OARRIP,&OA0CTL1
                                            ; Comparator mode, no r-to-r input
                                            ; "-" connected to AVcc * 4/16,					
Mainloop    bis.w   #LPM3,SR                ; Enter LPM3
            nop                             ; Required only for debug
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; RESET Vector
            .short  RESET                   ;
            .end