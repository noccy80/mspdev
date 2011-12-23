;******************************************************************************
;   MSP430x21x1 Demo - OFIFG ISR for LF Failsafe Operation
;
;   Description: Toggle P1.0 using software timed by the WDT ISR. Toggle rate
;   is approximately 250ms based on 32768Hz ACLK when present. When the LFXT1
;   input signal faults during operation, the NMI ISR is entered and the fault
;   is serviced. During this time the LED will flash at a faster rate indicating
;   an ACLK fault. During this time the CPU is held in the NMI ISR.
;
;   ACLK = 32768 Hz, MCLK = SMCLK = ~1.16 MHz
;
;               MSP430F21x1
;             -----------------
;         /|\|              XIN|-
;          | |                 |  32.768kHz
;          --|RST          XOUT|-
;            |                 |
;            |             P1.0|-->LED
;
;   H. Grewal / A. Dannenberg
;   Texas Instruments, Inc
;   June 2005
;   Built with Code Composer Essentials Version: 1.0
;*****************************************************************************
 .cdecls C,LIST,  "msp430x21x1.h"
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0300h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDT_ADLY_250,&WDTCTL   ; Set WDT interval to ~250ms from ACLK
            bis.b   #OFIE,&IE1              ; Enable osc fault interrupt
            bis.b   #WDTIE,&IE1             ; Enable WDT interrupt
                                            ;
            mov.b   #0,&P1OUT               ; P1.0 = 0
            bis.b   #01h,&P1DIR             ; P1.0 = Out
Mainloop    mov.w   #LPM3+GIE,SR            ; Enter LPM3 with ints
            jmp     Mainloop                ; Repeat
                                            ;
;------------------------------------------------------------------------------
NMI_ISR;   Only osc fault enabled, R15 used temporarly and not saved
;------------------------------------------------------------------------------
CheckOsc    bic.b   #OFIFG,&IFG1            ; Clear OSC fault flag
            mov.w   #0FFFh,R15              ; R15= Delay
CheckOsc1   dec.w   R15                     ; Additional delay to ensure start
            jnz     CheckOsc1               ;
            xor.b   #001h,&P1OUT            ; Toggle P1.0
            bit.b   #OFIFG,&IFG1            ; OSC fault flag set?
            jnz     CheckOsc                ; OSC Fault, clear flag again
            bis.b   #OFIE,&IE1              ; re-enable osc fault interrupt
            reti                            ; return from interrupt
                                            ;
;------------------------------------------------------------------------------
WDT_ISR;    Toggle P1.0
;------------------------------------------------------------------------------
            xor.b   #001h,&P1OUT            ; Toggle P1.0
            reti                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect ".int10"                  ; WDT Vector
            .short  WDT_ISR                 ;
            .sect ".int14"                  ; NMI vector
            .short  NMI_ISR                 ;
            .sect ".reset"                  ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
