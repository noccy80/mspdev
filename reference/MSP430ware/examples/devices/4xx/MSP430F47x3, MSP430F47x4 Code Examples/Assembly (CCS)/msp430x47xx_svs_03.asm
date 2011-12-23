;******************************************************************************
;   MSP430x47xx Demo - SVM, Toggle port 5.1 on Vcc < 2.8V
;
;  Description: The SVS feature is used to monitor VCC. LED turns ON when Vcc 
;  drops below reference threshold of 2.8V.SVS flags need to be reset in
;  software.
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;                MSP430x47xx
;              -----------------
;          /|\|              XIN|-
;           | |                 |
;           --|RST          XOUT|-
;             |                 |
;             |             P5.1|-->LED
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x47x4.h"
;-------------------------------------------------------------------------------
			.text							; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #900h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP5     bis.b   #BIT1,&P5DIR            ; P5.1  output            
            mov.b   #VLD3,&SVSCTL           ; SVS enabled @ 2.8V, no POR
                                            
Mainloop    clr.b   &P5OUT
            bit.b   #SVSFG,&SVSCTL
            jz      Mainloop
            bic.b   #SVSFG,&SVSCTL
            bis.b   #BIT1,&P5OUT            ; Turn LED on
            mov.w   #050000,R15             ; Delay to R15
L1          dec.w   R15                     ; Decrement R15
            jnz     L1    
            jmp     Mainloop                ; Again
;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect     ".reset"            	; RESET Vector
            .short   RESET                  ;
            .end
            