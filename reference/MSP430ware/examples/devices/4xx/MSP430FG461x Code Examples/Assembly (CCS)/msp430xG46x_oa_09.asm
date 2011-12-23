;******************************************************************************
;   MSP430xG46x Demo - OA1, Inverting PGA Mode
;
;   Description: Configure OA1 for Inverting PGA mode. In this mode, the
;   "+" terminal must be supplied with an offset, since the OA is a
;   single-supply opamp, and the input must be positive. If an offset is
;   not supplied, the opamp will try to drive its output negative, which
;   cannot be done. In this example, the offset is provided by DAC120
;   and is 1.5V. The "-" terminal is connected to the R ladder tap and
;   the OAFBRx bits select the gain. The input signal should be AC coupled.
;   With the gain set to -7 and supply of 3V, the output will reach the rails
;   with an input of 1.5/7 = +/-0.21V relative to the 1.5V offset.
;   ACLK = 32.768kHz, MCLK = SMCLK = default DCO
;
;                    MSP430FG461x
;                 -------------------
;             /|\|                XIN|-
;              | |                   |
;              --|RST            XOUT|-
;                |                   |
;     "-" --||-->|P6.4/OA1I0         |
;                |                   |
;                |          P6.3/OA1O|-->  OA1 Output
;                |                   |     Gain is -7
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
REFOn       mov.w   #REFON+REF2_5V,&ADC12CTL0
                                            ; 2.5V reference for DAC12
DAC12_0     mov.w   #DAC12IR+DAC12AMP_2+DAC12ENC,&DAC12_0CTL
                                            ; 1x input range, enable DAC120,
                                            ; low speed/current
            mov.w   #099Ah,&DAC12_0DAT      ; Set DAC120 to output 1.5V
                                            ;

SetupOA     mov.b   #OAP_2+OAPM_1+OAADC1,&OA1CTL0
                                            ; "+" connected to DAC120,
                                            ; slow slew rate,
                                            ; output connected to A3
            mov.b   #OAFC_6+OAFBR_6+OARRIP,&OA1CTL1
                                            ; Inverting PGA mode,
                                            ; amplifier gain is -7,
                                            ; limited range (see datasheet)
                                            ;						
Mainloop    bis.w   #LPM3,SR                ; Exit LPM3
            nop                             ; Required only for debug
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ; POR, ext. Reset, Watchdog
            .short   RESET
            .end
                     