;******************************************************************************
;   MSP430FG479 Demo - WDT, Toggle P4.6, Interval Overflow ISR, DCO SMCLK
;
;   Description: Toggle P4.6 using WDT configured for Interval Timer mode.
;   Interrupt toggles LED every 31ms when using default FLL+ register
;   settings and an external 32kHz watch crystal.
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   //* An external watch crystal between XIN & XOUT is required for ACLK *//	
;
;                 MSP430FG479
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |             P4.6|-->LED
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
RESET       mov.w   #0A00h,SP               ; Initialize stackpointer
SetupWDT    mov.w   #WDT_MDLY_32,&WDTCTL    ; WDT ~31ms interval timer
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps
            bis.b   #WDTIE,&IE1             ; Enable WDT interrupt
SetupP4     bis.b   #040h,&P4DIR            ; P4.6 output
                                            ;						
Mainloop    bis.w   #CPUOFF+GIE,SR          ; Enter LPM0, enable interrupts
            nop                             ; Required only for debugger
                                            ;
;------------------------------------------------------------------------------
WDT_ISR;    Toggle P4.6
;------------------------------------------------------------------------------
            xor.b   #040h,&P4OUT            ; Toggle P4.6
            reti                            ;		
                                            ;
;-----------------------------------------------------------------------------
;           Interrupt Vectors Used
;-----------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int10"                ; MSP430 RESET Vector
            .short  WDT_ISR 
            .end

