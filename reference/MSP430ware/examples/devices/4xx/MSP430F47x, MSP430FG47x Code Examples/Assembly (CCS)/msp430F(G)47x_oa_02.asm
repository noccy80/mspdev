;******************************************************************************
;   MSP430FG479 Demo - OA0, Comparator in General-Purpose Mode
;
;   Description: Use OA0 as a comparator in general-purpose mode. In this
;   example, OA0 is configured for general-purpose mode, but used as a
;   comparator. The reference is supplied by DAC12_0 on the "-" input.
;   The "+" terminal is connected to OA0I0.
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;                 MSP430FG479 
;              -------------------
;          /|\|                XIN|-
;           | |                   |
;           --|RST            XOUT|-
;             |                   |
;      "+" -->|P6.0/OA0I0         |
;             |                   |
;             |          P6.1/OA0O|--> OA0 Output
;             |                   |    Output goes high when
;             |                   |    Input > 1.5V
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
                                            ; AVcc reference for DAC12
DAC12_0     mov.w   #DAC12IR+DAC12AMP_2+DAC12ENC,&DAC12_0CTL
                                            ; 1x input range, enable DAC120,
                                            ; low speed/current
            mov.w   #07FFh,&DAC12_0DAT      ; Set DAC120 to output 1.5V
                                            ;
SetupOA     mov.b   #OAN_3 + OAPM_1,&OA0CTL0; "-" connected to DAC120,
                                            ; "+" connected to OA0I0 (default),
                                            ; slow slew rate
Mainloop    bis.w   #LPM3,SR                ; Enter LPM3
            nop                             ; Required only for debug
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;  
            .end