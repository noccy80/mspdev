;******************************************************************************
;   MSP430xG46x Demo - 3-Amp Differential Amplifier with OA2, OA0, and OA1
;
;   Description: Configure OA2, OA0, and OA1 as a 3-Amp Differential Amp.
;   In this configuration, the R2/R1 ratio sets the gain. The R ladders for
;   OA1 and OA2 form the R2/R1 dividers. The OAFBRx settings for both OA1
;   and OA2 must be equal.
;   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
;
;                |\
;                | \ OA2
;   V2-----------|+ \           R1             R2
;                |   |----+---/\/\/\/---+----/\/\/\/----|
;            ----|- /     |             |               |
;            |   | /      |             |  |\          GND
;            |   |/       |             |  | \ OA1
;            |____________|             ---|+ \
;                                          |   |--------+--------->
;                                       ---|- /         |
;                |\                     |  | /          | Vout = (V2-V1)xR2/R1
;                | \ OA0                |  |/           |        (Gain is 3)
;   V1-----------|+ \           R1      |      R2       |
;                |   |----+---/\/\/\/---+----/\/\/\/----|
;            ----|- /     |
;            |   | /      |
;            |   |/       |
;            |____________|
;
;
;                 MSP430FG461x
;              -------------------
;          /|\|                XIN|-
;           | |                   |
;           --|RST            XOUT|-
;             |                   |
;       V2 -->|P6.6/OA2I0         |
;       V1 -->|P6.0/OA0I0         |
;             |                   |
;             |          P6.3/OA1O|--> Diff Amp Output
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
                                            ;
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
                                            ;
SetupOA     mov.b   #OAPM_1,&OA0CTL0        ; Select inputs, power mode
            mov.b   #OAFC_7+OARRIP,&OA0CTL1 ; Differential amp mode
                                            ; limited range (see datasheet)
                                            ;
            mov.b   #OAN_3+OAP_3+OAPM_1+OAADC1,&OA1CTL0
                                            ; Select inputs, output
            mov.b   #OAFC_6+OAFBR_4+OARRIP,&OA1CTL1
                                            ; Inverting PGA mode,
                                            ; OAFBRx sets gain
                                            ; limited range (see datasheet)
                                            ;
            mov.b   #OAPM_1,&OA2CTL0        ; Select inputs, power mode
            mov.b   #OAFC_1+OAFBR_4+OARRIP,&OA2CTL1
                                            ; Unity gain mode,
                                            ; OAFBRx sets gain
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
                    