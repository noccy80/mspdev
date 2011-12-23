//******************************************************************************
//   MSP430F54x Demo - USCI_A0, SPI 3-Wire Master Incremented Data
//
//   Description: SPI master talks to SPI slave using 3-wire mode. Incrementing
//   data is sent by the master starting at 0x01. Received data is expected to
//   be same as the previous transmission TXData = RXData-1.  
//   USCI RX ISR is used to handle communication with the CPU, normally in LPM0. 
//   ACLK = ~32.768kHz, MCLK = SMCLK = DCO ~1MHz.  BRCLK = ACLK/2
//
//
//                   MSP430FR5739
//                 -----------------
//             /|\|                 |
//              | |                 |
//              --|RST              |
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

unsigned char RXData =0;
unsigned char TXData;

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
  P1DIR |= BIT0;
  P1OUT &= ~BIT0;

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

  P1SEL1 |= BIT5; 
  P2SEL1 |= BIT0 + BIT1;
  UCA0CTLW0 |= UCSWRST;                     // **Put state machine in reset**
  UCA0CTLW0 |= UCMST+UCSYNC+UCCKPL+UCMSB;   // 3-pin, 8-bit SPI master
                                            // Clock polarity high, MSB
  UCA0CTLW0 |= UCSSEL_1;                    // ACLK
  UCA0BR0 = 0x02;                           // /2
  UCA0BR1 = 0;                              //
  UCA0MCTLW = 0;                            // No modulation
  UCA0CTLW0 &= ~UCSWRST;                    // **Initialize USCI state machine**
  UCA0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt
  TXData = 0x1;                             // Holds TX data

  while(1)
  {
     
    UCA0IE |= UCTXIE;
    __bis_SR_register(LPM0_bits + GIE);      // CPU off, enable interrupts
    __no_operation();                       // Remain in LPM0 
    __delay_cycles(2000);                   // Delay before next transmission
    TXData++;                               // Increment transmit data
  }

}

#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
  volatile unsigned int i;

  switch(__even_in_range(UCA0IV,0x04))
  {
    case 0: break;                          // Vector 0 - no interrupt
    case 2: 
           RXData = UCA0RXBUF; 
           UCA0IFG &= ~UCRXIFG;
           __bic_SR_register_on_exit(CPUOFF);// Wake up to setup next TX
           break;
    case 4: 
          UCA0TXBUF = TXData;             // Transmit characters
          UCA0IE &= ~UCTXIE; 
          break;
    default: break;
  }
}
