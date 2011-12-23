;*******************************************************************************
;   MSP430x11x1 Demo - Timer_A, Toggle P1.0-3, Cont. Mode ISR, 32kHz ACLK
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
;   ACLK = TACLK = 32kHz, MCLK = SMCLK = default DCO ~800kHz
;   ;* An external watch crystal on XIN XOUT is required for ACLK *//	
;
;   As coded and with TACLK = 32768Hz, toggle rates are:
;   P1.1= CCR0 = 32768/(2*4) = 4096Hz
;   P1.2= CCR1 = 32768/(2*16) = 1024Hz
;   P1.3= CCR2 = 32768/(2*100) = 163.84Hz
;   P1.0= overflow = 32768/(2*65536) = 0.25Hz
;
;                MSP430F1121
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |         P1.1/TA0|--> CCR0
;            |         P1.2/TA1|--> CCR1
;            |         P1.3/TA2|--> CCR2
;            |             P1.0|--> Overflow/software
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
SetupP1     bis.b   #00Eh,&P1SEL            ; P1.1 - P1.3 option select
            bis.b   #00Fh,&P1DIR            ; P1.0-3 outputs
SetupC0     mov.w   #OUTMOD_4 +CCIE,&CCTL0  ; CCR0 toggle, interrupt enabled
SetupC1     mov.w   #OUTMOD_4 +CCIE,&CCTL1  ; CCR1 toggle, interrupt enabled
SetupC2     mov.w   #OUTMOD_4 +CCIE,&CCTL2  ; CCR2 toggle, interrupt enabled
SetupTA     mov.w   #TASSEL_1+MC_2+TAIE,&TACTL; ACLK, contmode, interrupt
                                            ;													
Mainloop    bis.w   #LPM3+GIE,SR            ; Enter LPM3, interrupts enabled
            nop                             ; Required for debug
                                            ;
;-------------------------------------------------------------------------------
TA0_ISR;
;-------------------------------------------------------------------------------
            add.w   #4,&CCR0                ; Offset until next interrupt
            reti                            ;		
                                            ;
;-------------------------------------------------------------------------------
TAX_ISR;    Common ISR for CCR1-4 and overflow
;-------------------------------------------------------------------------------
            add.w   &TAIV,PC                ; Add Timer_A offset vector
            reti                            ; CCR0 - no source
            jmp     CCR1_ISR                ; CCR1
            jmp     CCR2_ISR                ; CCR1
            reti                            ; CCR3
            reti                            ; CCR4
TA_over     xor.b   #001h,&P1OUT            ; Toggle P1.0
            reti                            ; Return from overflow ISR		
                                            ;
CCR1_ISR    add.w   #16,&CCR1               ; Offset until next interrupt
            reti                            ; Return ISR		
                                            ;
CCR2_ISR    add.w   #100,&CCR2              ; Offset until next interrupt
            reti                            ; Return ISR		
                                            ;
;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int09"                ; Timer_A0 Vector
            .short  TA0_ISR                 ;
            .sect   ".int08"                ; Timer_AX Vector
            .short  TAX_ISR                 ;
            .end