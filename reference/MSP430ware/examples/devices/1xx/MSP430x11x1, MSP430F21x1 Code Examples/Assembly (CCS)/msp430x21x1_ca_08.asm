;*****************************************************************************
;   MSP430x21x1 Demo - Comp_A, Millivolt Meter
;
;   Description: This program demonstrates how to implement an MSP430F21x1/
;   MSP430F11x1 millivolt meter using Comparator_A. The measurement result can
;   be readout of variable 'ADCRESULT' using the watch window.
;   ACLK = n/a, MCLK = SMCLK = default DCO
;
;             MSP430F21x1/11x1
;            -----------------
;       /|\ |              XIN|-
;        |  |                 |
;        ---|RST          XOUT|-
;           |                 |
;    AIN--->|P2.4             |
;           |                 |
;    +-10k--|P2.0             |
;    |      |                 |
;    +----- |P2.3             |
;    |      |                 |
;   ===2.2  |                 |
;    |      |                 |
;    ------ |VSS              |
;
;
;  H. Grewal / A. Dannenberg
;  Texas Instruments Inc.
;  July 2005
;  Built with Code Composer Essentials Version: 1.0
;*****************************************************************************
 .cdecls C,LIST,  "msp430x11x1.h"

VCC_VALUE   .equ   2980
ADCRESULT .equ R4
Result    .equ R5
Counter   .equ R7
Result2   .equ R9
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stackpointer
            mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
            mov.b   #020h,&P2OUT            ; P2.5 high
            mov.b   #021h,&P2DIR            ; P2.0 = DAC, P2.5 powers pot
            mov.b   #P2CA0+P2CA1,&CACTL2    ; Setup CA, P2.3+ P2.4-
            mov.b   #050h,&DCOCTL           ; Set DCO
            mov.b   #0CCh,&BCSCTL1
Mainloop    call    #Meas_ADC
            mov.w   Result,ADCRESULT
            nop
            jmp     Mainloop

;------------------------------------------------------------------------------
Meas_ADC;
;------------------------------------------------------------------------------
            mov.b   #CAON,&CACTL1           ; Comparator on
            call    #Meas_ADC2              ; Do 1st ADC conversion
            mov.w   Result2,Result
            bis.b   #CAEX,&CACTL1           ; Invert comparator terminals
            call    #Meas_ADC2              ; 2nd ADC, add inverted result
            add.w   Result2,Result
            clr.b   &CACTL1                 ; Comparator off
            ret                             ;
                                            ;
;------------------------------------------------------------------------------
Meas_ADC2;
;------------------------------------------------------------------------------
            mov.w   #VCC_VALUE,R8
            rra.w   R8
            mov.w   R8,Counter
            clr.w   Result2
            bis.b   #01h,&P2OUT             ; .set power to capacitor
test        bit.b   #01h,&CACTL2            ; Wait for CAOUT to get .set
            jnc     test
tstCA       bit.b   #01h,&CACTL2            ; Comparator high/low?
            jnc     itslow
            bic.b   #01h,&P2OUT             ; Remove power if high
            jmp     whloop
itslow      bis.b   #01h,&P2OUT             ; Set power if low
            inc.w   Result2                 ; Measure the 'ON' time
            nop
whloop      dec.w   Counter                 ; Decrement and loop
            jnz     tstCA                   ;
            bic.b   #01h,&P2OUT             ; Remove power from cap
            ret                             ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect ".reset"                  ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
