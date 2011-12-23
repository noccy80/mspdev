;******************************************************************************
;   MSP430F5438 Demo - USCI_A0, 9600 UART, SMCLK, LPM0, Echo with over-sampling
;
;   Description: Echo a received character, RX ISR used. Normal mode is LPM0.
;   USCI_A0 RX interrupt triggers TX Echo.
;   If UCOS16=1, UCBRx=Fbrclk/(16*Baudrate)
;   Baud rate divider with UCBRx = 1MHz/(16*9600) = ~6.8
;   ACLK = REFO = ~32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
;   See User Guide for baud rate divider table
;
;                MSP430F5438
;             -----------------
;         /|\|                 |
;          | |                 |
;          --|RST              |
;            |                 |
;            |     P3.4/UCA0TXD|------------>
;            |                 | 9600 - 8N1
;            |     P3.5/UCA0RXD|<------------
;
;   M. Morales
;   Texas Instruments Inc.
;   September 2008
;   Built with Code Composer Essentials v3.x
;******************************************************************************

    .cdecls C,LIST,"msp430x54x.h"

;-------------------------------------------------------------------------------
            .global _main 
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x5C00,SP              ; Initialize stackpointer
            mov.w   #WDTPW + WDTHOLD,&WDTCTL; Stop WDT    
            mov.b   #0x30,&P3SEL            ; P3.4,5 = USCI_A0 TXD/RXD
            bis.b   #UCSWRST,&UCA0CTL1      ; **Put state machine in reset**
            bis.b   #UCSSEL_2,&UCA0CTL1     ; CLK = SMCLK
            mov.b   #0x06,&UCA0BR0          ; 1MHz 9600 (see User's Guide)
            mov.b   #0x00,&UCA0BR1
            mov.b   #UCBRS_0 + UCBRF_13 + UCOS16,&UCA0BR1
                                            ; Modulation UCBRSx=0, UCBRFx=0,                                           
            bic.b   #UCSWRST,&UCA0CTL1      ; **Initialize USCI state machine**
            bis.b   #UCRXIE,&UCA0IE         ; Enable USCI_A0 RX interrupt

            bis.b   #LPM0 + GIE,SR          ; Enter LPM0, interrupts enabled
            nop                             ; For debugger 

;-------------------------------------------------------------------------------
USCI_A0_ISR
;-------------------------------------------------------------------------------
            ; Echo back RXed character, confirm TX buffer is ready first
            add.w   &UCA0IV,PC      
            reti                            ; Vector 0 - no interrupt
            jmp     RXIFG_HND               ; Vector 2 - RXIFG
            reti                            ; Vector 4 - TXIFG

RXIFG_HND
wait_TX_rdy bit.b   #UCTXIFG,&UCA0IFG       ; USCI_A0 TX buffer ready? 
            jnc     wait_TX_rdy
            mov.b   &UCA0RXBUF,&UCA0TXBUF   ; RXBUF -> TXBUF
            reti                            ; Return from interrupt 

;-------------------------------------------------------------------------------
                  ; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".int57"    
            .short  USCI_A0_ISR
            .sect   ".reset"                ; POR, ext. Reset
            .short  RESET
            .end
            