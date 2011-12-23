;*******************************************************************************
;   MSP430x11x1 Demo - Comp_A, Resistance Meter
;
;   Description: Comparator_A is used to measure a resistance value. Charge
;   times of a 0.1uf capacitor through a resistive element and 10k ohm
;   reference resistor are measured using Timer_A CCR1. The times are compared
;   and the resistance of the element calculated and made available in R14|13.
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
;      +-Rx--|P2.1             |
;      |     |                 |
;      +-----|P2.3             |
;      |     |                 |
;     ===.1uf|                 |
;      |     |                 |			
;      ------|VSS
;
;            Rx = 1k - 50k
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
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop Watchdog Timer
SetupP2     bic.b   #Sensor+Ref,&P2OUT      ; Sensor, Ref reset
            bic.b   #Sensor+Ref,&P2DIR      ; Sensor, Ref input
SetupCA     mov.b   #008h, &CAPD            ; Disconnect port pins
            mov.b   #CARSEL+CAREF0+CAON,&CACTL1; -Comp = 0.25*Vcc -  on
            mov.b   #P2CA0,&CACTL2          ; +Comp = P2.3
SetupTA     mov.w   #TASSEL_2+MC_2,&TACTL   ; SMCLK, cont mode
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
            mov.w   R14,R12
            call    #BIN2BCD                ; R14|R13 = resistance
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
       ;      Input: R11, R12
       ;    Working: R10 is used and not saved
       ;     Output: R15, R14
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
       ;      Input: R13, R12
       ;    Working: R10 is used and not saved
       ;     Output: R14
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
BIN2BCD;     Subroutine for converting 16 bit binary to BCD
;              Input: R12 is 16 bit binary
;            Working: R15 is used and not saved
;             Output: R14|R13 5 digit BCD
;-------------------------------------------------------------------------------
             mov    #16,R15
             clr    R14
             clr    R13
L$1          rla    R12
             dadd   R13,R13
             dadd   R14,R14
             dec    R15
             jnz    L$1
             ret
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
                                            ;
;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int08"                ; Timer_AX Vector
            .short  TAX_ISR                 ;
            .end
