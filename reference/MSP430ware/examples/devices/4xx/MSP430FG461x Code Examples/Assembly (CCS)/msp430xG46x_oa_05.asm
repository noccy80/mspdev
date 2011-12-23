;******************************************************************************
;   MSP430xG46x Demo - OA0, Non-Inverting PGA Mode
;
;   Description: Configure OA0 for Non-Inverting PGA mode. In this mode,
;   the "-" terminal is connected to the R ladder tap and the OAFBRx bits
;   select the gain.
;   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
;
;                 MSP430FG461x
;              -------------------
;          /|\|                XIN|-
;           | |                   |
;           --|RST            XOUT|-
;             |                   |
;      "+" -->|P6.0/OA0I0         |
;             |                   |
;             |          P6.1/OA0O|--> OA0 Output
;             |                   |    Gain is 8
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
SetupOA     mov.b   #OAPM_1+OAADC1,&OA0CTL0 ; Slow slew rate,
                                            ; "+" connected to OA0IO (default),
                                            ; output connected to A1
            mov.b   #OAFC_4+OAFBR_6+OARRIP,&OA0CTL1
                                            ; Non-inverting PGA mode,
                                            ; gain is 8,
                                            ; limited range (see datasheet)
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
                     