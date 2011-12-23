;******************************************************************************
;   MSP-FET430P120 Demo - USART0, UART 9600 Echo ISR, 32kHz ACLK + DCO
;
;   Description: Echo a received character, USART0 RX ISR at high-speed using
;   32kHz XTAL and DCO. Normal operation in LMP0, DCO continously stabilized,
;   interrupt driven using CCR2. DCO used for UART baud generation.
;   On a valid RX character, character echoed back.
;   Baud rate divider with 2MHz = 2MHz/9600 ~208 (00D0h)
;   ACLK = LFXT1/8 = 32768/8, MCLK = SMCLK = UCLK0 = DCOCLK ~2MHz
;   //* An external 32kHz watch crystal on XIN XOUT is required for ACLK *//	
;
Delta       .equ    488                     ; Delta = (target DCO)/(4096) ~ 2MHz
;
;                MSP430F123(2)
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32768Hz
;          --|RST          XOUT|-
;            |                 |
;            |             P3.4|------------>
;            |                 |  9600 - 8N1
;            |             P3.5|<------------
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
SetupP3     bis.b   #030h,&P3SEL            ; P3.4,5 = USART0 TXD/RXD
SetupBC     bis.b   #DIVA_3,&BCSCTL1        ; ACLK = LFXT1CLK/8
Setup_CC2   mov.w   #CM_1+CCIS_1+CAP+CCIE,&CCTL2 ; CAP, ACLK, interrupt
Setup_TA    mov.w   #TASSEL_2+MC_2+TACLR,&TACTL   ; SMCLK, ContMode, clr
SetupUART0  bis.b   #UTXE0+URXE0,&ME2       ; Enable USART0 TXD/RXD
            bis.b   #CHAR,&UCTL0            ; 8-bit char
            bis.b   #SSEL1,&UTCTL0          ; UCLK = SMCLK
            mov.b   #0D0h,&UBR00            ; 2MHz 9600
            mov.b   #000h,&UBR10            ;
            mov.b   #000h,&UMCTL0           ; no modulation
            bic.b   #SWRST,&UCTL0           ; **Initalize USART state machine**
            bis.b   #URXIE0,&IE2            ; Enable USART0 RX interrupt
                                            ;
                                            ;
Mainloop    bis.b   #LPM0+GIE,SR            ; Enter LPM0, interrupts enabled
            nop                             ; Needed only for debugger
                                            ;
;------------------------------------------------------------------------------
USART0RX_ISR;  Echo back RXed character, confirm TX buffer is ready first
;------------------------------------------------------------------------------
TX1         bit.b   #UTXIFG0,&IFG2          ; USART0 TX buffer ready?
            jz      TX1                     ; Jump is TX buffer not ready
            mov.b   &RXBUF0,&TXBUF0         ; TX -> RXed character
            reti                            ;
                                            ;
;-----------------------------------------------------------------------------
TA2_ISR
;-----------------------------------------------------------------------------
AdjDCO      push.w  &CCR2                   ;
            sub.w   R15,&CCR2               ;
            cmp.w   #Delta,&CCR2            ; Delta = SMCLK/(32768/8)
            pop.w   R15                     ;
            jlo     IncDCO                  ;
            jeq     DoneDCO                 ;
DecDCO      dec.b   &DCOCTL                 ; Slow DCO with DCO and MOD
            jc      DoneDCO                 ; Slower?
            cmp.b   #XT2OFF+DIVA_3,&BCSCTL1 ; Can RSEL.x be decremented?
            jz      DoneDCO                 ; jump>DCO at slowest setting
            dec.b   &BCSCTL1                ; Decrement RSEL.x
            reti                            ; Return from interrrupt
IncDCO      inc.b   &DCOCTL                 ; Speed DCO with DCO and MOD
            jnc     DoneDCO                 ; Faster?
            cmp.b   #XT2OFF+DIVA_3+07h,&BCSCTL1 ; Can RSEL.x be increased?
            jz      DoneDCO                 ; jump> DCO at fastest settting
            inc.b   &BCSCTL1                ; Increment RSEL.x
DoneDCO     reti                            ; Return from interrrupt
                                            ;
;------------------------------------------------------------------------------
TAX_ISR;    Common ISR for CCR1-4 and overflow
;------------------------------------------------------------------------------
            add.w   &TAIV,PC                ; Add Timer_A offset vector
            reti                            ; CCR0 - no source
            reti                            ; CCR1
            jmp     TA2_ISR                 ; CCR2
;            reti                            ; CCR3
;            reti                            ; CCR4
;            reti                            ; Return from overflow ISR		
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ;
            .short  RESET                   ; POR, ext. Reset, Watchdog
            .sect   ".int07"                ;
            .short  USART0RX_ISR            ; USART0 receive
            .sect   ".int08"                ; Timer_AX Vector
            .short  TAX_ISR                 ;
            .end