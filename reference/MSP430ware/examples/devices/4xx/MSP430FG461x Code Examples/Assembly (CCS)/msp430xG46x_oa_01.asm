;******************************************************************************
;   MSP430xG46x Demo - OA0, Comparator Mode
;
;   Description: Configure OA0 for Comparator mode. In this example, OA0 is
;   configured as a comparator. The comparator reference is connected to
;   the "-" input and comes from the integrated R ladder. The reference level
;   is selected with the OAFBR bits. The "+" terminal is connected to OA0I0.
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
;             |                   |    Output goes high when
;             |                   |    Input > (0.25 * AVcc)
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430xG46x.h"
;-------------------------------------------------------------------------------
			.text	;Program Start
;-----------------------------------------------------------------------------
RESET       mov.w   #900,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
                                            ;
SetupOA     mov.b   #OAPM_1+OAADC1,&OA0CTL0 ; Slow slew rate,
                                            ; "+" connected to OA0IO (default),
                                            ; output connected to A1
            mov.b   #OAFC_3+OAFBR_1+OARRIP,&OA0CTL1
                                            ; Comparator mode,
                                            ; "-" connected to AVcc * 4/16,
                                            ; limited range (see datasheet)						
Mainloop    bis.w   #LPM3,SR                ; Enter LPM3
            nop                             ; Required only for debug
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ; POR, ext. Reset, Watchdog
            .short   RESET
            .end
           