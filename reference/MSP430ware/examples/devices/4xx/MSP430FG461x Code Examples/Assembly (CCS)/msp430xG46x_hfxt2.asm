;******************************************************************************
;   MSP430xG46x Demo - FLL+, MCLK Configured to Operate from XT2 HF XTAL
;
;   Description: Proper selection of an external HF XTAL for MCLK is
;   demonstrated using HF XT2 OSC.  OFIFG is polled until the HF XTAL
;   is stable - only then is MCLK sourced by XT2.  MCLK is buffered on P1.1.
;   //** HF XTAL NOT INSTALLED ON FET **//
;
;                MSP430xG461x
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |                 |
;            |            XT2IN|-
;            |                 | HF XTAL (455kHz - 8MHz)
;            |           XT2OUT|-
;            |                 |
;            |                 |
;            |        P1.1/MCLK|-->MCLK = HF XTAL
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430xG46x.h"
;-------------------------------------------------------------------------------
			.text	;Program Start
;-----------------------------------------------------------------------------
RESET       mov.w   #900,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
            bis.b   #OSCOFF+SCG0,SR         ; Disable LFXT1 xtal osc & FLL loop
SetupHF     bic.b   #XT2OFF,&FLL_CTL1       ; Clear bit = high freq xtal on
ClearFlag   bic.b   #OFIFG,&IFG1            ; Clear osc fault flag
            mov     #0F000h,R15             ; Move delay time to register 15
HF_Wait     dec     R15                     ; Delay for xtal to start, FLL lock
            jnz     HF_Wait		    ; Loop if delay not finished

            bit.b   #OFIFG,&IFG1            ; Test osc fault flag
            jnz     ClearFlag               ; If not loop again
                                            ;
            bis.b   #SELM1,&FLL_CTL1        ; MCLK = XT2
                                            ;
SetupP1     bis.b   #002h,&P1DIR            ; P1.1 output direction
            bis.b   #002h,&P1SEL            ; P1.1 option select

Mainloop    jmp     Mainloop                ;
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ; POR, ext. Reset, Watchdog
            .short   RESET
            .end
