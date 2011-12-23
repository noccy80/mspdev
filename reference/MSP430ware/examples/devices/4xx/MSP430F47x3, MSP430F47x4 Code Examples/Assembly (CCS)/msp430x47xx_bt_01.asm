;******************************************************************************
;  MSP430x47xx Demo - Basic Timer, Toggle P5.1 Inside ISR, 32kHz ACLK
;
;  Description: Toggles P5.1 by xor'ing P5.1 inside of a basic timer ISR.
;  ACLK provides the basic timer clock source. LED toggles every 125ms.
;  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
;
;		  MSP430x47xx
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |             P5.1|-->LED
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
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps
            bis.b   #BIT1,&P5DIR            ; Set P5.1 as Output
SetupBT     mov.b   #BTDIV+BT_fCLK2_DIV16, & BTCTL ; ACLK/(256*16)
            bis.b   #BTIE,&IE2              ; Enable BT interrupt
Mainloop    bis.w   #LPM3+GIE,SR            ; Enter LPM3, enable interrupts
            nop                             ; Required for Debugger              
            
;------------------------------------------------------------------------------
Basic_Timer_ISR;  // Basic Timer Interrupt Service Routine
;------------------------------------------------------------------------------
            xor.b   #BIT1,&P5OUT            ; Toggle P5.1 (LED)
            reti
;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect	".reset"            ; RESET Vector
            .short  RESET                   ;
            .sect   ".int00"	       ; MSP430 Basic Timer Interrupt Vector
            .short  Basic_Timer_ISR         
            .end
