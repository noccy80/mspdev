//******************************************************************************
//  MSP430F22x4 Demo - USCI_A0 IrDA Monitor, 8MHz SMCLK
//
//  Description: This example receives bytes through the USCI module
//  configured for IrDA mode, and sends them out as ASCII strings using the
//  Timer_A UART to a PC running a terminal software. The code can be used
//  to monitor and log an IrDA communication.
//
//  ACLK = n/a, MCLK = SMCLK = BRCLK = CALxxx_8MHZ = 8MHz
//
//                                     MSP430F22x4
//                               -----------------------
//                              |                       |
//                           /|\|                    XIN|-
//                            | |                       |
//                            --|RST                XOUT|-
//                              |                       |
//    GP2W0116YPS   /|\         |                       |
//      -------      |          |                       |
//     |    Vcc|-----+  IrDA    |               P2.4/TA2|--> 115,200 8N1
//     #    LED|-----+ 9600 8N1 |                       |    Terminal SW
//     #    TxD|<---------------|P3.4/UCA0TXD           |
//     #    RxD|--------------->|P3.5/UCA0RXD           |
//     #     SD|-----+          |                       |
//     |    GND|-----+          |                       |
//      -------      |           -----------------------
//                  ---
//
//  A. Dannenberg
//  Texas Instruments Inc.
//  April 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

#define BITTIME     69                      // UART bit time = 8MHz / 115,200

unsigned char RxByte;
unsigned int TXData;                        // Data to transmit
unsigned char TxBitCnt;                     // Keeps track of # bits TX'd

//  Table for nibble-to-ASCII conversion
unsigned const char Nibble2ASCII[] =
{
  '0',
  '1',
  '2',
  '3',
  '4',
  '5',
  '6',
  '7',
  '8',
  '9',
  'A',
  'B',
  'C',
  'D',
  'E',
  'F'
};

// Function prototypes
void TX_Byte(unsigned char Data);

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  DCOCTL = CALDCO_8MHZ;                     // Load 8MHz constants
  BCSCTL1 = CALBC1_8MHZ;
  P2SEL |= 0x10;                            // Use P2.4 for Timer_A
  P2DIR |= 0x10;                            // P2.4 output
  P3SEL |= 0x30;                            // Use P3.4/P3.5 for USCI_A0
  UCA0CTL1 |= UCSWRST;                      // Set SW Reset
  UCA0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
  UCA0BR0 = 52;                             // 8MHz/52=153.8KHz
  UCA0BR1 = 0;
  UCA0MCTL = UCBRF_1 + UCOS16;              // Set 1st stage modulator to 1
                                            // 16-times oversampling mode
  UCA0IRTCTL = UCIRTXPL2 + UCIRTXPL0 + UCIRTXCLK + UCIREN;
                                            // Pulse length = 6 half clock cyc
                                            // Enable BITCLK16, IrDA enc/dec
  UCA0IRRCTL = UCIRRXPL;                    // Light = low pulse
  UCA0CTL1 &= ~UCSWRST;                     // Resume operation
  TACCTL2 = OUT;                            // TXD Idle as Mark
  TACTL = TASSEL_2 + MC_2;                  // SMCLK, continuous mode

  while (1)
  {
    __disable_interrupt();
    IE2 |= UCA0RXIE;                        // Enable RX int
    __bis_SR_register(CPUOFF + GIE);        // Enter LPM0 w/ interrupts

    TX_Byte(Nibble2ASCII[(RxByte >> 4) & 0x0f]);  // TX upper nibble
    while (TACCTL2 & CCIE);                 // Loop while TX is pending

    TX_Byte(Nibble2ASCII[RxByte & 0x0f]);   // TX lower nibble
    while (TACCTL2 & CCIE);                 // Loop while TX is pending

    TX_Byte(' ');                           // TX space character
    while (TACCTL2 & CCIE);                 // Loop while TX is pending
  }
}

//------------------------------------------------------------------------------
// TX the byte 'Data' using Timer_A UART
//------------------------------------------------------------------------------
void TX_Byte(unsigned char Data)
{
  TxBitCnt = 10;                            // Load Bit counter, 8 data + ST/SP
  TACCR2 = TAR;                             // Current state of TA counter
  TACCR2 += BITTIME;                        // Some time till first bit
  TXData = Data;                            // Load global variable
  TXData |= 0x0100;                         // Add mark stop bit
  TXData <<= 1;                             // Add space start bit
  TACCTL2 = OUTMOD0 + CCIE;                 // TXD = mark = idle
}

//------------------------------------------------------------------------------
// Read RXed character, return from LPM0
//------------------------------------------------------------------------------
#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void)
{
  RxByte = UCA0RXBUF;                       // Get RXed character
  IE2 &= ~UCA0RXIE;                         // Disable RX int
  __bic_SR_register_on_exit(CPUOFF);        // Exit LPM0
}

//------------------------------------------------------------------------------
// Timer_A UART TX
//------------------------------------------------------------------------------
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A1_ISR(void)
{
  switch (TAIV)        // Use calculated branching
  {
    case  2 :                               // TACCR1 CCIFG
      break;
    case  4 :                               // TACCR2 CCIFG - UART TX
      TACCR2 += BITTIME;                    // Add Offset to TACCR2
      if (TxBitCnt == 0)                    // All bits TXed?
      {
        TACCTL2 &= ~CCIE;                   // All bits TXed, disable interrupt
      }
      else
      {
        if (TXData & 0x01)
          TACCTL2 &= ~OUTMOD2;              // TX Mark
        else
          TACCTL2 |= OUTMOD2;               // TX Space
        TXData >>= 1;
        TxBitCnt--;
      }
      break;
  }
}
