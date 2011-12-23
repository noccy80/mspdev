;******************************************************************************
;  MSP430x21x1 Demo - OFIFG ISR for LF Failsafe Operation on Ext Clk
;
;  Description: Toggle P1.0 using software timed by the WDT ISR. Toggle rate
;  is approximately 250ms based on 32768Hz ACLK when present. When the LFXT1
;  input signal faults during operation, the NMI ISR is entered and the fault
;  is serviced. During this time the LED will flash at a faster rate indicating
;  an ACLK fault. During this time the CPU is held in the NMI ISR.
;  Buffer ACLK on P2.0 and default SMCLK(DCO) on P1.4.
;  To measure SMCLK on P1.4 with the FET, use "Release JTAG on Go"
;  in the debugger to have access to the port. Then run the code.
;
;  ACLK = 32768 Hz, MCLK = SMCLK = ~1.16 MHz
;
;               MSP430F21x1
;             -----------------
;         /|\|              XIN|<--LF Ext ACLK (10-50 kHz)
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |       P1.4/SMCLK|-->SMCLK = ~1.16MHz
;            |        P2.0/ACLK|-->ACLK = LF Ext ACLK
;            |             P1.0|-->LED
;
;  H. Grewal / A. Dannenberg
;  Texas Instruments, Inc
;  June 2005
;  Built with Code Composer Essentials Version: 1.0
;*****************************************************************************
 .cdecls C,LIST,  "msp430x21x1.h"
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0300h,SP               ; Initialize stackpointer
            bis.b   #LFXT1S_3,&BCSCTL3      ; Ext Digital Clk
StopWDT     mov.w   #WDT_ADLY_250,&WDTCTL   ; Set WDT interval to ~250ms from ACLK
                                            ;
            mov.b   #0,&P1OUT               ; P1.0 = 0
            bis.b   #011h,&P1DIR            ; P1.0,1.4 outputs
            bis.b   #010h,&P1SEL            ; P1.4 SMCLK output
            bis.b   #01h,&P2DIR             ; P2.0 output
            bis.b   #01h,&P2SEL             ; P2.0 ACLK output
            bis.b   #OFIE,&IE1              ; Enable osc fault interrupt
            bis.b   #WDTIE,&IE1             ; Enable WDT interrupt

Mainloop    mov.w   #LPM0+GIE,SR            ; Enter LPM0 with ints
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
