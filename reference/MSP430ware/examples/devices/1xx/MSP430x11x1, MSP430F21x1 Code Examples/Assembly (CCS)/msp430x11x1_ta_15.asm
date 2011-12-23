;*******************************************************************************
;   MSP430x11x1 Demo - Timer_A, Toggle P1.1/TA0, Up/Down Mode, HF XTAL ACLK
;
;   Description: Toggle P1.1 using hardware TA0 output. Timer_A is configured
;   for up/down mode with CCR0 defining period, TA0 also output on P1.1. In
;   this example, CCR0 is loaded with 250 and TA0 will toggling P1.1 at
;   TACLK/2*250. Thus the output frequency on P1.1 will be the TACLK/1000.
;   No CPU or software resources required.
;   As coded with TACLK = ACLK, P1.1 output frequency = HF XTAL/1000.
;   ACLK = MCLK = TACLK = HF XTAL
;   ;* HF XTAL REQUIRED AND NOT INSTALLED ON FET *//
;   ;* Min Vcc required varies with MCLK frequency - refer to datasheet *//
;
;               MSP430F1121
;             -----------------
;         /|\|              XIN|-
;          | |                 | HF XTAL (455k - 8MHz)
;          --|RST          XOUT|-
;            |                 |
;            |         P1.1/TA0|--> ACLK/1000
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
SetupP1     bis.b   #002h,&P1DIR            ; P1.1 output
            bis.b   #002h,&P1SEL            ; P1.1 option slect
SetupBC     bis.b   #XTS,&BCSCTL1           ; LFXT1 = HF XTAL
SetupOsc    bic.b   #OFIFG,&IFG1            ; Clear OSC fault flag
            mov.w   #0FFh,R15               ; R15 = Delay
SetupOsc1   dec.w   R15                     ; Additional delay to ensure start
            jnz     SetupOsc1               ;
            bit.b   #OFIFG,&IFG1            ; OSC fault flag set?
            jnz     SetupOsc                ; OSC Fault, clear flag again
            bis.b   #SELM1+SELM0,&BCSCTL2   ; MCLK = LFXT1
SetupC0     mov.w   #OUTMOD_4,&CCTL0        ; CCR0 toggle mode
            mov.w   #250,&CCR0              ;
SetupTA     mov.w   #TASSEL_1+MC_3,&TACTL   ; ACLK, updown mode
            bis.w   #MC1+MC0,&TACTL         ; Start Timer_a in up-downmode
                                            ;						
Mainloop    bis.w   #CPUOFF,SR              ; CPU off
            nop                             ; Required only for debugger
                                            ;
;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
