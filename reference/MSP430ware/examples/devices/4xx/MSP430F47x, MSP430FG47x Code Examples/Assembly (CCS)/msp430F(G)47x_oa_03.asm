;*****************************************************************************
;  MSP430F(G)47x Demo - OA0, General-Purpose Mode
;
;  Description: Configure OA0 for General-Purpose mode.
;  ACLK = n/a, MCLK = SMCLK = default DCO
;
;                MSP430F(G)47x
;             -------------------
;         /|\|                XIN|-
;          | |                   |
;          --|RST            XOUT|-
;            |                   |
;     "+" -->|P1.6/OA0I0         |
;     "-" -->|P6.2/OA0I1         |
;            |                   |
;            |          P6.0/OA0O|--> OA0 Output
;            |                   |
;            |                   |
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
SetupOA     mov.b   #OAN_0 + OAP_0 + OAPM_1,&OA0CTL0  ; "+" connected to OA0I0 (default),
                                            ; "-" connected to OA0I1           			
Mainloop    bis.w   #LPM3,SR                ; Enter LPM3
            nop                             ; Required only for debug
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;  
            .end