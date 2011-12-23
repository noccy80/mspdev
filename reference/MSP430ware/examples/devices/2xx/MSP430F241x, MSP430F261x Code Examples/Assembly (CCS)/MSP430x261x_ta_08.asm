;******************************************************************************
;   MSP430x261x Demo - Timer_A, Toggle P1.0,P1.2 & P2.0 Cont. Mode ISR, 32kHz ACLK
;
;   Description: Use Timer_A CCRx units and overflow to generate four
;   independent timing intervals. For demonstration, TACCR0, TACCR1 and TACCR2
;   output units are optionally selected with port pins P1.0, P1.2 and P2.0
;   in toggle mode. As such, these pins will toggle when respective CCRx
;   registers match the TAR counter. Interrupts are also enabled with all
;   CCRx units, software loads offset to next interval only - as long as
;   the interval offset is added to CCRx, toggle rate is generated in
;   hardware. Timer_A overflow ISR is used to toggle P1.0 with software.
;   Proper use of the TAIV interrupt vector generator is demonstrated.
;   ACLK = TACLK = 32kHz, MCLK = SMCLK = default DCO ~1048kHz
;   //* An external watch crystal on XIN XOUT is required for ACLK *//	
;
;   As coded and with TACLK = 32768Hz, toggle rates are:
;   P1.1 = TACCR0     = 32768/(2*4)     = 4096 Hz
;   P1.2 = TACCR1     = 32768/(2*16)    = 1024 Hz
;   P1.3 = TACCR2     = 32768/(2*100)   = 163.84 Hz
;   P1.0 = overflow   = 32768/(2*65536) = 0.25 Hz
;
;                MSP430F241x
;                MSP430F261x
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |         P1.1/TA0|--> TACCR0
;            |         P1.2/TA1|--> TACCR1
;            |         P1.3/TA2|--> TACCR2
;            |             P1.0|--> Overflow/software
;
;  JL Bile
;  Texas Instruments Inc.
;  June 2008
;  Built Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x26x.h"
;-------------------------------------------------------------------------------
			.text	;Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #0850h,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT

OFIFGcheck  bic.b   #OFIFG,&IFG1            ; Clear OFIFG
            mov.w   #047FFh,R15             ; Wait for OFIFG to set again if
OFIFGwait   dec.w   R15                     ; not stable yet
            jnz     OFIFGwait
            bit.b   #OFIFG,&IFG1            ; Has it set again?
            jnz     OFIFGcheck              ; If so, wait some more


SetupP1     bis.b   #BIT1+BIT2+BIT3,&P1SEL  ; P1.1,P1.2, P1.3-TA0,TA1,TA2 selected
            bis.b   #BIT1+BIT2+BIT3,&P1DIR  ; P1.1,P1.2, P1.3 outputs

            bis.b   #BIT0,&P1DIR            ; P1.0 output


SetupC0     mov.w   #OUTMOD_4 +CCIE,&TACCTL0  ; TACCR0 toggle, interrupt enabled
SetupC1     mov.w   #OUTMOD_4 +CCIE,&TACCTL1  ; TACCR1 toggle, interrupt enabled
SetupC2     mov.w   #OUTMOD_4 +CCIE,&TACCTL2  ; TACCR2 toggle, interrupt enabled
SetupTA     mov.w   #TASSEL_1+MC_2+TAIE,&TACTL ; ACLK, contmode, interrupt
                                        			
Mainloop    bis.w   #LPM3+GIE,SR            ; Enter LPM3, interrupts enabled
            nop                             ; Required for debug
                                            ;
;------------------------------------------------------------------------------
TA0_ISR;
;------------------------------------------------------------------------------
            add.w   #4,&TACCR0              ; Offset until next interrupt
            reti                            ;		
                                            ;
;------------------------------------------------------------------------------
TAX_ISR;    Common ISR for TACCR1-4 and overflow
;------------------------------------------------------------------------------
            add.w   &TAIV,PC                ; Add Timer_A offset vector
            reti                            ; TACCR0 - no source
            jmp     TACCR1_ISR              ; TACCR1
            jmp     TACCR2_ISR              ; TACCR1
            reti                            ; CCR3
            reti                            ; CCR4
TA_over     xor.b   #BIT0,&P1OUT            ; Toggle P1.0
            reti                            ; Return from overflow ISR		
                                            ;
TACCR1_ISR  add.w   #16,&TACCR1             ; Offset until next interrupt
            reti                            ; Return ISR		
                                            ;
TACCR2_ISR  add.w   #100,&TACCR2            ; Offset until next interrupt
            reti                            ; Return ISR		
                                            ;
;------------------------------------------------------------------------------
;			Interrupt Vectors
;------------------------------------------------------------------------------
            .sect	".reset"	           ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int25"	          ; Timer_A0 Vector
            .short  TA0_ISR                 ;
            .sect  	".int24"	          ; Timer_AX Vector
            .short   TAX_ISR                 ;
            .end