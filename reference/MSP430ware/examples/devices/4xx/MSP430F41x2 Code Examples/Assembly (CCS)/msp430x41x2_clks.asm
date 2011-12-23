;*****************************************************************************
; MSP430F41x2 Demo - FLL+, Output Buffered SMCLK, ACLK
;
;  Description: Buffer ACLK on P1.6 and MCLK(DCO) on P1.1.
;  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO
;  //* An external watch crystal between XIN & XOUT is required for ACLK *//
;
;                MSP430F41x2
;            -----------------
;        /|\ |              XIN|-
;         |  |                 | 32kHz
;         ---|RST          XOUT|-
;            |                 |
;            |                 |
;            |                 |
;            |        P1.6/ACLK|--> ACLK = 32768 Hz
;            |                 |
;            |        P1.1/MCLK|--> MCLK = 1048576 Hz (Default DCO)
;            |                 |
;            |                 |
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
SetupWDT    mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupFLL2   bis.b   #XCAP18PF,&FLL_CTL0     ; Set load capacitance for 32k xtal

ClearFlag   bic.b   #OFIFG,&IFG1            ; Clear osc fault flag
            mov     #0F000h,R15             ; Move delay time to register 15
Wait        dec     R15                     ; Delay for xtal to start, FLL lock
            jnz     Wait        		    ; Loop if delay not finished
            bit.b   #OFIFG,&IFG1            ; Test osc fault flag
            jnz     ClearFlag               ; If not loop again
                                            ;
SetupPorts  bis.b   #BIT1+BIT6,&P1DIR       ; P1.1,P1.6 to outputs
            bis.b   #BIT1+BIT6,&P1SEL       ; P1.1,P1.6 functions
                                            ; MCLK & ACLK

Mainloop    jmp     Mainloop                ; Loop with CPU running
                                            ;
;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;  
            .end
