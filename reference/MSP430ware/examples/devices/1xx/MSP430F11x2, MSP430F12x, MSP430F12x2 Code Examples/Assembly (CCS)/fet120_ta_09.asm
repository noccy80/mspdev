;******************************************************************************
;   MSP-FET430P120 Demo - Timer_A, Toggle P1.0-3, Cont. Mode ISR, HF XTAL ACLK
;
;   Description: Use Timer_A CCRx units and overflow to generate four
;   independent timing intervals. For demonstration, CCR0, CCR1 and CCR2
;   output units are optionally selected with port pins P1.1, P1.2 and P1.3
;   in toggle mode. As such, these pins will toggle when respective CCRx
;   registers match the TAR counter. Interrupts are also enabled with all
;   CCRx units, software loads offset to next interval only - as long as the
;   interval offset is added to CCRx, toggle rate is generated in hardware.
;   Timer_A overflow ISR is used to toggle P1.0 with software. Proper use
;   of the TAIV interrupt vector generator is demonstrated.
;   ACLK = MCLK = TACLK = LFXT1 = HF XTAL
;   //* HF XTAL NOT INSTALLED ON FET *//
;   //* Min Vcc required varies with MCLK frequency - refer to datasheet *//	
;
;   As coded with TACLK = HF XTAL and assuming 8MHz HF XTAL, toggle rates are:
;   P1.1 = CCR0 = 8MHz/(2*200) = 20kHz
;   P1.2 = CCR1 = 8MHz/(2*1000) = 4kHz
;   P1.3 = CCR2 = 8MHz/(2*10000) = 400Hz
;   P1.0 = overflow = 8MHz/(2*65536) = 61Hz
;
;                MSP430F123(2)
;             -----------------
;         /|\|              XIN|-
;          | |                 | HF XTAL (455k - 8MHz)
;          --|RST          XOUT|-
;            |                 |
;            |         P1.1/TA0|--> CCR0
;            |         P1.2/TA1|--> CCR1
;            |         P1.3/TA2|--> CCR2
;            |             P1.0|--> Overflow/software
;
;   M. Buccini / M. Raju
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x12x2.h"
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     bis.b   #00Eh,&P1SEL            ; P1.1 - P1.3 option select
            bis.b   #00Fh,&P1DIR            ; P1.0-3 outputs
SetupBC     bis.b   #XTS,&BCSCTL1           ; LFXT1 = HF XTAL
SetupOsc    bic.b   #OFIFG,&IFG1            ; Clear OSC fault flag
            mov.w   #0FFh,R15               ; R15 = Delay
SetupOsc1   dec.w   R15                     ; Additional delay to ensure start
            jnz     SetupOsc1               ;
            bit.b   #OFIFG,&IFG1            ; OSC fault flag set?
            jnz     SetupOsc                ; OSC Fault, clear flag again
            bis.b   #SELM_3,&BCSCTL2        ; MCLK= LFXT1
SetupC0     mov.w   #OUTMOD_4+CCIE,&CCTL0   ; CCR0 toggle, interrupt enabled
SetupC1     mov.w   #OUTMOD_4+CCIE,&CCTL1   ; CCR1 toggle, interrupt enabled
SetupC2     mov.w   #OUTMOD_4+CCIE,&CCTL2   ; CCR2 toggle, interrupt enabled
SetupTA     mov.w   #TASSEL_1+MC_2+TAIE,&TACTL   ; ACLK, contmode, interrupt
                                            ;													
Mainloop    bis.w   #CPUOFF+GIE,SR          ; Enter LPM3, interrupts enabled
            nop                             ; Required for debugger
                                            ;
;------------------------------------------------------------------------------
TA0_ISR;
;------------------------------------------------------------------------------
            add.w   #200,&CCR0              ; Offset until next interrupt
            reti                            ;		
                                            ;
;------------------------------------------------------------------------------
TAX_ISR;    Common ISR for CCR1-4 and overflow
;------------------------------------------------------------------------------
            add.w   &TAIV,PC                ; Add Timer_A offset vector
            reti                            ; CCR0 - no source
            jmp     CCR1_ISR                ; CCR1
            jmp     CCR2_ISR                ; CCR1
            reti                            ; CCR3
            reti                            ; CCR4
TA_over     xor.b   #001h,&P1OUT            ; Toggle P1.0
            reti                            ; Return from overflow ISR		
                                            ;
CCR1_ISR    add.w   #1000,&CCR1             ; Offset until next interrupt
            reti                            ; Return ISR		
                                            ;
CCR2_ISR    add.w   #10000,&CCR2            ; Offset until next interrupt
            reti                            ; Return ISR		
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int09"                ; Timer_A0 Vector
            .short  TA0_ISR                 ;
            .sect   ".int08"                ; Timer_AX Vector
            .short  TAX_ISR                 ;
            .end