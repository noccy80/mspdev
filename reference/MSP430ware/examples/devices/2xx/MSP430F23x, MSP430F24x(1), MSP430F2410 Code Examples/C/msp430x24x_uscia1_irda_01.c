//******************************************************************************
//  MSP430x24x Demo - USCI_A1 IrDA External Loopback Test, 8MHz SMCLK
//
//  Description: This example transmits bytes through the USCI module
//  configured for IrDA mode, and receives them using an external loopback
//  connection. The transfered sequence is 00h, 01h, 02h, ..., ffh. The
//  received bytes are also stored in memory starting at address RxData.
//  In the case of an RX error the LED is lighted and program execution stops.
//  An external loopback connection has been used as it allows for the
//  connection of a scope to monitor the communication, which is not possible
//  when using the internal loopback.
//  ACLK = n/a, MCLK = SMCLK = BRCLK = CALxxx_8MHZ = 8MHz
//
//              MSP430F249
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |     P3.7/UCA1RXD|--+   external
//           |     P3.6/UCA1TXD|--+   loopback connection
//           |                 |
//           |                 |
//           |             P1.0|--->  LED
//           |                 |
//
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include "msp430x24x.h" 

unsigned char RxByte;
volatile unsigned char RxData[256];
unsigned char TxByte;
volatile unsigned int i;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  if (CALBC1_8MHZ ==0xFF || CALDCO_8MHZ == 0xFF)                                     
  {  
    while(1);                               // If calibration constants erased
                                            // do not load, trap CPU!!
  }  
  DCOCTL = CALDCO_8MHZ;                     // Load 8MHz constants
  BCSCTL1 = CALBC1_8MHZ;
  P1OUT &= ~0x01;                           // Clear P1.0
  P1DIR |= 0x01;                            // P1.0 output
  P3SEL |= 0x0C0;                           // Use P3.6/P3.7 for USCI_A1
  UCA1CTL1 |= UCSWRST;                      // Set SW Reset
  UCA1CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
  UCA1BR0 = 52;                             // 8MHz/52=153.8KHz
  UCA1BR1 = 0;
  UCA1MCTL = UCBRF_1 + UCOS16;              // Set 1st stage modulator to 1
                                            // 16-times oversampling mode
  UCA1IRTCTL = UCIRTXPL2 + UCIRTXPL0 + UCIRTXCLK + UCIREN;
                                            // Pulse length = 6 half clock cyc
                                            // Enable BITCLK16, IrDA enc/dec
  UCA1CTL1 &= ~UCSWRST;                     // Resume operation

  TxByte = 0x00;                            // TX data and pointer, 8-bit

  while (1)
  {
    for (i = 1000; i; i--);                 // Small delay
    while (!(UC1IFG & UCA1TXIFG));            // USCI_A1 TX buffer ready?
    UCA1TXBUF = TxByte;                     // TX and Rx character

    __disable_interrupt();
    UC1IE |= UCA1RXIE;                        // Enable RX interrupt
    __bis_SR_register(CPUOFF + GIE);        // Enter LPM0 w/ interrupts

    RxData[TxByte] = RxByte;                // Store RXed character in RAM
    if (TxByte != RxByte)                   // RX OK?
    {
      P1OUT |= 0x01;                        // LED P1.0 on
      while (1);                            // Trap PC here
    }
    TxByte++;                               // Next character to TX
  }
}

#pragma vector = USCIAB1RX_VECTOR
__interrupt void USCIAB1RX_ISR(void)
{
  RxByte = UCA1RXBUF;                       // Get RXed character
  UC1IE &= ~UCA1RXIE;                         // Disable RX interrupt
  __bic_SR_register_on_exit(CPUOFF);        // Exit LPM0
}
