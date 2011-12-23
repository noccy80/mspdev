;******************************************************************************
;   MSP-FET430P140 Demo - Basic Clock, MCLK Sourced from HF XTAL XT2
;
;   Description: Proper selection of an external HF XTAL for MCLK is shown
;   by first polling the OSC fault until XTAL is stable - only then is MCLK
;   source switched to XT2.  MCLK is on P5.4.
;   ACLK = n/a, MCLK = XT2 = HF XTAL
;   //* HF XTAL NOT INSTALLED ON FET *//
;   //* Min Vcc required varies with MCLK frequency - refer to datasheet *//	
;
;                MSP430F149
;             -----------------
;         /|\|            XT2IN|-
;          | |                 | XTAL (455k - 8Mhz)
;          --|RST        XT2OUT|-
;            |                 |
;            |             P5.4|-->MCLK = XTAL
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
SetupP5     bis.b   #010h,&P5DIR            ; P5.4 = output
            bis.b   #010h,&P5SEL            ; P5.4 = MCLK option select
                                            ;
SetupBC     bic.b   #XT2OFF,&BCSCTL1        ; XT2 = on
SetupOsc    bic.b   #OFIFG,&IFG1            ; Clear OSC fault flag
            mov.w   #0FFh,R15               ; R15 = Delay
SetupOsc1   dec.w   R15                     ; Additional delay to ensure start
            jnz     SetupOsc1               ;
            bit.b   #OFIFG,&IFG1            ; OSC fault flag set?
            jnz     SetupOsc                ; OSC Fault, clear flag again
            bis.b   #SELM_2,&BCSCTL2        ; MCLK = XT2 (safe)
                                            ;
Mainloop    jmp     Mainloop                ; Do nothing
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
