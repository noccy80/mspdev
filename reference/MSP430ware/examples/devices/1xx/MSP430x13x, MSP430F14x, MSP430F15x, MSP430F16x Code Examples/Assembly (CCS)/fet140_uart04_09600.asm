;******************************************************************************
;   MSP-FET430P140 Demo - USART0, UART 9600 Echo ISR, No XTAL, Rosc DCO Only
;
;   Description: Echo a received character, USART0 RX ISR at high-speed using
;   no XTAL and external resistor for DCO stabilized. DCO used for UART baud
;   generation. On valid RX character, character echoed back. Using a 100k
;   resistor on ROSC, with default DCO setting, set DCOCLK ~ 2MHz.
;   ACLK = n/a  MCLK = SMCLK = UCLK0 = DCOCLK  ~ 2MHz
;   Baud rate divider with 2MHz = 2MHz/9600 ~ 208 (00D0h)
;   //* Use of external resistor reduces temperature sensitivity of DCOCLK *//
;
;                MSP430F149
;             -----------------
;   /|\   /|\|              XIN|-
;    |     | |                 |
;   100k   --|RST          XOUT|-
;    |       |                 |
;    +-------|P2.5/ROSC    P3.4|------------>
;            |                 |  9600 - 8N1
;            |             P3.5|<------------
;
;   M. Buccini / G. Morton
;   Texas Instruments Inc.
;   May 2005
;   Built with Code Composer Essentials Version: 1.0
;******************************************************************************
 .cdecls C,LIST,  "msp430x14x.h"
;------------------------------------------------------------------------------
            .text                           ; Progam Start
;------------------------------------------------------------------------------
RESET       mov.w   #0A00h,SP               ; Initialize stackpointer
StopWDT     mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
SetupP3     bis.b   #030h,&P3SEL            ; P3.4,5 = USART0 TXD/RXD
SetupBC     bis.b   #DCOR,&BCSCTL2          ; Rosc
            bis.w   #OSCOFF,SR              ; XTAL not used
SetupUART0  bis.b   #UTXE0+URXE0,&ME1       ; Enable USART0 TXD/RXD
            bis.b   #CHAR,&UCTL0            ; 8-bit char
            bis.b   #SSEL1,&UTCTL0          ; UCLK = SMCLK
            mov.b   #0D0h,&UBR00            ; 2MHz 9600
            mov.b   #000h,&UBR10            ;
            mov.b   #000h,&UMCTL0           ; no modulation
            bic.b   #SWRST,&UCTL0           ; **Initialize USART state machine**
            bis.b   #URXIE0,&IE1            ; Enable USART0 RX interrupt
                                            ;
Mainloop    bis.b   #CPUOFF+GIE,SR          ; Enter LPM0, interrupts enabled
            nop                             ; Needed only for debugger
                                            ;
;------------------------------------------------------------------------------
USART0RX_ISR;  Echo back RXed character, confirm TX buffer is ready first
;------------------------------------------------------------------------------
TX1         bit.b   #UTXIFG0,&IFG1          ; USART0 TX buffer ready?
            jz      TX1                     ; Jump is TX buffer not ready
            mov.b   &RXBUF0,&TXBUF0         ; TX -> RXed character
            reti                            ;
                                            ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect   ".reset"                ;
            .short  RESET                   ; POR, ext. Reset, Watchdog
            .sect   ".int09"                ;
            .short  USART0RX_ISR            ; USART0 receive
            .end