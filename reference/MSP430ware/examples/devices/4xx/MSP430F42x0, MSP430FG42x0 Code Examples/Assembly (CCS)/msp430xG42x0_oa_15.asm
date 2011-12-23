;*****************************************************************************
;  MSP430xG42x0 Demo - OA0, Offset Calibration
;
;  Description: Configure OA0 for measuring offset calibration. The DAC0 
;  module is used to provide a reference input to the non-inverting
;  terminal of the op-amp. The reference is also given to the negative input of  
;  the SD16 module (internaly using the OACAL bit). The output of the OA is 
;  connected internally to the positive input of the SD16. The differential 
;  voltage measured by the SD16 gives the offset value of the OA. 
;  ACLK = 32.768kHz, MCLK = SMCLK = default DCO 
;  ACLK = 32.768kHz, MCLK = SMCLK = default DCO
;
;                MSP430xG42x0
;             -------------------
;         /|\|                XIN|-
;          | |                   |
;          --|RST            XOUT|-
;            |                   |
;            |                   |
;            |                   |
;            |          SD16MEM0 |--> OA0 Offset voltage
;            |                   |
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430xG42x0.h"
 
RESULTS	.equ R12
;-------------------------------------------------------------------------------
            .text                 ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stackpointer

StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT

DAC12_0     mov.w   #DAC12OPS+ DAC12IR + DAC12AMP_2 + DAC12ENC,&DAC12_0CTL
                                            ; 1x input range, enable DAC120,
                                            ; low speed/current
            mov.w   #0545h,&DAC12_0DAT      ; DAC120 ref. voltage ~ 1V
            
SetupOA     mov.b   #OAPM_1+OAP_2,&OA0CTL0  ; Select inputs, power mode
            mov.b   #OAFC_1+OACAL,&OA0CTL1  ; Mode, offset calib. enabled

SetupSD16   mov.w   #SD16REFON+SD16SSEL0,&SD16CTL ; 1.2V ref, SMCLK
            bis.w   #SD16SNGL+SD16DF+SD16BUF_2,&SD16CCTL0; Single conversion,
                                            ; 2s complement mode, buffer on
            bis.b   #01h,&SD16AE            ; Analog input enable                               
            mov.w   #03600h,R15             ; Delay needed for 1.2V ref startup
L$1         dec.w   R15                     ;
            jnz     L$1                     ;

Mainloop    bis.w   #SD16SC,&SD16CCTL0      ; Start conversion
testIFG     bit.w   #SD16IFG,&SD16CCTL0     ; Is conversion done?
            jz      testIFG                 ; No, test again
            mov.w   &SD16MEM0,RESULTS       ; Yes, save conversion result
                                            ; (automatically clears SD16IFG)
            jmp     Mainloop                ; SET BREAKPOINT HERE

;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect	".reset"            ; MSP430 RESET Vector
            .short   RESET                   ;
            .end
   