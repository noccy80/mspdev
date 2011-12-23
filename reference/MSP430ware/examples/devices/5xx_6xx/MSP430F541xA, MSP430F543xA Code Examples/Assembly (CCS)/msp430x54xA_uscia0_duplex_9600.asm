;******************************************************************************
;    MSP430F54xA Demo - USCI_A0, UART 9600 Full-Duplex Transceiver, 32K ACLK
;
;   Description: USCI_A0 communicates continuously as fast as possible
;   full-duplex with another device. Normal mode is LPM3, with activity only
;   during RX and TX ISR's. The TX ISR indicates the UART is ready to send
;   another character.  The RX ISR indicates the UART has received a character.
;   At 9600 baud, a full character is tranceived ~1ms.
;   The levels on P1.4/5 are TX'ed. RX'ed value is displayed on P1.0/1.
;   ACLK = BRCLK = LFXT1 = 32768, MCLK = SMCLK = DCO~ 1048k
;   Baud rate divider with 32768hz XTAL @9600 = 32768Hz/9600 = 3.41 (0003h 4Ah)
;
;
;                 MSP430F5438A                 MSP430F5438A
;              -----------------            -----------------
;         /|\ |              XIN|-     /|\ |              XIN|-
;          |  |                 | 32KHz |  |                 | 32KHz
;           --|RST          XOUT|-       --|RST          XOUT|-
;             |                 |          |                 |
;             |                 |          |                 |
;             |                 |          |                 |
;           ->|P1.4             |          |             P1.0|-> LED
;           ->|P1.5             |          |             P1.1|-> LED
;       LED <-|P1.0             |          |             P1.4|<-
;       LED <-|P1.1             |          |             P1.5|<-
;             |     UCA0TXD/P3.4|--------->|P3.5/UCA0RXD     |
;             |                 |   9600   |                 |
;             |     UCA0RXD/P3.5|<---------|P3.4/UCA0TXD     |
;
;
;   D. Dang
;   Texas Instruments Inc.
;   December 2009
;   Built with CCS Version: 4.0.2 
;******************************************************************************

    .cdecls C,LIST,"msp430x54xA.h"

count    .equ    R4 
delay    .equ    R12 
tx_char    .equ    R13 
;-------------------------------------------------------------------------------
            .global _main 
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x5C00,SP              ; Initialize stackpointer
            mov.w   #WDTPW + WDTHOLD,&WDTCTL; Stop WDT
            bis.b   #0x03,&P7SEL            ; Port select XT1

            ; Loop until XT1,XT2 & DCO stabilizes
do_while    bic.w  #XT2OFFG + XT1LFOFFG + DCOFFG,&UCSCTL7
                                            ; Clear XT2,XT1,DCO fault flags
            bic.w  #OFIFG,&SFRIFG1          ; Clear fault flags
            mov.w  #0xFFFF,count            ; Load delay counter
osc_delay   dec.w  count                    ; Decrement counter
            jne    osc_delay
            bit.w  #OFIFG,&SFRIFG1          ; Test oscillator fault flag
            jc     do_while

            clr.b  P1OUT                    ; P1.0/1 setup for LED output
            bis.b  #BIT0 + BIT1,&P1DIR
            bis.b  #BIT4 + BIT5,&P3SEL      ; P3.4,5 UART option select
            bis.b  #UCSWRST,&UCA0CTL1       ; **Reset USCI state machine **
            bis.b  #UCSSEL_1,&UCA0CTL1      ; CLK = ACLK
            mov.b  #0x03,&UCA0BR0           ; 32k/9600 - 3.41
            mov.b  #0x00,&UCA0BR1
            mov.b  #0x06,&UCA0MCTL          ; Modulation
            bic.b  #UCSWRST,&UCA0CTL1       ; **Initialize USCI state machine**
            bis.b  #UCRXIE + UCRXIE,&UCA0IE ; Enable USCI_A0 TX/RX interrupt

            bis.w  #LPM3 + GIE,SR           ; Enter LPM3, enable interrupts
            nop                             ; For debugger

;-------------------------------------------------------------------------------
USCI_A0_ISR
;-------------------------------------------------------------------------------
            clr.b  tx_char
            clr.b  delay
check_TXIFG bit.b  #UCTXIFG,&UCA0IFG        ; TXBUF is empty?
            jnc    check_RXIFG              ; no -> Check for RXIFG
            mov.b  #240,delay               ; yes -> Load delay counter
tx_delay    dec.w  delay                    ; Add small gap between TX'ed bytes
            jne    tx_delay
            mov.b  &P1IN,tx_char
            rra.b  tx_char
            rra.b  tx_char
            rra.b  tx_char
            rra.b  tx_char
            mov.b  tx_char,&UCA0TXBUF       ; Transmit character
            jmp    exit_isr
check_RXIFG bit.b  #UCRXIFG,&UCA0IFG        ; Received a character?
            jnc    exit_isr                 ; no -> Jump to exit_isr
            mov.b  &UCA0RXBUF,&P1OUT        ; yes -> Move RXBUF1 to P1OUT for TX
exit_isr    reti                            ; Return from interrupt

;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int57"    
            .short  USCI_A0_ISR
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end