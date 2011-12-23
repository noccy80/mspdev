;*******************************************************************************
;   MSP430G2xx1 Demo - LFXT1 Oscillator Fault Detection
;
;   Description: System runs normally in LPM3 with WDT timer clocked by
;   32kHz ACLK with a 1x4 second interrupt. P1.0 is normally pulsed every
;   second inside WDT interrupt. If an LFXT1 oscillator fault occurs,
;   NMI is requested forcing exit from LPM3. P1.0 is toggled rapidly by software
;   as long as LFXT1 oscillator fault is present. Assumed only LFXT1 as NMI
;   source - code does not check for other NMI sources.
;   ACLK = LFXT1 = 32768, MCLK = SMCLK = Default DCO
;
;   //*External watch crystal on XIN XOUT is required for ACLK*//	
;
;
;            MSP430G2xx1
;          ---------------
;      /|\|            XIN|-
;       | |               | 32kHz
;       --|RST        XOUT|-
;         |               |
;         |           P1.0|-->LED;
;
;   D. Dang
;   Texas Instruments Inc.
;   October 2010
;   Built with Code Composer Essentials Version: 4.2.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430g2231.h"
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0280h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDT_ADLY_1000,&WDTCTL  ; WDT 1s interval timer
            bis.b   #WDTIE,&IE1             ; Enable WDT interrupt
SetupP1     mov.b   #0FFh,&P1DIR            ; All P1.x outputs
            clr.b   &P1OUT                  ; All P1.x reset
SetupP2     mov.b   #0FFh,&P2DIR            ; All P2.x outputs
            clr.b   &P2OUT                  ; All P2.x reset
; An immedate Osc Fault will occur next
            bis.b   #OFIE,&IE1              ; Enable osc fault interrupt
                                            ;						
Mainloop    xor.b   #001h,&P1OUT            ; Toggle P1.0
            bis.w   #LPM3+GIE,SR            ; Enter LPM3, enable interrupts
            jmp     Mainloop                ;
                                            ;
;-------------------------------------------------------------------------------
NMI_ISR;   Only osc fault enabled, R15 used temporarily and not saved
;          Assumed LFXT1 is only source for NMI interrupt
;-------------------------------------------------------------------------------
CheckOsc    bic.b   #OFIFG,&IFG1            ; Clear OSC fault flag
            xor.b   #001h,&P1OUT            ; Toggle P1.0
            mov.w   #03FFFh,R15             ; R15 = Delay
CheckOsc1   dec.w   R15                     ; Time for flag to set
            jnz     CheckOsc1               ;
            bit.b   #OFIFG,&IFG1            ; OSC fault flag set?
            jnz     CheckOsc                ; OSC Fault, clear flag again
            bis.b   #OFIE,&IE1              ; re-enable osc fault interrupt
            reti                            ; return from interrupt
                                            ;
;-------------------------------------------------------------------------------
WDT_ISR;    Exit LPM3 on reti
;-------------------------------------------------------------------------------
            bic.w   #LPM3,0(SP)             ;
            reti                            ;
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int10"                ; WDT Vector
            .short  WDT_ISR                 ;
            .sect   ".int14"                ; NMI Vector
            .short  NMI_ISR            
            .end
