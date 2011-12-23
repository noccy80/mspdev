;*******************************************************************************
;   MSP430F22x4 Demo - Basic Clock, Implement Cont. SW FLL with Auto RSEL
;
;   Description: Set DCO clock to (Delta)*(4096) using software FLL. DCO clock
;   is output on P1.4 as SMCLK.  DCO clock, which is the selected SMCLK source
;   for timer_A is integrated over ACLK/8 (4096) continuously. CCR2 captures
;   ACLK/8.  To use this SW FLL, Timer_A must be operating in continous mode
;   with a watch crystal used for ACLK. Delta must be kept in a  range that
;   allows possible DCO speeds.  Minimum Delta must ensure
;   the AdjDCO ISR can complete. Maximum delta  can be calculated by
;   f(DCOx7) / 4096.  f(DCOx7) found in device specific datasheet.
;   ACLK = LFXT1/8 = 32768/8, MCLK = SMCLK = DCO = 4096xDelta
;   //* An external watch crystal on XIN XOUT is required for ACLK *//
;
;                MSP430F22x4
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |             P2.1|--> SMCLK = target DCO
;
;  P.Thanigai
;  Texas Instruments Inc.
;  August 2007
;  Built with Code Composer Essentials Version: 2.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430x22x4.h"
;-------------------------------------------------------------------------------
Delta        .set    2930   ; target DCO = DELTA*(4096) = 12MHz
;Delta       .set    977    ; target DCO = Delta*(4096) = 4000000
;Delta       .set    900    ; target DCO = Delta*(4096) = 3686400
;Delta       .set    600    ; target DCO = Delta*(4096) = 2457600
;Delta       .set    256    ; target DCO = Delta*(4096) = 1048576
;Delta       .set    250    ; target DCO = Delta*(4096) = 1024000
;Delta       .set    244    ; target DCO = Delta*(4096) = 1000000
;Delta       .set    078    ; target DCO = Delta*(4096) =  319488
;Delta       .set    070    ; target DCO = Delta*(4096) =  286720
;------------------------------------------------------------------------------
            .text                  			; Program reset
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
            push.w  #0ffffh                 ; LFXT1 startup delay
OscDelay    dec.w   0(SP)                   ; Do calc on the stack
            jnz     OscDelay                ;
            incd.w  SP                      ; Correct SP
SetupP2     bis.b   #002h,&P2DIR            ; P2.1 output
            bis.b   #002h,&P2SEL            ; P2.1 SMCLK output
SetupBC     bis.b   #DIVA_3,&BCSCTL1        ; ACLK = LFXT1CLK/8
Setup_CC2   mov.w   #CM_1+CCIS_1+CAP+CCIE,&TACCTL2  ; CAP,ACLK, with interrupt
Setup_TA    mov.w   #TASSEL_2+MC_2,&TACTL   ; SMCLK, Continous Mode
                                            ;
Mainloop    bis.w   #CPUOFF+GIE,SR          ; CPU off, interrupts enabled
            nop                             ; Needed only for debugger
                                            ;
;-------------------------------------------------------------------------------
TA2_ISR;
;-------------------------------------------------------------------------------
AdjDCO      push.w  &TACCR2                 ;
            sub.w   R15,&TACCR2             ;
            cmp.w   #Delta,&TACCR2          ; Delta = SMCLK/(32768/8)
            pop.w   R15                     ;
            jlo     IncDCO                  ;
            jeq     DoneDCO                 ;
DecDCO      dec.b   &DCOCTL                 ; Slow DCO with DCO and MOD
            jc      DoneDCO                 ; Slower?
            bit.b   #00fh,&BCSCTL1          ; Can RSELx be decremented
            jnc     DoneDCO                 ; No
            dec.b   &BCSCTL1                ; Decrement RSEL.x
            reti                            ; Return from interrrupt
IncDCO      inc.b   &DCOCTL                 ; Speed DCO with DCO and MOD
            jnc     DoneDCO                 ; Faster?
            mov.b   &BCSCTL1,R13            ; Can RSEL.x be increased?
            and.b   #00fh,R13               ;
            cmp.b   #00fh,R13               ;
            jz      DoneDCO                 ; No
            inc.b   &BCSCTL1                ; Increment RSEL.x
DoneDCO     reti                            ; Return from interrrupt
                                            ;
;-------------------------------------------------------------------------------
TAX_ISR;    Common ISR for CCR1-2 and overflow
;-------------------------------------------------------------------------------
            add.w   &TAIV,PC                ; Add Timer_A offset vector
            reti                            ; No interrupt
            reti                            ; TACCR1
            jmp     TA2_ISR                 ; TACCR2
            reti                            ; Reserved
            reti                            ; Reserved
            reti                            ; Overflow
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int08"                ; Timer_AX Vector
            .short  TAX_ISR                 ;
            .end

