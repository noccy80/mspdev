;*******************************************************************************
;   MSP430F22x4 Demo - Timer_B, Toggle P4.0-2, Cont. Mode ISR, HF XTAL ACLK
;
;   Description: Use Timer_B CCRx units and overflow to generate eight
;   independent timing intervals. For demonstration, TBCCR0-2 output
;   units are optionally selected with P4.0-2 respectively in toggle
;   mode. As such, these pins will toggle when respective TBCCRx registers
;   match the TBR counter. Interrupts are also enabled with all TBCCRx units,
;   software only adds offset to next interval - as long as the interval
;   offset is aded to TBCCRx, toggle rate is generated in hardware. Timer_B
;   overflow ISR is used to toggle P1.0 with software. Proper use of the
;   TBIV interrupt vector generator is demonstrated.
;   MCLK = ACLK = TBCLK = LFXT1 = HF XTAL
;   //* Min Vcc required varies with MCLK frequency - refer to datasheet *//
;
;   As coded with TBCLK= HF XTAL and assuming HF XTAL= 8MHz, toggle rates are:
;   P4.0 = TBCCR0 = 8MHz/(2*200) = 20kHz
;   P4.1 = TBCCR1 = 8MHz/(2*400) = 10kHz
;   P4.2 = TBCCR2 = 8MHz/(2*500) = 8000Hz
;   P1.0 = overflow = 8MHz/(2*65536) = 61Hz
;
;                MSP430F22x4
;             -----------------
;         /|\|              XIN|-
;          | |                 | HF XTAL (3 – 16MHz crystal or resonator)
;          --|RST          XOUT|-
;            |                 |
;            |         P4.0/TB0|--> TBCCR0
;            |         P4.1/TB1|--> TBCCR1
;            |         P4.2/TB2|--> TBCCR2
;            |             P1.0|--> Overflow/software
;
;  P.Thanigai
;  Texas Instruments Inc.
;  August 2007
;  Built with Code Composer Essentials Version: 2.0
;*******************************************************************************
 .cdecls C,LIST,  "msp430x22x4.h"
                              
;------------------------------------------------------------------------------
            .text                  			; Program reset
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stack pointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP4     bis.b   #07h,&P4SEL             ; P4.x - P4.2 option select
            bis.b   #07h,&P4DIR             ; P4.x = outputs
SetupP1     bis.b   #01h,&P1DIR             ; P1.0 = output
            bis.b   #XTS,&BCSCTL1           ; LFXT1 = HF XTAL
            bis.b   #LFXT1S1,&BCSCTL3       ; LFXT1S1 = 3-16Mhz
SetupOsc    bic.b   #OFIFG,&IFG1            ; Clear OSC fault flag
            mov.w   #0FFh,R15               ; R15 = Delay
SetupOsc1   dec.w   R15                     ; Additional delay to ensure start
            jnz     SetupOsc1               ;
            bit.b   #OFIFG,&IFG1            ; OSC fault flag set?
            jnz     SetupOsc                ; OSC Fault, clear flag again
            bis.b   #SELM_3,&BCSCTL2        ; MCLK = LFXT1
                                            ;
SetupCx     mov.w   #OUTMOD_4+CCIE,&TBCCTL0 ; TBCCR0 interrupt enabled
            mov.w   #OUTMOD_4+CCIE,&TBCCTL1 ; TBCCR1 interrupt enabled
            mov.w   #OUTMOD_4+CCIE,&TBCCTL2 ; TBCCR2 interrupt enabled
SetupTB     mov.w   #TBSSEL_1+MC_2+TBIE,&TBCTL   ; ACLK, contmode, interrupt
                                            ;
Mainloop    bis.w   #CPUOFF+GIE,SR          ; Enter LPM0, interrupts enabled
            nop                             ; Required for debugger
                                            ;
;-------------------------------------------------------------------------------
TB0_ISR;    ISR for TBCCR0
;-------------------------------------------------------------------------------
            add.w   #200,&TBCCR0            ; Offset until next interrupt
            reti                            ;
                                            ;
;-------------------------------------------------------------------------------
TBX_ISR;    Common ISR for TBCCR1-2 and overflow
;-------------------------------------------------------------------------------
            add.w   &TBIV,PC                ; Add Timer_B offset vector
            reti                            ;
            jmp     TBCCR1_ISR              ; TBCCR1
            jmp     TBCCR2_ISR              ; TBCCR2
            nop                             ;
            nop                             ;
            nop                             ;
            nop                             ;
TB_over     xor.b   #001h,&P1OUT            ; Toggle P1.0
            reti                            ; Return from overflow ISR
                                            ;
TBCCR1_ISR  add.w   #400,&TBCCR1            ; Offset until next interrupt
            jmp     TBX_ISR                 ;
                                            ;
TBCCR2_ISR  add.w   #500,&TBCCR2            ; Offset until next interrupt
            jmp     TBX_ISR                 ;
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int13"                ; Timer_B0 Vector
            .short  TB0_ISR     
            .sect   ".int12"                ; Timer_B1 Vector
            .short  TBX_ISR                 ;
            .end
