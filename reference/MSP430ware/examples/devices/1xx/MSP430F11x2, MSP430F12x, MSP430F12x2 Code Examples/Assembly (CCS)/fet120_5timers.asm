;******************************************************************************
;   MSP-FET430P120 Demo - 5 Interrupt Timers & 2 Clock Outputs, 32kHz ACLK
;
;   Description: Use timer_A CCRx units and overflow and and watchdog overflow
;   ISR to generate 5 continous and interval timing intervals. Additionally
;   ACLK and SMCLK/4 both driven from a 32kHz XTAL are buffer off-chip driving
;   32768 and 8096 square waves respectively, For demonstration, CCR0, CCR1 and
;   CCR2 output units are optionally selected with port pins P1.1, P1.2 and
;   P1.3 in toggle mode. As such, these pins will toggle when respective CCRx
;   registers match the TAR counter. Interrupts are also enabled with all CCRx
;   units, software loads offset to next interval only - as long as the
;   interval offset is added to CCRx, toggle rate is generated in hardware.
;   Timer_A overflow ISR is used to toggle P1.0 with software, watchdog
;   overflow toggles P2.1 with software.
;   ACLK = TACLK = LFXT1 = 32768, SMCLK = LFXT1/4,  MCLK = default DCO ~ 800k
;   As coded and with TACLK = 32768, toggle rates:
;   P1.1 = CCR0 = 32768/(2*4) = 4096Hz
;   P1.2 = CCR1 = 32768/(2*16) = 1024Hz
;   P1.3 = CCR2 = 32768/(2*32) = 512Hz
;   P1.0 = overflow = 32768/(2*65536) = 0.25Hz
;   Proper use of TAIV interrupt vector generator demonstrated.
;   ;* An external watch crystal on XIN XOUT is required for ACLK *//	
;
;               MSP430F123(2)
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kHz
;          --|RST          XOUT|-
;            |                 |
;            |             P1.1|--> CCR0 = 4096
;            |             P1.2|--> CCR1 = 1024
;            |             P1.3|--> CCR2 = 512
;            |             P1.4|--> SMCLK = 32kHz/4 = 8192
;            |             P1.0|--> TA overflow/software
;            |             P2.1|--> WDT_ISR/software = 32
;            |             P2.0|--> ACLK = 32768
;
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
SetupWDT    mov.w   #WDT_ADLY_16,&WDTCTL    ; WDT 16ms, ACLK, interval timer
            bis.b   #WDTIE,&IE1             ; Enable WDT interrupt
SetupBC     bis.b   #SELS+DIVS_2,&BCSCTL2   ; SMCLK = LFXT1/4
SetupTA     mov.w   #TASSEL0+TACLR+TAIE,&TACTL  ; ACLK, clear TAR, interrupt
SetupC0     mov.w   #OUTMOD_4+CCIE,&CCTL0   ; CCR0 toggle, interrupt enabled
SetupC1     mov.w   #OUTMOD_4+CCIE,&CCTL1   ; CCR1 toggle, interrupt enabled
SetupC2     mov.w   #OUTMOD_4+CCIE,&CCTL2   ; CCR2 toggle, interrupt enabled
            mov.w   #4,&CCR0                ;
            mov.w   #16,&CCR1               ;
            mov.w   #32,&CCR2               ;
SetupP1     bis.b   #01Eh,&P1SEL            ; P1.1 - P1.4 option select
            bis.b   #01Fh,&P1DIR            ; P1.0 - 4 output direction
            bis.b   #003h,&P2DIR            ; P2.0 - P2.1 output direction
            bis.b   #001h,&P2SEL            ; P2.0 = ACLK option selection
            bis.w   #MC1,&TACTL             ; Start Timer_a in continous mode
            eint                            ; Enable interrupts
                                            ;													
Mainloop    jmp     Mainloop                ;
                                            ;
;------------------------------------------------------------------------------
TA0_ISR;
;------------------------------------------------------------------------------
            add.w   #4,&CCR0                ; Offset until next interrupt
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
CCR1_ISR    add.w   #16,&CCR1               ; Offset until next interrupt
            reti                            ; Return ISR		
                                            ;
CCR2_ISR    add.w   #32,&CCR2               ; Offset until next interrupt
            reti                            ; Return ISR		
                                            ;
;------------------------------------------------------------------------------
WDT_ISR;    Toggle P2.1
;------------------------------------------------------------------------------
            xor.b   #002h,&P2OUT            ; Toggle P2.1
            reti                            ;		
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
            .sect   ".int10"                ; WDT Vector
            .short  WDT_ISR                 ;
            .end
