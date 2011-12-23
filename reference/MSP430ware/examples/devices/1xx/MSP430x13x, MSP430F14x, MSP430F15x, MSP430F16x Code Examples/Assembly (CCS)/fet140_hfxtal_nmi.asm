;******************************************************************************
;   MSP-FET430P140 Demo - Basic Clock, MCLK Sourced from HF XTAL & Osc Fault
;
;   Description: Proper selection of an external HF XTAL for MCLK is shown with
;   enabled OSC fault interrupt - if HF XTAL fails, NMI interrupt is requested.
;   HF XTAL can only source MCLK when OSC fault is clear. For demonstration
;   purposes P1.0 is set during OSC fault. MCLK output on P5.4.
;   ACLK = MCLK = LFXT1 = HFXTAL
;   //* HF XTAL NOT INSTALLED ON FET *//
;   //* Min Vcc required varies with MCLK frequency - refer to datasheet *//	
;
;                MSP430F149
;             -----------------
;         /|\|              XIN|-
;          | |                 | HF XTAL (455k - 8Mhz)
;          --|RST          XOUT|-
;            |                 |
;            |             P1.0|-->LED
;            |             P5.4|-->MCLK = XTAL (or DCO durring fault)
;
;   M. Buccini / G. Morton
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x14x.h"
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
            bis.b   #001h,&P1DIR            ; P1.0= output direction
            bic.b   #001h,&P1OUT            ; P1.0= reset
SetupP5     bis.b   #010h,&P5DIR            ; P5.4 output
            bis.b   #010h,&P5SEL            ; P5.4 option
SetupBC     bis.b   #XTS,&BCSCTL1           ; LFXT1= HF XTAL
            bis.b   #OFIE,&IE1              ; Enable osc fault interrupt
                                            ;
Mainloop    jmp     Mainloop                ; Repeat
                                            ;
;------------------------------------------------------------------------------
NMI_ISR;   Only osc fault enabled, R15 used temporarly and not saved
;------------------------------------------------------------------------------
            bis.b   #001h,&P1OUT            ; P1.0= .set
CheckOsc    bic.b   #OFIFG,&IFG1            ; Clear OSC fault flag
            mov.w   #0FFh,R15               ; R15= Delay
CheckOsc1   dec.w   R15                     ; Additional delay to ensure start
            jnz     CheckOsc1               ;
            bit.b   #OFIFG,&IFG1            ; OSC fault flag set?
            jnz     CheckOsc                ; OSC Fault, clear flag again
            bic.b   #001h,&P1OUT            ; P1.0= reset
            bis.b   #SELM_3,&BCSCTL2        ; MCLK = LFXT1 - now safe
            bis.b   #OFIE,&IE1              ; re-enable osc fault interrupt
            reti                            ; return from interrupt
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors Used MSP430x13x/14x/15x/16x
;------------------------------------------------------------------------------
            .sect   ".int14"                ; NMI vector
            .short  NMI_ISR                 ;
            .sect     ".reset"              ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
