;*******************************************************************************
;   MSP430x261x Demo - Basic Clock, MCLK Sourced from HF XTAL
;
;   Description: Proper selection of an external HF XTAL for MCLK is shown by
;   first polling the OSC fault until XTAL is stable - only then is MCLK
;   sourced by LFXT1. MCLK/10 is on P1.1 driven by a software loop taking
;   exactly 10 CPU cycles.
;   ACLK = MCLK = LFXT1 = HF XTAL, SMCLK = default DCO ~1.045MHz
;   //* HF XTAL NOT INSTALLED ON FET *//
;   //* Min Vcc required varies with MCLK frequency - refer to datasheet *//
;
;                MSP430F241x
;                MSP430F261x
;             -----------------
;         /|\|              XIN|-
;          | |                 | HF XTAL (3  16MHz crystal or resonator)
;          --|RST          XOUT|-
;            |                 |
;            |             P1.1|-->MCLK/10 = HFXTAL/10
;            |        P5.4/MCLK|-->MCLK = XT2 HFXTAL
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x26x.h"
;-------------------------------------------------------------------------------
			.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #0850h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT

SetupBC     bic.b   #XT2OFF,&BCSCTL1        ; Activate XT2 high freq xtal
            bis.b   #XT2S_2,&BCSCTL3        ; 3  16MHz crystal or resonator

SetupOsc    bic.b   #OFIFG,&IFG1            ; Clear OSC fault flag
            mov.w   #0FFh,R15               ; R15 = Delay
SetupOsc1   dec.w   R15                     ; Additional delay to ensure start
            jnz     SetupOsc1               ;
            bit.b   #OFIFG,&IFG1            ; OSC fault flag set?
            jnz     SetupOsc                ; OSC Fault, clear flag again
                                           
            bis.b   #SELM_2, &BCSCTL2       ; MCLK = XT2 HF XTAL (safe)
                                            
            bis.b   #010h,&P5DIR            ; P5.4 = output direction
            bis.b   #010h,&P5SEL            ; P5.4 = ACLK function
            bis.b   #002h,&P1DIR            ; P1.1 = output direction

Mainloop    bis.b   #002h,&P1OUT            ; P1.1 = 1
            bic.b   #002h,&P1OUT            ; P1.1 = 0
            jmp     Mainloop                ; Repeat
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"	           ; POR, ext. Reset, Watchdog
            .short  RESET
            .end
            