;*******************************************************************************
;   MSP430x11x1 Demo - Software Output 6-Bit R2R DAC
;
;   Description: Implement a 6-bit DAC using 6 P2.x outputs and an R2R
;   ladder.  A sine wave is generated using a 6-bit, 32-step sine look-up
;   table Sin_Tab.  R5 is used as a pointer into Sin_Tab.  Any MSP430
;   outputs can be used for the DAC with their bit-resolutions and
;   frequencies possible.  ACLK as an input to CCR2 is used to trigger an
;   interrupt at exacty 32768Hz.  The ISR updates the DAC using
;   Sin_Tab.  The frequency of the sine wave in this example is ISR
;   frequency/steps = 32768/32 = 1024hz.
;   ACLK = LFXT1 = 32768, MCLK = SMCLK = default DCO ~800k
;   ;* An external watch crystal on XIN XOUT is required for ACLK *//	
;
;
;                MSP430F1121
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |             P2.5|--20k--+---> 1024hz sine wave
;            |                 |      10k
;            |             P2.4|--20k--+
;            |                 |      10k
;            |             P2.3|--20k--+
;            |                 |      10k
;            |             P2.2|--20k--+
;            |                 |      10k
;            |             P2.1|--20k--+
;            |                 |      10k
;            |             P2.0|--20k--+
;            |                 |      20k
;                                      |
;                                      V
;   M. Buccini / Z. Albus
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430x11x1.h"
;-------------------------------------------------------------------------------
            .text                           ; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #0300h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop watchdog timer
SetupBC     bis.b   #RSEL2+RSEL0,&BCSCTL1   ; RSEL=5
SetupP2     mov.b   #03Fh,&P2DIR            ; P2.0 - 5 output direction
            clr.w   R5                      ; Clear pointer
Setup_CC2   mov.w   #CCIS0+CM0+CAP+CCIE,&CCTL2 ; CCR2,CAP on CCxB,ACLK,int				
SetupTA     mov.w   #TASSEL_2+MC_2,&TACTL   ; SMCLK, contmode
            eint                            ; Enable interrupts
                                            ;
Mainloop    jmp     Mainloop                ; Do Nothing
                                            ;
;-------------------------------------------------------------------------------
TAX_ISR;    Common ISR for CCR1-4 and overflow
;-------------------------------------------------------------------------------
            add.w   &TAIV,PC                ; Add TA interrupt offset to PC
            reti                            ; CCR0 - no source
            reti                            ; CCR1
            jmp     CCR2_ISR                ; CCR2
;            reti                            ; CCR3
;            reti                            ; CCR4
;TA_over     reti                            ; Timer_A overflow
                                            ;
CCR2_ISR    mov.b   Sin_tab(R5),&P2OUT      ; Move sine value to P2
            inc.b   R5                      ; Inc pointer
            and.b   #01Fh,R5                ; R5 = 0 - 31 only (32 bytes)
            reti                            ;
;-------------------------------------------------------------------------------
Sin_tab;    Sine 6-bit Lookup table with 32 steps
;-------------------------------------------------------------------------------
            .byte  32
            .byte  38
            .byte  44
            .byte  49
            .byte  54
            .byte  58
            .byte  61
            .byte  62
            .byte  63
            .byte  62
            .byte  61
            .byte  58
            .byte  54
            .byte  49
            .byte  44
            .byte  38
            .byte  32
            .byte  25
            .byte  19
            .byte  14
            .byte  9
            .byte  5
            .byte  2
            .byte  1
            .byte  0
            .byte  1
            .byte  2
            .byte  5
            .byte  9
            .byte  14
            .byte  19
            .byte  25
                                            ;
;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int08"                ; Timer_AX Vector
            .short  TAX_ISR                 ;
            .end
