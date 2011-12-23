;******************************************************************************
;   MSP430xG46x Demo - OA0, General-Purpose Mode
;
;   Description: Configure OA0 for General-Purpose mode.
;   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
;
;                 MSP430FG461x
;              -------------------
;          /|\|                XIN|-
;           | |                   |
;           --|RST            XOUT|-
;             |                   |
;      "+" -->|P6.0/OA0I0         |
;      "-" -->|P6.2/OA0I1         |
;             |                   |
;             |          P6.1/OA0O|--> OA0 Output
;             |                   |
;             |                   |
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430xG46x.h"
;-------------------------------------------------------------------------------
			.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #900,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
                                            ;
SetupOA     mov.b   #OAN_1+OAPM_1,&OA0CTL0  ; "+" connected to OA0I0 (default),
                                            ; "-" connected to OA0I1
            mov.b   #OARRIP,&OA0CTL1        ; Limited range (see datasheet)
                                            ; 				
Mainloop    bis.w   #LPM3,SR                ; Enter LPM3
            nop                             ; Required only for debug
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ; POR, ext. Reset, Watchdog
            .short   RESET
            .end
                       