;******************************************************************************
;   MSP430x47xx Demo - WDT, Toggle P5.1, Interval Overflow ISR, DCO SMCLK
;
;   Description: Toggle P5.1 using WDT configured for Interval Timer mode.
;   Interrupt toggles LED every 31ms when using default FLL+ register
;   settings and an external 32kHz watch crystal.
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   //* An external watch crystal between XIN & XOUT is required for ACLK *//	
;
;                 MSP430x47xx
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
RESET       mov.w   #850h,SP         ; Initialize stackpointer
SetupWDT    mov.w   #WDT_MDLY_32,&WDTCTL    ; WDT ~31ms interval timer
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps
            bis.b   #WDTIE,&IE1             ; Enable WDT interrupt
SetupP5     bis.b   #BIT1,&P5DIR            ; P5.1 output
                                            ;						
Mainloop    bis.w   #CPUOFF+GIE,SR          ; Enter LPM0, enable interrupts
            nop                             ; Required only for debugger
                                            ;
;------------------------------------------------------------------------------
WDT_ISR;    Toggle P5.1
;------------------------------------------------------------------------------
            xor.b   #BIT1,&P5OUT            ; Toggle P5.1
            reti                            ;		
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"            	; MSP430 RESET Vector
            .short  RESET                   ;    
            .sect   ".int10"              ; MSP430 Watchdog Interrupt Vector
            .short   WDT_ISR         
            .end
            