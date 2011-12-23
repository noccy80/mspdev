;*******************************************************************************
;   MSP430x11x1 Demo - Comp_A, Thermometer 59-99 F
;
;   Description: Comparator_A is used to measure a resistance value of
;   an 10k-NTC (25c) and converted to temperature (oF). Discharge times
;   of a 0.1uf capacitor through a 10k-NTC (25C) and 10k ohm reference
;   resistor are measured using Timer_A CCR1. The times are compared
;   and the ratio converted to an absolute temperature. The resulting
;   temperature is placed in R11 (59 - 99).
;   ACLK = n/a, MCLK = SMCLK = default DCO ~800k
;
;		         MSP430F1121
;             -----------------
;        /|\ |              XIN|-
;         |  |                 |
;         ---|RST          XOUT|-
;            |                 |
;      +-10k-|P2.0             |
;      |     |                 |	
;      +-NTC-|P2.1             |
;      |     |                 |
;      +-----|P2.3             |
;      |     |                 |
;     ===.1uf|                 |
;      |     |                 |			
;      ------|VSS
;
;            NTC = 10k @25c, (P/N 271-110A Radio Shack)
;
Ref         .equ    001h	            ; P2.0 = Reference
Sensor      .equ    002h	            ; P2.1 = Sensor
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
            mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop Watchdog Timer
            bic.b   #Sensor+Ref,&P2OUT      ; Sensor, Ref reset
            bic.b   #Sensor+Ref,&P2DIR      ; Sensor, Ref input
            mov.b   #008h, &CAPD            ; Disconnect port pins
            mov.b   #CARSEL+CAREF0+CAON,&CACTL1; -Comp = 0.25*Vcc -  on
            mov.b   #P2CA0,&CACTL2          ; +Comp = P2.3
            mov.w   #TASSEL_2+MC_2,&TACTL   ; SMCLK, contmode
            eint                            ; General interrupt enable
                                            ;								
Mainloop    mov.w   #Sensor,R14             ; R14 = discharge pin
            call    #Measure                ; R14 = Sensor discarge time
            mov.w   R14,R11                 ; R11 = Sensor discharge time			
            mov.w   #Ref,R14                ; R14 = discharge pin
            call    #Measure                ; R14 = Ref discharge time
            push.w  R14                     ; TOS = Ref discharge time
                                            ;
;Calculate   mov.w   #10000,R12              ;
Calculate   mov.w   #9870,R12               ;
            call    #MPYU                   ; Sensor (R11)*10000 = R15 | 14
            pop.w   R11                     ; R11 = Ref discharge time
            mov.w   R14,R12                 ;
            mov.w   R15,R13                 ;
            call    #DIVIDE                 ; R14 = Sensor*10000/Ref
            call    #RES_2_F                ; R11 = oF
            jmp     Mainloop                ; Repeat, Place Breakpoint Here
                                            ;
;-------------------------------------------------------------------------------
Measure;    Input:  R14 = Sensor or Ref P2.x bit location
;           Output:  R14 = Sensor or Ref discharge time
;-------------------------------------------------------------------------------
Charge;     Capacitor is charged via Ref
            bis.b   #Ref,&P2OUT             ; Ref .set
            bis.b   #Ref,&P2DIR             ; Ref output
            mov.w   &TAR,&CCR1              ; CCR1 = TAR
            add.w   #5000,&CCR1             ; CCR1 ~ TAR+5ms (5tu)
            mov.w   #CCIE,&CCTL1            ; Compare mode,interrupt enable
            bis.w   #LPM0,SR                ; Wait for CCR1 interrupt				
            bic.b   #Ref,&P2DIR             ; Ref = HiZ, Charge complete
            bic.b   #Ref,&P2OUT             ; Ref = Reset						
Discharge;  Measure Discharge Time
            mov.w   #CM_2+CCIS_1+CAP+CCIE,&CCTL1; Neg, CCIB,Cap,interrupt
            push.w  &TAR                    ; TOS = TAR at SOC
            bis.b   R14,&P2DIR              ; R14 = Sensor or REF
            bis.w   #LPM0,SR                ; Wait for CCR1 interrupt				
            mov.w   &CCR1,R14               ; R14 = TAR (CCR1) at EOC
            sub.w   @SP+,R14                ; R14 = discharge time
            bic.b   #Sensor+Ref,&P2DIR      ; Disable Sensor or Ref
            clr.w   &CCTL1                  ; Disable CCTL1
            ret                             ; Return from subroutine
                                            ;
