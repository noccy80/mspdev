;******************************************************************************
;   MSP-FET430P430 Demo - FLL+, MCLK Configured to Operate from XT2 HF XTAL
;
;   Description: Proper selection of an external HF XTAL for MCLK is
;   demonstrated using XT2 OSC. XT2OF is polled until the XTAL is stable -
;   only then is MCLK sourced by XT2. MCLK is buffered on P1.1.
;   ;** HF XTAL NOT INSTALLED ON FET **//
;
;                MSP430FG439
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |            XT2IN|-
;            |                 | XTAL (455k - 8MHz)
;            |           XT2OUT|-
;            |                 |
;            |        P1.1/MCLK|-->MCLK = XTAL
;
;   M. Buccini / M. Mitchell
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430xG43x.h"
;------------------------------------------------------------------------------
            .text                  ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     bis.b   #002h,&P1DIR            ; P1.1 output direction
            bis.b   #002h,&P1SEL            ; P1.1 option select
                                            ;
SetupHF     bic.b   #XT2OFF,&FLL_CTL1       ; Clear bit = high freq xtal on
SetupOsc    bic.b   #OFIFG,&IFG1            ; Clear OSC fault flag
            mov.w   #0FFh,R15               ; R15 = Delay
SetupOsc1   dec.w   R15                     ; Additional delay to ensure start
            jnz     SetupOsc1               ;
            bit.b   #OFIFG,&IFG1            ; Is OSC fault flag set?
            jnz     SetupOsc                ; OSC Fault, clear flag again
            bis.b   #SELM1,&FLL_CTL1        ; MCLK = XT2
                                            ;
Mainloop    jmp     Mainloop                ;
                                            ;
;-----------------------------------------------------------------------------
;           Interrupt Vectors
;-----------------------------------------------------------------------------
            .sect   ".reset"                ; RESET Vector
            .short  RESET                   ;
            .end
