;******************************************************************************
;   MSP-FET430P440 Demo - USART1, 38400 UART Echo ISR, DCO SMCLK
;
;   Description: Echo a received character, RX ISR used. Normal mode is LPM0.
;   USART1 RX interrupt triggers TX Echo.
;   Baud rate divider with 1048576hz = 1048576/38400 = ~27.31 (01Bh|03h)
;   ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   ;* An external watch crystal between XIN & XOUT is required for ACLK *//	
;
;                MSP430F449
;             -----------------
;         /|\|              XIN|-
;          | |                 | 32kz
;          --|RST          XOUT|-
;            |                 |
;            |       P4.0/UTXD1|------------>
;            |                 | 38400 - 8N1
;            |       P4.1/URXD1|<------------
;
;   M. Buccini / A. Dannenberg
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST, "msp430x44x.h"
;------------------------------------------------------------------------------
            .text                  			; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupFLL    bis.b   #XCAP14PF,&FLL_CTL0     ; Configure load caps
SetupP4     bis.b   #003h,&P4SEL            ; P4.0,1 = USART1 TXD/RXD
SetupUART1  bis.b   #UTXE1+URXE1,&ME2       ; Enable USART1 TXD/RXD
            bis.b   #CHAR,&UCTL1            ; 8-bit characters
            mov.b   #SSEL1,&UTCTL1          ; UCLK1 = SMCLK
            mov.b   #01Bh,&UBR01            ; 1MHz 38400
            mov.b   #000h,&UBR11            ; 1MHz 38400
            mov.b   #003h,&UMCTL1           ; Modulation
            bic.b   #SWRST,&UCTL1           ; **Initialize USART state machine**
            bis.b   #URXIE1,&IE2            ; Enable USART1 RX interrupt
                                            ;
Mainloop    bis.b   #CPUOFF+GIE,SR          ; Enter LPM0, interrupts enabled
            nop                             ; Needed only for debugger
                                            ;
;------------------------------------------------------------------------------
USART1RX_ISR;  Echo back RXed character, confirm TX buffer is ready first
;------------------------------------------------------------------------------
TX1         bit.b   #UTXIFG1,&IFG2          ; USART1 TX buffer ready?
            jz      TX1                     ; Jump if TX buffer not ready
            mov.b   &RXBUF1,&TXBUF1         ; TX -> RXed character
            reti                            ;
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; RESET Vector
            .short  RESET                   ;
            .sect   ".int03"                ; USART1 Rx Vector
            .short  USART1RX_ISR            ;
            .end
