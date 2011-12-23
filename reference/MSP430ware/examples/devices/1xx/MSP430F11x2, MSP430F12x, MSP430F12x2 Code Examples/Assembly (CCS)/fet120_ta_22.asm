;******************************************************************************
;   MSP-FET430P120 Demo - Timer_A, Ultra-Low Pwr Pulse Accumulator
;
;   Description: Timer_A is used as ultra-low power pulse counter. In this
;   example TAR is offset 100 counts, which are acculmulated on INCLK P2.1,
;   with the system in LPM4 - all internal clocks off. After 100 counts, TAR
;   will overflow requesting an interrupt, and waking the system. Timer_A is
;   then reconfigured with SMCLK as clock source in up mode - CCR1 will then
;   toggle P1.0 every 50000 SMCLK cycles. SMCLK is then configured to operate
;   at default DCO value.
;
;                MSP430F123(2)
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;        --->|P2.1/INCLK   P1.0|-->LED
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
RESET       mov.w   #0300h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupTA     mov.w   #TASSEL1+TASSEL0+TACLR+TAIE,&TACTL  ; Ext. INCLK, interrupt
            bis.b   #02h,&P2SEL             ; INCLK option select
            mov.w   #0FFFFh-100,&TAR        ; Offset until TAR overflow
            bis.w   #MC1,&TACTL             ; Start Timer_A continuous mode
            eint                            ; Enable interrupts
                                            ;
Mainloop    xor.b   #001h,&P1OUT            ; P1.0 = toggle
            bis.w   #CPUOFF,SR              ; CPU is not required
            jmp     Mainloop                ; Repeat
                                            ;
;------------------------------------------------------------------------------
TAX_ISR;    Common ISR for CCR1-4 and overflow
;------------------------------------------------------------------------------
            add.w   &TAIV,PC                ; Add Timer_A offset vector
            reti                            ; CCR0 - no source
            jmp     CCR1_ISR                ; CCR1
            reti                            ; CCR2
            reti                            ; CCR3
            reti                            ; CCR4
TA_over     mov.w   #TASSEL1+TACLR,&TACTL   ; SMCLK, clear TAR
SetupC1     mov.w   #CCIE,&CCTL1            ; CCR1 interrupt enabled
            mov.w   #50000,&CCR1            ;
SetupP1     bis.b   #001h,&P1DIR            ; P1.0 output
            bis.w   #MC1,&TACTL             ; Start Timer_A in continuous
            bic.w   #LPM4,0(SP)             ; Exit any LPMx mode on reti
            reti                            ; Return from overflow ISR		
                                            ;
CCR1_ISR    add.w   #50000,&CCR1            ; Offset until next interrupt
            bic.w   #CPUOFF,0(SP)           ; CPU active on reti
            reti                            ; Return from overflow ISR		


;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int08"                ; Timer_AX Vector
            .short  TAX_ISR                 ;
            .end
