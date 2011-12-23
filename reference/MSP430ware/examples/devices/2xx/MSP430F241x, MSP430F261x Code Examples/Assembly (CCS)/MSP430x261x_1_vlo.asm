;*******************************************************************************
;   MSP430x261x Demo - Software Toggle P1.0, MCLK = VLO/8
;
;   Description; Pulse P1.0 with a 1/100 active duty cycle using software.
;   Ultra-low frequency ~ 1.5kHz, ultra-low power active mode demonstrated.
;   ACLK = VL0, MCLK = VLO/8 ~1.5kHz, SMCLK = n/a
;
;                MSP430F241x
;                MSP430F261x
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |             P1.0|-->LED
;            |        P5.4/MCLK|-->MCLK = VLO/8
;            |        P5.6/ACLK|-->ACLK = VLO
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
SetupBC     bis.b   #LFXT1S_2,&BCSCTL3      ; LFXT1 = VLO
SetupOsc    bic.b   #OFIFG,&IFG1            ; Clear OSC fault flag
            bis.w   #SCG1+SCG0,SR           ; Stop DCO
            bis.b   #SELM_3+DIVM_3,&BCSCTL2 ; MCLK = LFXT1/8
SetupP1     mov.b   #0FFh,&P1DIR            ; All P1.x outputs
            clr.b   &P1OUT                  ; All P1.x reset
SetupP2     clr.b   &P2SEL                  ; All P2.x GPIO function
            mov.b   #0FFh,&P2DIR            ; All P2.x outputs
            clr.b   &P2OUT                  ; All P2.x reset
SetupP3     mov.b   #0FFh,&P3DIR            ; All P3.x outputs
            clr.b   &P3OUT                  ; All P3.x reset
SetupP4     mov.b   #0FFh,&P4DIR            ; All P4.x outputs
            clr.b   &P4OUT                  ; All P4.x reset
SetupP5     mov.b   #0FFh,&P5DIR            ; All P5.x outputs
            clr.b   &P5OUT                  ; All P5.x reset
SetupP6     mov.b   #0FFh,&P6DIR            ; All P6.x outputs
            clr.b   &P6OUT                  ; All P6.x reset   
SetupP7     mov.b   #0FFh,&P7DIR            ; All P7.x outputs
            clr.b   &P7OUT                  ; All P7.x reset
SetupP8     mov.b   #0FFh,&P8DIR            ; All P8.x outputs
            clr.b   &P8OUT                  ; All P8.x reset  
            
            bis.b   #BIT4+BIT6, &P5SEL      ; P5.4= MCLK option select
                                            ; P5.6= ACLK option select
                                            
Mainloop    bis.b   #001h,&P1OUT            ; Set P1.0
Delay1      mov.w   #020,R15                ; Delay to R15
L1          dec.w   R15                     ;
            jnz     L1                      ;
            bic.b   #001h,&P1OUT            ; Reset P1.0
Delay2      mov.w   #02000,R15              ; Delay to R15
L2          dec.w   R15                     ;
            jnz     L2                      ;
            jmp     Mainloop                ; Again
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"            ; POR, ext. Reset
            .short      RESET
            .end

