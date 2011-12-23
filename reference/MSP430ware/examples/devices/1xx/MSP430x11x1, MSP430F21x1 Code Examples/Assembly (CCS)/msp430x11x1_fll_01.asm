;*******************************************************************************
;   MSP430x11x1 Demo - Basic Clock, Implement Auto RSEL SW FLL
;
;   Description: .set DCO clock to (Delta)*(4096) using software FLL. DCO clock
;   is output on P1.4 as SMCLK.  DCO clock, which is the selected SMCLK source
;   for timer_A is integrated over LFXT1/8 (4096) until SMCLK is is equal
;   to Delta.  CCR2 captures ACLK.  To use Set_DCO Timer_A must be
;   operating in continous mode.  Watch crystal for ACLK is required for
;   this example.  Delta must be kept in a range that allows possible
;   DCO speeds.  Minimum Delta must ensure that Set_DCO loop
;   can complete within capture interval. Maximum delta can be calculated by
;   f(DCOx7) / 4096.  f(DCOx7) can be found in device specific datasheet.
;   ACLK = LFXT1/8 = 32768/8, MCLK = SMCLK = target DCO
;   [] To measure SMCLK on P1.4 with the FET, use "Release JTAG on Run"
;   in the debugger to have access to the port. Then run the code.
;   ;* External watch crystal installed on XIN XOUT is required for ACLK *//	
;
Delta       .equ    900                     ; target DCO=Delta*(4096) = 3686400
;Delta       .equ    600                     ; target DCO=Delta*(4096) = 2457600
;Delta       .equ    250                     ; target DCO=Delta*(4096) = 1024000
;Delta       .equ    78                      ; target DCO=Delta*(4096) =  319488
;Delta       .equ    70                      ; target DCO=Delta*(4096) =  286720
;
;                MSP430F1121
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32k
;          --|RST          XOUT|-
;            |                 |
;            |       P1.4/SMCLK|--> SMCLK = target DCO
;
;   M. Buccini / Z. Albus
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430x11x1.h"
;-------------------------------------------------------------------------------
            .text                           ; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupBC     bis.b   #DIVA_3,&BCSCTL1        ; ACLK = LFXT1CLK/8
SetupP1     bis.b   #010h,&P1DIR            ; P1.4 output
            bis.b   #010h,&P1SEL            ; P1.4 SMCLK output
            call    #Set_DCO                ; Set DCO clock
                                            ;											
Mainloop    bis.w   #CPUOFF,SR              ; CPU is not required
            nop                             ; Required only for debugger
                                            ;
;-------------------------------------------------------------------------------
Set_DCO;    Subroutine: Sets DCO to selected frequency based on Delta.
;           R14 and R15 are used, ACLK= 32768/8 Timer_A clocked by DCOCLK
;-------------------------------------------------------------------------------
            clr.w   R15                     ;							
Setup_CC2   mov.w   #CM_1+CCIS_1+CAP,&CCTL2 ; CAP, ACLK
Setup_TA    mov.w   #TASSEL_2+MC_2,&TACTL   ; SMCLK, Continous Mode
Test_DCO    bit.w   #CCIFG,&CCTL2           ; Test capture flag
            jz      Test_DCO                ;
            bic.w   #CCIFG,&CCTL2           ; Clear capture flag
                                            ;
AdjDCO      mov.w   &CCR2,R14               ; R14 = captured SMCLK
            sub.w   R15,R14                 ; R14 = capture difference
            mov.w   &CCR2,R15               ; R15 = captured SMCLK
            cmp.w   #Delta,R14              ; Delta = SMCLK/(32768/8)
            jlo     IncDCO                  ;
            jeq     DoneDCO                 ;
DecDCO      dec.b   &DCOCTL                 ; Slow DCO with DCO and MOD
            jc      Test_DCO                ; Slower?
            cmp.b   #XT2OFF+DIVA_3,&BCSCTL1 ; Can RSELx be decremented
            jz      Test_DCO
            dec.b   &BCSCTL1                ; Decrement RSEL.x
            jmp     Test_DCO                ;
IncDCO      inc.b   &DCOCTL                 ; Speed DCO with DCO and MOD
            jnc     Test_DCO                ; Faster?
            cmp.b   #XT2OFF+DIVA_3+07h,&BCSCTL1; Can RSEL.x be increased?
            jz      Test_DCO
            inc.b   &BCSCTL1                ; Increment RSEL.x
            jmp     Test_DCO                ;
DoneDCO     clr.w   &CCTL2                  ; Stop CCR2
            clr.w   &TACTL                  ; Stop timer_A
            ret                             ; Return from subroutine
                                            ;
;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
