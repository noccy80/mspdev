;******************************************************************************
;   MSP430FG479 Demo - OA1, Unity-Gain Buffer Mode
;
;   Description: Configure OA1 for Unity-Gain Buffer mode.
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;                 MSP430FG479
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
;   P.Thanigai
;   Texas Instruments Inc.
;   September 2008
;   Built with Code Composer Essentials Version: 3.0
;******************************************************************************
 .cdecls C,LIST, "msp430xG47x.h" 

;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
                                            ;
SetupOA     mov.b   #OAPM_1+OAP_0,&OA1CTL0  ; Slow slew rate,
                                            ; "+" connected to OA0IO (default),
                                            ; output connected to A1
            mov.b   #OAFC_1,&OA1CTL1        ; Unity gain buffer mode,
                                            ; 
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