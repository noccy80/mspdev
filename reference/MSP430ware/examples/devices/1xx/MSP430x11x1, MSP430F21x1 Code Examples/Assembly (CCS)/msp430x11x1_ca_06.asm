;*******************************************************************************
;   MSP430x11x1 Demo - Comp_A, Thermometer 0-50 C
;
;   Description: Comparator_A is used to measure a resistance value of an
;   10k-NTC (25C) and converted to temperature (oC). Discharge times of a 0.1uf
;   capacitor through a 10k-NTC (25C) and 10k ohm reference resistor are
;   measured using Timer_A CCR1. The times are compared and the ratio
;   converted to an absolute temperature. The resulting temperature is placed
;   in R11 (00 - 50). Normal operating mode is LPM0, Timer_A overflow clocked
;   from SMCLK sets wakeup time ~80ms.
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
            mov.b   #CARSEL+CAREF0+CAON,&CACTL1   ; -Comp = 0.25*Vcc -  on
            mov.b   #P2CA0,&CACTL2                ; +Comp = P2.3
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
            call    #RES_2_C                ; R11 = oc
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
            mov.w   #CM_2+CCIS_1+CAP+CCIE,&CCTL1    ; Neg, CCIB,Cap,interrupt
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
RES_2_C;    Convert Resistance (R14) to Degrees C (R11) using RES_TAB
;           Input:  R14, R12 are working registers
;           Output: R11
;-------------------------------------------------------------------------------
            clr.w   R12                     ; R12 Used as Pointer
            mov.w   #00h,R11                ; R11 Used as Temperature Counter
CMPR        cmp.w   RES_TAB(R12),R14        ; Compare Table Value to Sensor
            jhs     End_RES_2_C             ; Jump if Sensor > Table
            incd.w  R12                     ; Increment word Pointer
            dadd.b  #01h,R11                ; Add 1 from Counter
            jmp     CMPR                    ;
End_RES_2_C ret                             ; Return from subroutine
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
;   Resistance table, K ohms to 0-50 degrees C.
;-------------------------------------------------------------------------------
            .align 2                        ; Evenly aligned
RES_TAB     .short 27280                    ; oC
            .short 26130
            .short 25030
            .short 23990
            .short 23000
            .short 22050
            .short 21150
            .short 20300
            .short 19480
            .short 18700
            .short 17960
            .short 17240
            .short 16560
            .short 15900
            .short 15280
            .short 14690
            .short 14120
            .short 13580
            .short 13060
            .short 12560
            .short 12090
            .short 11630
            .short 11200
            .short 10780
            .short 10380
            .short 10000                ; 25c
            .short 9632
            .short 9281
            .short 8944
            .short 8622
            .short 8313
            .short 8014
            .short 7728
            .short 7454
            .short 7192
            .short 6940
            .short 6699
            .short 6467
            .short 6245
            .short 6032
            .short 5827
            .short 5629
            .short 5438
            .short 5255
            .short 5080
            .short 4911
            .short 4749
            .short 4593
            .short 4443
            .short 4299
            .short 4160                     ; 50c
                                            ;
;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int08"                ; Timer_AX Vector
            .short  TAX_ISR                 ;
            .end