;-------------------------------------------------------------------------------
MPYU   ;    Unsigned Multipy R11 x R12 = R15 | R14
       ;    Input:  R11, R12 , R10 = working register
       ;    Output: R15, R14
;-------------------------------------------------------------------------------
            clr.w   R14                     ; 0 -> LSBs result
            clr.w   R15                     ; 0 -> MSBs result
MACU        clr.w   R13                     ; MSBs multiplier
            mov.w   #1,R10                  ; bit test register
MPY2        bit.w   R10,R11                 ; test actual bit
            jz      MPY1                    ; IF 0: do nothing
            add.w   R12,R14                 ; IF 1: add multiplier to result
            addc.w  R13,R15                 ;
MPY1        rla.w   R12                     ; multiplier x 2
            rlc.w   R13                     ;
            rla.w   R10                     ; next bit to test
            jnc     MPY2                    ; if bit in carry: finished
            ret                             ; Return from subroutine
                                            ;
;-------------------------------------------------------------------------------
DIVIDE ;    Unsigned 32/16 divide R13 | R12 / R11 = R14
       ;    Input:  R13, R12, R10 is a working register
       ;    Output: R14
;-------------------------------------------------------------------------------
            clr.w   R14                     ; Clear Accumulator Low
            mov.w   #17,R10                 ; Initalize Loop Counter
DIV1        cmp.w   R11,R13                 ;
            jlo     DIV2                    ;
            sub.w   R11,R13                 ;
DIV2        rlc.w   R14                     ;
            jc      DIV4                    ; Error: result > 16 bits
            dec.w   R10                     ; Decrement loop counter
            jz      DIV4                    ; Is 0: terminate w/o err
            rla.w   R12                     ;
            rlc.w   R13                     ;
            jnc     DIV1                    ;
            sub.w   R11,R13                 ;
            setc                            ;
            jmp     DIV2                    ;
DIV4        ret                             ; Error indication in C
                                            ;
;-------------------------------------------------------------------------------
RES_2_F;    Convert Resistance (R14) to Degrees F (R11) using RES_TAB
;           Input:  R14, R12 is a working register
;           Output: R11
;-------------------------------------------------------------------------------
            clr.w   R12                     ; R12 Used as Pointer
            mov.w   #99h,R11                ; R11 Used as Temperature Counter
CMPR        cmp.w   RES_TAB(R12),R14        ; Compare Table Value to Sensor
            jlo     End_RES_2_F             ; Jump if Sensor < Table
            incd.w  R12                     ; Increment word Pointer
            dadd.b  #99h,R11                ; Subtract 1 from Counter
            jmp     CMPR                    ;
End_RES_2_F ret                             ; Return from subroutine
                                            ;
;-------------------------------------------------------------------------------
TAX_ISR;    Common ISR for CCR1-4 and overflow
;-------------------------------------------------------------------------------
            add.w   &TAIV,PC                ; Add TA interrupt offset to PC
            reti                            ; CCR0 - no source
            jmp     CCR1_ISR                ; CCR1
;            reti                            ; CCR2
;            reti                            ; CCR3
;            reti                            ; CCR4
;TA_over     reti                            ; Timer_A overflow
                                             ;
CCR1_ISR    bic.w   #LPM0,0(SP)             ; Exit LPM0 on reti
            reti                            ;
                                            ;
;-------------------------------------------------------------------------------
;   Resistance table, K ohms to 99-59 degrees F.
;-------------------------------------------------------------------------------
RES_TAB     .align 2                        ; Evenly aligned
            .short  6446                    ;99 F
            .short  6570
            .short  6693
            .short  6817                    ;96 F
            .short  6941                    ;95 F
            .short  7093
            .short  7245
            .short  7398
            .short  7550
            .short  7703                    ;90 F
            .short  7856
            .short  8008
            .short  8161
            .short  8313
            .short  8500                    ;85 F
            .short  8688
            .short  8875
            .short  9063
            .short  9250
            .short  9438                    ;80 F
            .short  9625
            .short  9813
            .short  10000
            .short  10232
            .short  10464                   ;75 F
            .short  10697
            .short  10929
            .short  11161
            .short  11393
            .short  11626                   ;70 F
            .short  11858
            .short  12090
            .short  12378
            .short  12666
            .short  12953                   ;65 F
            .short  13241                   ;64 F
            .short  13529
            .short  13817
            .short  14104
            .short  14392
            .short  14680                   ;59 F
                                            ;
;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int08"                ; Timer_AX Vector
            .short  TAX_ISR                 ;
            .end
