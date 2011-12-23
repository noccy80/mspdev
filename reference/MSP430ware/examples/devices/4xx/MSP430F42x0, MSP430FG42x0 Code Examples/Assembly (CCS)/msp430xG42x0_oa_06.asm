;*****************************************************************************
;  MSP430xG42x0 Demo - OA0, Unity-Gain Buffer Mode                            
;                                                                             
;  Description: Configure OA0 for Unity-Gain Buffer mode.                     
;  ACLK = 32.768kHz, MCLK = SMCLK = default DCO                               
;                                                                             
;                MSP430xG42x0                                                 
;             -------------------                                             
;         /|\|                XIN|-                                           
;          | |                   |                                            
;          --|RST            XOUT|-                                           
;            |                   |                                            
;     "+" -->|P1.6/OA0I0         |                                            
;            |                   |                                            
;            |          P6.1/OA0O|--> OA0 Output                              
;            |                   |                                            
;                                                                             
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430xG42x0.h"

;-------------------------------------------------------------------------------
            .text                 ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stackpointer

StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupOA     mov.b   #OAPM_1,&OA0CTL0        ; Select inputs, power mode
                                            ; "+" connected to OA0I0 (default),
                                            ; slow slew rate	
            mov.b   #OAFC_1,&OA0CTL1        ; Unity gain mode
Mainloop    bis.w   #LPM3,SR                ; Enter LPM3
            nop                             ; Required only for debug
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect	".reset"            ; MSP430 RESET Vector
            .short   RESET                   ;
            .end
            