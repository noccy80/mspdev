;*******************************************************************************
;   MSP430x41x2 Demo - Software Toggle P5.1, MCLK = VLO/8
;
;   Description; Pulse P5.1 with a 1/100 active duty cycle using software.
;   Ultra-low frequency ~ 1.5kHz, ultra-low power active mode demonstrated.
;   ACLK = VL0, MCLK = VLO/8 ~1.5kHz, SMCLK = n/a
;
;                MSP430F41x2
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |             P5.1|-->LED
;            |        P1.1/MCLK|-->MCLK = VLO
;            |        P1.6/ACLK|-->ACLK = VLO
;   
;  P. Thanigai
;  Texas Instruments Inc.
;  January 2009
;  Built with CCE Version: 3.1   
;******************************************************************************
 .cdecls C,LIST, "msp430x41x2.h" 
 
            .global _main
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
_main
RESET       mov.w   #0400h,SP               ; Initialize stack pointer
            mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupFLL    bis.b   #SELM0+SELM1,&FLL_CTL1  ; MCLK = VLO
            bis.b   #LF1XT1S_2,&FLL_CTL2    ; ACLK = VLO            
SetupOsc    bic.b   #OFIFG,&IFG1            ; Clear OSC fault flag
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

            
            bis.b   #BIT1+BIT6, &P1SEL      ; P1.1= MCLK option select
                                            ; P1.6= ACLK option select
                                            
Mainloop    bis.b   #002h,&P5OUT            ; Set P5.1
Delay1      mov.w   #020,R15                ; Delay to R15
L1          dec.w   R15                     ;
            jnz     L1                      ;
            bic.b   #002h,&P5OUT            ; Reset P5.1
Delay2      mov.w   #02000,R15              ; Delay to R15
L2          dec.w   R15                     ;
            jnz     L2                      ;
            jmp     Mainloop                ; Again
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;  
            .end

