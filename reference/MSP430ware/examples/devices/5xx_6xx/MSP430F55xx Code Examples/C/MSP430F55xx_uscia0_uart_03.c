//******************************************************************************
//   MSP430F552x Demo - USCI_A0, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK
//
//   Description: Echo a received character, RX ISR used. Normal mode is LPM3,
//   USCI_A0 RX interrupt triggers TX Echo.
//   ACLK = 32768Hz crystal, MCLK = SMCLK = DCO ~1.045MHz
//   Baud rate divider with 32768Hz XTAL @9600 = 32768Hz/9600 = 3.41
//   See User Guide for baud rate divider table
//
//                MSP430F552x
//             -----------------
//        /|\ |              XIN|-
//         |  |                 | 32kHz
//         ---|RST          XOUT|-
//            |                 |
//            |     P3.3/UCA0TXD|------------>
//            |                 | 9600 - 8N1
//            |     P3.4/UCA0RXD|<------------
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   April 2009
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************

#include <msp430f5529.h>

void main(void)
{
  unsigned char i;

  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

  P3SEL = BIT3+BIT4;                        // P3.4,5 = USCI_A0 TXD/RXD
//.......................
//  P5SEL |= BIT4+BIT5;                       // Select XT1
//
//  UCSCTL6 &= ~(XT1OFF);                     // XT1 On
//  UCSCTL6 |= XCAP_3;                        // Internal load cap
//  UCSCTL3 = 0;                              // FLL Reference Clock = XT1
//
//  // Loop until XT1,XT2 & DCO stabilizes - In this case loop until XT1 and DCo settle
//  do
//  {
//    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
//                                            // Clear XT2,XT1,DCO fault flags
//    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
//  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
//  
//  UCSCTL6 &= ~(XT1DRIVE_3);                 // Xtal is now stable, reduce drive strength
//
//  UCSCTL4 |= SELA_0 + SELS_4 + SELM_4;      // ACLK = LFTX1
//                                            // SMCLK = default DCO
//                                            // MCLK = default DCO
//  
  //................
  UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
  UCA0CTL1 |= UCSSEL_1;                     // CLK = ACLK
  UCA0BR0 = 0x03;                           // 32kHz/9600=3.41 (see User's Guide)
  UCA0BR1 = 0x00;                           //
  UCA0MCTL = UCBRS_3+UCBRF_0;               // Modulation UCBRSx=3, UCBRFx=0
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  UCA0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3, interrupts enabled
  __no_operation();                         // For debugger
}

// Echo back RXed character, confirm TX buffer is ready first
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
  switch(__even_in_range(UCA0IV,4))
  {
  case 0:break;                             // Vector 0 - no interrupt
  case 2:                                   // Vector 2 - RXIFG
    while (!(UCA0IFG&UCTXIFG));             // USCI_A0 TX buffer ready?
    UCA0TXBUF = UCA0RXBUF;                  // TX -> RXed character
    break;
  case 4:break;                             // Vector 4 - TXIFG
  default: break;  
  }
}
