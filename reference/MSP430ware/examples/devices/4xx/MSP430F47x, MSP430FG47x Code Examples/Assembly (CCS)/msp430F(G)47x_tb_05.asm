;******************************************************************************
;   MSP430FG479 Demo - Timer_B, Toggle P4.6, CCR0 Up Mode ISR, 32kHz ACLK
;
;   Description: Toggle P4.6 using software and the TB_0 ISR. Timer_B is
;   configured for up mode, thus the timer overflows when TBR counts
;   to CCR0. In this example, CCR0 is loaded with 1000-1.
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   //* An external watch crystal between XIN & XOUT is required for ACLK *//	
;
;                MSP430FG479
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
RESET       mov.w   #0A00h,SP               ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps
SetupP4     bis.b   #040h,&P4DIR            ; P4.6 output
SetupC0     mov.w   #CCIE,&TBCCTL0          ; CCR0 interrupt enabled
            mov.w   #1000-1,&TBCCR0         ; CCR0 counts to 1000
SetupTB     mov.w   #TBSSEL_1+MC_1,&TBCTL   ; ACLK, up mode
                                            ;													
Mainloop    bis.w   #LPM3+GIE,SR            ; Enter LPM3, interrupts enabled
            nop                             ; Required only for debugger
                                            ;
;------------------------------------------------------------------------------
TB0_ISR;    Toggle P4.6
;------------------------------------------------------------------------------
            xor.b   #040h,&P4OUT            ; Toggle P4.6
            reti                            ;		
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect    ".reset"            	; RESET Vector
            .short   RESET                  ;
            .sect    ".int13"          ; Timer_A0 Vector
            .short   TB0_ISR                 ;
            .end
