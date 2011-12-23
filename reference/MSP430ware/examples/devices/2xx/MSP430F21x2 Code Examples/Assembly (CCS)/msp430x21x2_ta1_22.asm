;*******************************************************************************
;   MSP430F22x4 Demo - Timer_A, Ultra-Low Pwr Pulse Accumulator
;
;   Description: Timer_A is used as ultra-low power pulse counter. In this
;   example TAR is offset 100 counts, which are acculmulated on INCLK P2.1,
;   with the system in LPM4 - all internal clocks off. After 100 counts, TAR
;   will overflow requesting an interrupt, and waking the system. Timer_A is
;   then reconfigured with SMCLK as clock source in up mode - TACCR1 will then
;   toggle P1.0 every 50000 SMCLK cycles. SMCLK is then configured to operate
;   at default DCO value.
;
;                MSP430F22x4
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;        --->|P2.1/TAINCLK P1.0|-->LED
;
;  JL Bile
;  Texas Instruments Inc.
;  May 2008
;  Built with Code Composer Essentials: v3 FET
;*******************************************************************************
 .cdecls C,LIST, "msp430x21x2.h"
;-------------------------------------------------------------------------------
 			.text							; Program Start
;-------------------------------------------------------------------------------
RESET       mov.w   #025Fh,SP         		; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP1     mov.b   #0FFh,&P1DIR            ; All P1.x outputs
            clr.b   &P1OUT                  ; All P1.x reset
SetupP2     mov.b   #0FDh,&P2DIR            ; All but P2.1 outputs
            mov.b   #002h,&P2SEL            ; P2.1 TAINCLK option select
            clr.b   &P2OUT                  ; All P2.x reset
SetupP3     mov.b   #0FFh,&P3DIR            ; All P3.x outputs
            clr.b   &P3OUT                  ; All P3.x reset
;SetupP4     mov.b   #0FFh,&P4DIR            ; All P4.x outputs
;            clr.b   &P4OUT                  ; All P4.x reset
SetupTA     mov.w   #TASSEL1+TASSEL0+TACLR+TAIE,&TACTL  ; Ext. INCLK, interrupt
            mov.w   #0FFFFh-100,&TAR        ; Offset until TAR overflow
            bis.w   #MC1,&TACTL             ; Start Timer_A continuous mode
            bis.w   #LPM4+GIE,SR            ; Enter LPM4 w/ interrupts
                                            ;
Mainloop    xor.b   #001h,&P1OUT            ; P1.0 = toggle
            bis.w   #CPUOFF,SR              ; CPU is not required
            jmp     Mainloop                ; Repeat
                                            ;
;-------------------------------------------------------------------------------
TAX_ISR;    Common ISR for TACCR1 and overflow
;-------------------------------------------------------------------------------
            add.w   &TAIV,PC                ; Add Timer_A offset vector
            reti                            ;
            jmp     TACCR1_ISR              ; TACCR1
            reti                            ;
            reti                            ;
            reti                            ;
TA_over     mov.w   #TASSEL1+TACLR,&TACTL   ; SMCLK, clear TAR
SetupC1     mov.w   #CCIE,&TACCTL1          ; TACCR1 interrupt enabled
            mov.w   #50000,&TACCR1          ;
            bis.w   #MC1,&TACTL             ; Start Timer_A in continuous
            bic.w   #LPM4,0(SP)             ; Exit LPM4 on reti
            reti                            ; Return from overflow ISR
                                            ;
TACCR1_ISR  add.w   #50000,&TACCR1          ; Offset until next interrupt
            bic.w   #CPUOFF,0(SP)           ; CPU active on reti
            reti                            ; Return from TACCR1 ISR
                                            ;
;-------------------------------------------------------------------------------
;			Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect	".reset"				; MSP430 RESET Vector
            .short	RESET                   ;
            .sect	".int08"       			; Timer1_AX Vector
            .short	TAX_ISR                 ;
            .end
