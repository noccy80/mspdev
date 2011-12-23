//******************************************************************************
//  MSP430F22x4 Demo - USCI_A0 IrDA Physical Layer Comm, 8MHz SMCLK
//
//  Description: This example receives bytes through the USCI module
//  configured for IrDA mode, and sends them out using the Timer_A UART
//  to a PC running a terminal software. Likewise, data received from the PC
//  through the Timer_A UART link is transmitted via IrDA.
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
//     #    LED|-----+ 9600 8N1 |               P2.3/TA1|<-- Terminal SW
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
#define BITTIME_5   35                      // UART half bit time

#define FLAG_USCI   0x01                    // USCI data received
#define FLAG_UART   0x02                    // Timer_A UART data received

unsigned int TXData;                        // Timer_A UART TX data
unsigned char TxBitCnt;                     // Timer_A UART TX bit counter
unsigned char RXData;                       // Timer_A UART RX data
unsigned char RxBitCnt;                     // Timer_A UART RX bit counter
unsigned char Flags;                        // Flag register
unsigned char RXDataIR;                     // Received IrDA data

// Function prototypes
void RX_Ready(void);
void TX_Byte(unsigned char Data);

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  DCOCTL = CALDCO_8MHZ;                     // Load 8MHz constants
  BCSCTL1 = CALBC1_8MHZ;
  P2SEL |= 0x18;                            // Use P2.3/P2.4 for Timer_A
  P2DIR |= 0x10;                            // P2.4 output
  P3SEL |= 0x30;                            // Use P3.4/P3.5 for USCI_A0
  UCA0CTL1 |= UCSWRST;                      // Set SW Reset
  UCA0CTL1 = UCSSEL_2 + UCSWRST;
  UCA0BR0 = 52;                             // 8MHz/52=153.8KHz
  UCA0BR1 = 0;
  UCA0MCTL = UCBRF_1 + UCOS16;
  UCA0IRTCTL = UCIRTXPL2 + UCIRTXPL0 + UCIRTXCLK + UCIREN;
                                            // Pulse length = 6 half clock cyc
                                            // Enable BITCLK16, IrDA enc/dec
  UCA0IRRCTL = UCIRRXPL;                    // Light = low pulse
  UCA0CTL1 &= ~UCSWRST;                     // Resume operation
  IE2 |= UCA0RXIE;                          // Enable RX int
  TACCTL2 = OUT;                            // TXD Idle as Mark
  TACTL = TASSEL_2 + MC_2;                  // SMCLK, continuous mode
  RX_Ready();                               // Ready Timer_A UART for RX

  while (1)
  {
    __disable_interrupt();                  // Disable interrupts
    if (!Flags)                             // Any events pending?
      __bis_SR_register(CPUOFF + GIE);      // Enter LPM0 w/ interrupts

    __enable_interrupt();                   // Enable interrupts

    if (Flags & FLAG_USCI)                  // USCI_A0 character received?
    {
      while (TACCTL2 & CCIE);               // Yes, ensure Timer_A UART is ready
      TX_Byte(RXDataIR);                    // Transmit using Timer_A UART
      Flags &= ~FLAG_USCI;                  // Clear flag
      IE2 |= UCA0RXIE;                      // Re-enable RX int
    }

    if (Flags & FLAG_UART)                  // Timer_A UART character received?
    {
      while (!(IFG2 & UCA0TXIFG));          // Ensure TX buffer is ready
      UCA0TXBUF = RXData;                   // Move RX'd character to USCI_A0
      Flags &= ~FLAG_UART;                  // Clear flag
      RX_Ready();                           // Ready Timer_A UART for RX
    }
  }
}

//------------------------------------------------------------------------------
// Read RXed character from USCI_A0, return from LPM0
//------------------------------------------------------------------------------
#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void)
{
  RXDataIR = UCA0RXBUF;                     // Get RXed character
  IE2 &= ~UCA0RXIE;                         // Disable RX int
  Flags |= FLAG_USCI;                       // Indicate received character
  __bic_SR_register_on_exit(CPUOFF);        // Return active after receiption
}

//------------------------------------------------------------------------------
// Readies the Timer_A UART to receive on byte
//------------------------------------------------------------------------------
void RX_Ready(void)
{
  RxBitCnt = 8;                             // Load Bit counter
  TACCTL1 = SCS + CCIS0 + CM1 + CAP + CCIE; // Sync, Neg Edge, Capture
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
// Timer_A UART RX and TX
//------------------------------------------------------------------------------
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A1_ISR(void)
{
  switch (TAIV)        // Use calculated branching
  {
    case  2 :                               // TACCR1 CCIFG - UART RX
      TACCR1 += BITTIME;                    // Add Offset to TACCR1
      if (TACCTL1 & CAP)                    // Capture mode = start bit edge
      {
        TACCTL1 &= ~CAP;                    // Capture to compare mode
        TACCR1 += BITTIME_5;
      }
      else
      {
        RXData >>= 1;
        if (TACCTL1 & SCCI)                 // Get bit waiting in receive latch
          RXData |= 0x80;
        RxBitCnt--;
        if (RxBitCnt == 0)                  // All bits RXed?
        {
          TACCTL1 &= ~CCIE;                 // All bits RXed, disable interrupt
          Flags |= FLAG_UART;               // Indicate received character
          __bic_SR_register_on_exit(CPUOFF);// Clear LPM0 bits from 0(SR)
        }
      }
      break;
    case  4 :                               // TACCR2 CCIFG - UART TX
      TACCR2 += BITTIME;                    // Add Offset to TACCR2
      if (TxBitCnt == 0)                    // All bits TXed?
      {
        TACCTL2 &= ~CCIE;                   // All bits TXed, disable interrupt
        __bic_SR_register_on_exit(CPUOFF);  // Clear LPM0 bits from 0(SR)
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
