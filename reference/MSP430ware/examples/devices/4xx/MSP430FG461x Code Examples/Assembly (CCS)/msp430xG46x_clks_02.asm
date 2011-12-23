;*******************************************************************************
;   MSP430xG46x Demo - FLL+, Output 32kHz Xtal + HF Xtal + Internal DCO
;
;   Description: This program demonstrates using an external 32kHz crystal to
;   source ACLK, and using a high speed crystal or resonator to source SMCLK.
;   MLCK for the CPU is supplied by the internal DCO. The 32kHz crystal
;   connects between pins XIN and XOUT. The high frequency crystal or
;   resonator connects between pins XT2IN and XT2OUT. The DCO clock is
;   generated internally and calibrated from the 32kHz crystal. ACLK is
;   brought out on P1.5, SMCLK is brought out on P1.4, and MCLK on pin P1.1.
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   //* An external watch crystal between XIN & XOUT is required for ACLK *//	
;
;   NOTE: External matching capacitors must be added for the high speed
;         crystal or resonator as required.
;  //* External XTALs are required and not installed on FET *//	
;
;                 MSP430xG46x
;             -----------------
;        /|\ |              XIN|-
;         |  |                 | 32kHz crystal
;         ---|RST          XOUT|-
;            |                 |
;            |                 |
;            |            XT2IN|-
;            |                 | HF XTAL (455k - 8Mhz) (add caps as needed)
;            |           XT2OUT|-
;            |                 |
;            |                 |
;            |        P1.1/MCLK|--> MCLK = Default DCO Frequency
;            |       P1.4/SMCLK|--> SMCLK = HF XTAL
;            |        P1.5/ACLK|--> ACLK = 32kHz
;            |                 |
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
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps

SetupHF     bic.b   #XT2OFF,&FLL_CTL1       ; Clear bit = high freq xtal on
ClearFlag   bic.b   #OFIFG,&IFG1            ; Clear osc fault flag
            mov     #0F000h,R15             ; Move delay time to register 15
HF_Wait     dec     R15                     ; Delay for xtal to start, FLL lock
            jnz     HF_Wait		    ; Loop if delay not finished
            bit.b   #OFIFG,&IFG1            ; Test osc fault flag
            jnz     ClearFlag               ; If not loop again
SwitchHF    bis.b   #SELS,&FLL_CTL1         ; Is reset so switch SMCLK = HF xtal
                                            ;
SetupPorts  bis.b   #032h,&P1DIR            ; P1.1, P1.4 & P1.5 to outputs
            bis.b   #032h,&P1SEL            ; P1.1, P1.4 & P1.5 functions
                                            ; set to output
                                            ; MCLK, SMCLK & ACLK
Mainloop    jmp     Mainloop                ; Loop with CPU running
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect 	".reset"	           ; MSP430 RESET Vector
            .short   RESET                   ;
            .end


