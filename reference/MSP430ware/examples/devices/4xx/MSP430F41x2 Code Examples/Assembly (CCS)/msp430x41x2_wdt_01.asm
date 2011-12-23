;******************************************************************************
;   MSP430F41x2 Demo - WDT, Toggle P5.1, Interval Overflow ISR, DCO SMCLK
;
;   Description: Toggle P5.1 using WDT configured for Interval Timer mode.
;   Interrupt toggles LED every 31ms when using default FLL+ register
;   settings and an external 32kHz watch crystal.
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   //* An external watch crystal between XIN & XOUT is required for ACLK *//	
;
;                 MSP430F41x2
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |             P5.1|-->LED
;
;  P. Thanigai
;  Texas Instruments Inc.
;  January 2009
;  Built with CCE Version: 3.1   
;******************************************************************************
 .cdecls C,LIST, "msp430x41x2.h" 
 
            .global _main
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
_main
RESET       mov.w   #0400h,SP               ; Initialize stack pointer
SetupWDT    mov.w   #WDT_MDLY_32,&WDTCTL    ; WDT ~31ms interval timer
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps
            bis.b   #WDTIE,&IE1             ; Enable WDT interrupt
SetupP4     bis.b   #02h,&P5DIR             ; P5.1output
                                            ;						
Mainloop    bis.w   #CPUOFF+GIE,SR          ; Enter LPM0, enable interrupts
            nop                             ; Required only for debugger
                                            ;
;------------------------------------------------------------------------------
WDT_ISR;    Toggle P5.1
;------------------------------------------------------------------------------
            xor.b   #02h,&P5OUT             ; Toggle P5.1
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

