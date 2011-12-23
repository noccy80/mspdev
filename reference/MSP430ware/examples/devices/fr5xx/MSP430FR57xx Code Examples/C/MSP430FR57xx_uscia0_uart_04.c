//******************************************************************************
//  MSP430FR57xx Demo - USCI_A0 External Loopback test
//
//  Description: This demo connects TX to RX of the MSP430 UART 
//  The example code shows proper initialization of registers 
//  and interrupts to receive and transmit data.
//  ACLK = n/a, MCLK = SMCLK = BRCLK = default DCO = ~1MHz
//
//                                
//                MSP430FR5739 
//                       
//             -----------------   
//       RST -|     P2.0/UCA0TXD|----|
//            |                 |    |
//           -|                 |    |
//            |     P2.1/UCA0RXD|----|
//            |                 |  
//
//   P. Thanigai
//   Texas Instruments Inc.
//   August 2010
//   Built with CCS V4 and IAR Embedded Workbench Version: 5.10
//******************************************************************************
#include "msp430fr5739.h"

unsigned int i;
unsigned char RXData = 0;
unsigned char TXData = 0;
unsigned char check = 0;
void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // stop watchdog
 
  // XT1 Setup 
  
  PJSEL0 |= BIT4 + BIT5; 
  
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
  
  // Configure UART pins
  P2SEL1 |= BIT0 + BIT1;
  P2SEL0 &= ~(BIT0 + BIT1);
  // Configure UART 0
  UCA0CTL1 |= UCSWRST; 
  UCA0CTL1 = UCSSEL_1;                      // Set ACLK = 32768 as UCBRCLK
  UCA0BR0 = 3;                              // 9600 baud
  UCA0MCTLW |= 0x5300;                      // 32768/9600 - INT(32768/9600)=0.41
                                            // UCBRSx value = 0x53 (See UG)  
  UCA0BR1 = 0;            
  UCA0CTL1 &= ~UCSWRST;                     // release from reset
  UCA0IE |= UCRXIE;                         // enable RX interrupt
  
  __enable_interrupt();                     // Enable interrupt
  while (1)
  {
    TXData = TXData+1;                      // Increment TX data
    UCA0TXBUF = TXData;                     // Load data onto buffer
    while(check !=1 );
    check = 0;  
  }
}



#pragma vector = USCI_A0_VECTOR             // USCI ISR
__interrupt void USCI_A0_ISR(void)
{
  UCA0IFG &=~ UCRXIFG;                      // Clear interrupt
  RXData = UCA0RXBUF;                       // Clear buffer
  if(!(RXData == TXData))                   // Check value
  {
    while(1);
  }
  check =1;
  
} 
