;*******************************************************************************
;   MSP430F21x2 Demo - Basic Clock, MCLK Sourced from HF XTAL
;
;   Description: Proper selection of an external HF XTAL for MCLK is shown by
;   first polling the OSC fault until XTAL is stable - only then is MCLK
;   sourced by LFXT1. MCLK/10 is on P1.1 driven by a software loop taking
;   exactly 10 CPU cycles.
;   ACLK = MCLK = LFXT1 = HF XTAL, SMCLK = default DCO ~1.2MHz
;   //* HF XTAL NOT INSTALLED ON FET *//
;   //* Min Vcc required varies with MCLK frequency - refer to datasheet *//
;
;                MSP430F21x2
;             -----------------
;         /|\|              XIN|-
;          | |                 | HF XTAL (3  16MHz crystal or resonator)
;          --|RST          XOUT|-
;            |                 |
;            |             P1.1|-->MCLK/10 = HFXTAL/10
;            |             P2.0|-->ACLK = HFXTAL
;
;  JL Bile
;  Texas Instruments Inc.
;  May 2008
;  Built with Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x21x2.h"
;-------------------------------------------------------------------------------
			.text							; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #025Fh,SP  		        ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupBC     bis.b   #XTS,&BCSCTL1           ; LFXT1 = HF XTAL
            bis.b   #LFXT1S1,&BCSCTL3       ; 3  16MHz crystal or resonator
SetupOsc    bic.b   #OFIFG,&IFG1            ; Clear OSC fault flag
            mov.w   #0FFh,R15               ; R15 = Delay
SetupOsc1   dec.w   R15                     ; Additional delay to ensure start
            jnz     SetupOsc1               ;
            bit.b   #OFIFG,&IFG1            ; OSC fault flag set?
            jnz     SetupOsc                ; OSC Fault, clear flag again
            bis.b   #SELM_3,&BCSCTL2        ; MCLK = LFXT1
                                            ;
            bis.b   #001h,&P2DIR            ; P2.0 = output direction
            bis.b   #001h,&P2SEL            ; P2.0 = ACLK function
            bis.b   #002h,&P1DIR            ; P1.1 = output direction
                                            ;
Mainloop    bis.b   #002h,&P1OUT            ; P1.1 = 1
            bic.b   #002h,&P1OUT            ; P1.1 = 0
            jmp     Mainloop                ; Repeat
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
           	.sect	".reset"            ; POR, ext. Reset
            .short	RESET
            .end
