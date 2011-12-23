//******************************************************************************
//   CC430F513x Demo - USCI_A0, UART 9600 Full-Duplex Transceiver, 32K ACLK
//
//   Description: USCI_A0 communicates continuously as fast as possible
//   full-duplex with another device. Normal mode is LPM3, with activity only
//   during RX and TX ISR's. The TX ISR indicates the UART is ready to send
//   another character.  The RX ISR indicates the UART has received a character.
//   At 9600 baud, a full character is tranceived ~1ms.
//   The levels on P1.4/5 are TX'ed. RX'ed value is displayed on P1.0/1.
//   ACLK = BRCLK = LFXT1 = 32768, MCLK = SMCLK = DCO~ 1048k
//   Baud rate divider with 32768hz XTAL @9600 = 32768Hz/9600 = 3.41 (0003h 4Ah)
//
//
//                 CC430F5137                  CC430F5137
//              -----------------            -----------------
//         /|\ |              XIN|-     /|\ |              XIN|-
//          |  |                 | 32KHz |  |                 | 32KHz
//           --|RST          XOUT|-       --|RST          XOUT|-
//             |                 |          |                 |
//             |                 |          |                 |
//             |                 |          |                 |
//           ->|P1.4             |          |             P1.0|-> LED
//           ->|P1.5             |          |             P1.1|-> LED
//       LED <-|P1.0             |          |             P1.4|<-
//       LED <-|P1.1             |          |             P1.5|<-
//             |     UCA0TXD/P2.7|--------->|P2.6/UCA0RXD     |
//             |                 |   9600   |                 |
//             |     UCA0RXD/P2.6|<---------|P2.7/UCA0TXD     |
//
//
//   M Morales
//   Texas Instruments Inc.
//   April 2009
//   Built with CCE Version: 3.2.2 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************

#include "cc430x513x.h"

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
  
  P5SEL |= 0x03;                            // Enable XT1 pins
  
  do
  {
    UCSCTL7 &= ~(XT1LFOFFG + DCOFFG);
                                            // Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
    __delay_cycles(100000);                 // Delay for Osc to stabilize
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag

  P1OUT = 0x000;                            // P1.0/1 setup for LED output
  P1DIR |= BIT0+BIT1;                       //

  PMAPPWD = 0x02D52;                        // Get write-access to port mapping regs  
  P2MAP6 = PM_UCA0RXD;                      // Map UCA0RXD output to P2.6 
  P2MAP7 = PM_UCA0TXD;                      // Map UCA0TXD output to P2.7 
  PMAPPWD = 0;                              // Lock port mapping registers 
  
  P2DIR |= BIT7;                            // Set P2.7 as TX output
  P2SEL |= BIT6 + BIT7;                     // Select P2.6 & P2.7 to UART function

  UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
  UCA0CTL1 |= UCSSEL_1;                     // CLK = ACLK
  UCA0BR0 = 0x03;                           // 32k/9600 - 3.41
  UCA0BR1 = 0x00;                           //
  UCA0MCTL = 0x06;                          // Modulation
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  UCA0IE |= UCTXIE + UCRXIE;                // Enable USCI_A0 TX/RX interrupt

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/ interrupts enabled
  __no_operation();                         // For debugger
}


#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
  unsigned char tx_char;

    switch(__even_in_range(UCA0IV,4))
  {
    case 0: break;                          // Vector 0 - no interrupt
    case 2:                                 // Vector 2 - RXIFG
      P1OUT = UCA0RXBUF;                    // RXBUF1 to TXBUF1
      break;
    case 4:                                 // Vector 4 - TXIFG
      __delay_cycles(5000);                 // Add small gap between TX'ed bytes
      tx_char = P1IN;
      tx_char = tx_char >> 4;
      UCA0TXBUF = tx_char;                  // Transmit character
      break;
    default: break;
  }
}
