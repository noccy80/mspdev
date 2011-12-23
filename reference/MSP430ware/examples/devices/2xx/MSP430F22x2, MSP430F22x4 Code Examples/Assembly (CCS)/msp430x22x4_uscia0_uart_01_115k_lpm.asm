;*******************************************************************************
;   MSP430F22x4 Demo - USCI_A0, 115200 UART Echo ISR, DCO SMCLK, LPM4
;
;   Description: Echo a received character, RX ISR used. Normal mode is LPM4.
;   Automatic clock activation for SMCLK through the USCI is demonstrated.
;   All I/O configured as low outputs to eliminate floating inputs.
;   USCI_A0 RX interrupt triggers TX Echo.
;   Baud rate divider with 1MHz = 1MHz/115200 = ~8.7
;   ACLK = n/a, MCLK = SMCLK = CALxxx_1MHZ = 1MHz
;
;                MSP430F22x4
;             -----------------
;         /|\|              XIN|-
;          | |                 |
;          --|RST          XOUT|-
;            |                 |
;            |             P2.1|-->SMCLK = 1MHz (active on demand)
;            |                 |
;            |     P3.4/UCA0TXD|------------>
;            |                 | 115200 - 8N1
;            |     P3.5/UCA0RXD|<------------
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
SetupDCO    mov.b   &CALBC1_1MHZ,&BCSCTL1   ; Set DCO
            mov.b   &CALDCO_1MHZ,&DCOCTL    ;
SetupP1     mov.b   #0FFh,&P1DIR            ; All P1.x outputs
            clr.b   &P1OUT                  ; All P1.x reset
SetupP2     mov.b   #002h,&P2SEL            ; P2.1 = SMCLK, others GPIO
            mov.b   #0FFh,&P2DIR            ; All P2.x outputs
            clr.b   &P2OUT                  ; All P2.x reset
SetupP3     bis.b   #030h,&P3SEL            ; P3.4,5 = USCI_A0 TXD/RXD
            mov.b   #0FFh,&P3DIR            ; All P3.x outputs
            clr.b   &P3OUT                  ; All P3.x reset
SetupP4     mov.b   #0FFh,&P4DIR            ; All P4.x outputs
            clr.b   &P4OUT                  ; All P4.x reset
SetupUSCI0  bis.b   #UCSSEL_2,&UCA0CTL1     ; SMCLK
            mov.b   #8,&UCA0BR0             ; 1MHz 115200
            mov.b   #0,&UCA0BR1             ; 1MHz 115200
            mov.b   #UCBRS2+UCBRS0,&UCA0MCTL; Modulation UCBRSx = 5
            bic.b   #UCSWRST,&UCA0CTL1      ; **Initialize USCI state machine**
            bis.b   #UCA0RXIE,&IE2          ; Enable USCI_A0 RX interrupt
                                            ;
Mainloop    bis.b   #LPM4+GIE,SR            ; Enter LPM4, interrupts enabled
            nop                             ; Needed only for debugger
                                            ;
;-------------------------------------------------------------------------------
USCI0RX_ISR;  Echo back RXed character, confirm TX buffer is ready first
;-------------------------------------------------------------------------------
TX0         bit.b   #UCA0TXIFG,&IFG2        ; USCI_A0 TX buffer ready?
            jz      TX0                     ; Jump if TX buffer not ready
            mov.b   &UCA0RXBUF,&UCA0TXBUF   ; TX -> RXed character
            reti                            ;
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET                   ;
            .sect   ".int07"                ; USCI Vector
            .short  USCI0RX_ISR             ;        
            .end
