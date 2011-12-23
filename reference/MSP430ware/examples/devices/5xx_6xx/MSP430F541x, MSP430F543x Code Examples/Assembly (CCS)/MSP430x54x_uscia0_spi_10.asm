;******************************************************************************
;   MSP430F54x Demo - USCI_A0, SPI 3-Wire Slave Data Echo
;
;   Description: SPI slave talks to SPI master using 3-wire mode. Data received
;   from master is echoed back.  USCI RX ISR is used to handle communication,
;   CPU normally in LPM4.  Prior to initial data exchange, master pulses
;   slaves RST for complete reset.
;   ACLK = ~32.768kHz, MCLK = SMCLK = DCO ~ 1048kHz
;
;   Use with SPI Master Incremented Data code example.  If the slave is in
;   debug mode, the reset signal from the master will conflict with slave's
;   JTAG; to work around, use IAR's "Release JTAG on Go" on slave device.  If
;   breakpoints are set in slave RX ISR, master must stopped also to avoid
;   overrunning slave RXBUF.
;
;                   MSP430F5438
;                 -----------------
;            /|\ |                 |
;             |  |                 |
;    Master---+->|RST          P1.0|-> LED
;                |                 |
;                |             P3.4|-> Data Out (UCA0SIMO)
;                |                 |
;                |             P3.5|<- Data In (UCA0SOMI)
;                |                 |
;                |             P3.0|-> Serial Clock Out (UCA0CLK)
;
;
;   M. Morales
;   Texas Instruments Inc.
;   September 2008
;   Built with Code Composer Essentials v3.x
;******************************************************************************

    .cdecls C,LIST,"msp430x54x.h"

count    .equ    R4 

;-------------------------------------------------------------------------------
            .global _main 
            .text                           ; Assemble to Flash memory
;-------------------------------------------------------------------------------
_main
RESET       mov.w   #0x5C00,SP              ; Initialize stackpointer
            mov.w   #WDTPW + WDTHOLD,&WDTCTL; Stop WDT

poll_P3_0   bit.b   #BIT0,&P3IN             ; If clock sig from mstr stays low,
            jnc     poll_P3_0               ; ... it is not yet in SPI mode

            bis.b   #0x31,&P3SEL            ; P3.5,4,0 option select
            bis.b   #UCSWRST,&UCA0CTL1      ; **Put state machine in reset**
            bis.b   #UCSYNC + UCCKPL + UCMSB,&UCA0CTL0
                                            ; 3-pin, 8-bit SPI slave,
                                            ; Clock polarity high, MSB
            bic.b   #UCSWRST,&UCA0CTL1      ; **Initialize USCI state machine**
            bis.b   #UCRXIE,&UCA0IE         ; Enable USCI_A0 RX interrupt

            bis.w   #LPM4 + GIE,SR          ; Enter LPM4, enable interrupts
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
