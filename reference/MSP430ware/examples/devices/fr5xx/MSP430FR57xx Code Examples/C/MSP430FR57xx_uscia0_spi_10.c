//******************************************************************************
//   MSP430F54x Demo - USCI_A0, SPI 3-Wire Slave Data Echo
//
//   Description: SPI slave talks to SPI master using 3-wire mode. Data received
//   from master is echoed back.  
//   ACLK = 32.768kHz, MCLK = SMCLK = DCO ~ 1MHz
//   Note: Ensure slave is powered up before master to prevent delays due to 
//   slave init.
//
//
//                   MSP430FR5739
//                 -----------------
//            /|\ |                 |
//             |  |                 |
//            -+->|                 |
//                |                 |
//                |             P2.0|-> Data Out (UCA0SIMO)
//                |                 |
//                |             P2.1|<- Data In (UCA0SOMI)
//                |                 |
//                |             P1.5|-> Serial Clock Out (UCA0CLK)
//
//
//   P. Thanigai
//   Texas Instruments Inc.
//   August 2010
//   Built with CCS V4 and IAR Embedded Workbench Version: 5.10
//******************************************************************************
#include "msp430fr5739.h"

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
  // Configure XT1
  PJSEL0 |= BIT4+BIT5;
  
  CSCTL0_H = 0xA5;
  CSCTL1 |= DCOFSEL0 + DCOFSEL1;             // Set max. DCO setting
  CSCTL2 = SELA_0 + SELS_3 + SELM_3;        // set ACLK = XT1; MCLK = DCO
  CSCTL3 = DIVA_0 + DIVS_3 + DIVM_3;        // set all dividers 
  CSCTL4 |= XT1DRIVE_0; 
  CSCTL4 &= ~XT1OFF;
  do
  {
    CSCTL5 &= ~XT1OFFG;
                                            // Clear XT1 fault flag
    SFRIFG1 &= ~OFIFG; 
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
  // Configure SPI pins
  P1SEL1 |= BIT5; 
  P2SEL1 |= BIT0 + BIT1;

  
  UCA0CTLW0 |= UCSWRST;                     // **Put state machine in reset**
  UCA0CTLW0 |= UCSYNC+UCCKPL+UCMSB;         // 3-pin, 8-bit SPI slave
                                            // Clock polarity high, MSB
  UCA0CTLW0 |= UCSSEL_2;                    // ACLK
  UCA0BR0 = 0x02;                           // /2
  UCA0BR1 = 0;                              //
  UCA0MCTLW = 0;                            // No modulation
  UCA0CTLW0 &= ~UCSWRST;                    // **Initialize USCI state machine**
  UCA0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt  
  
  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, enable interrupts
  


}

#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
  while (!(UCA0IFG&UCTXIFG));               // USCI_A0 TX buffer ready?
    UCA0TXBUF = UCA0RXBUF;                  // Echo received data
}
