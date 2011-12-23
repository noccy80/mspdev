;******************************************************************************
;   MSP-FET430P120 Demo - Basic Clock, LFXT1/MCLK Sourced from HF XTAL, NMI
;
;   Description: Proper selection of an external HF XTAL for MCLK is shown with
;   enabled OSC fault interrupt - if HF XTAL fails, NMI interrupt is requested.
;   HF XTAL can only source MCLK when OSC fault is clear. For demonstration
;   purposes P1.0 is .set during OSC fault. MCLK/10 is on P1.1.
;   ACLK = MCLK = LFXT1 = HFXTAL
;   //* HF XTAL NOT INSTALLED ON FET *//
;   //* Min Vcc required varies with MCLK frequency - refer to datasheet *//	
;
;                MSP430F123(2)
;             -----------------
;         /|\|              XIN|-
;          | |                 | HF XTAL (455k - 8Mhz)
;          --|RST          XOUT|-
;            |                 |
;            |             P1.1|-->MCLK/10
;            |             P1.0|-->LED
;
;   M. Buccini / M. Raju
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x12x2.h"
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0300h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupBC     bis.b   #XTS,&BCSCTL1           ; LFXT1 = HF XTAL
            bis.b   #OFIE,&IE1              ; Enable osc fault interrupt
SetupP1     bis.b   #003h,&P1DIR            ; P1.0,1 = output direction
            bic.b   #001h,&P1OUT            ; P1.0 = reset
                                            ;
Mainloop    bis.b   #002h,&P1OUT            ; P1.1 = 1
            bic.b   #002h,&P1OUT            ; P1.1 = 0
            jmp     Mainloop                ; Repeat
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
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".int14"                ; NMI vector
            .short  NMI_ISR                 ;
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
