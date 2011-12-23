//******************************************************************************
//  MSP430x21x1 Demo - Timer_A UART 115k, 8MHz DCO SMCLK
//
//  Description: Use Timer_A CCR0 hardware output modes and SCCI data latch
//  to implement UART function @ 115k baud. Software does not directly read and
//  write to RX and TX pins, instead proper use of output modes and SCCI data
//  latch are demonstrated. Use of these hardware features eliminates ISR
//  latency effects as hardware insures that output and input bit latching and
//  timing are perfectly synchronised with Timer_A regardless of other
//  software activity. In the Mainloop the UART function readies the UART to
//  receive one character and waits in LPM3 with all activity interrupt driven.
//  After a character has been received, the UART receive function forces exit
//  from LPM0 in the Mainloop which echo's back the received character.
//  The DCO frequency settings are stored in INFOA flash segment.
//  ACLK = LFXT1 = 32768, MCLK = SMCLK = saved DCO 8Mhz
//
//
//               MSP430F21x1
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//           |             P1.3|--------> Power for MAX3221
//           |   CCI0A/TXD/P1.1|-------->
//           |                 | 115200 8N1
//           |   CCI0B/RXD/P2.2|<--------
//
//   H. Grewal / A. Dannenberg
//   Texas Instruments, Inc
//   July 2005
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.30A
//*****************************************************************************

#include <msp430x21x1.h>

#define RXD   0x04                          // RXD on P2.2
#define TXD   0x02                          // TXD on P1.1

//   Conditions for 115200 Baud SW UART, DCO = 8000000Hz
#define Bitime_5  0x024                     // ~ 0.5 bit length
#define Bitime    0x045                     // ~ 115942 baud

unsigned int RXTXData;
unsigned char BitCnt;

void TX_Byte(void);
void RX_Ready(void);

void main (void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  BCSCTL1 = CALBC1_8MHZ;                    // Set DCO
  DCOCTL = CALDCO_8MHZ;

  TACTL = TASSEL_2 + MC_2 + TACLR;          // SMCLK, cont-mode, clear

  CCTL0 = OUT;                              // TXD Idle as Mark
  P1SEL = TXD;                              // P1.1/TA0 for TXD function
  P1DIR = TXD;                              // TXD output on P1
  P2SEL = RXD;                              // P2.2/TA0 as RXD input

  P1DIR |= 0x08;                            // Power MAX3221
  P1OUT |= 0x08;                            //

// Mainloop
  for (;;)
  {
  RX_Ready();                               // UART ready to RX one Byte
  _BIS_SR(LPM3_bits + GIE);                 // Enter LPM3 w/ interr until char RXed
  TX_Byte();                                // TX Back RXed Byte Received
  }
}

// Function Transmits Character from RXTXData Buffer
void TX_Byte (void)
{
  BitCnt = 0xA;                             // Load Bit counter, 8data + ST/SP
  CCR0 = TAR;                               // Current state of TA counter
  CCR0 += Bitime;                           // Some time till first bit
  RXTXData |= 0x100;                        // Add mark stop bit to RXTXData
  RXTXData = RXTXData << 1;                 // Add space start bit
  CCTL0 = OUTMOD0 + CCIE;                   // TXD = mark = idle
  while ( CCTL0 & CCIE );                   // Wait for TX completion
}

// Function Readies UART to Receive Character into RXTXData Buffer
// Sync capture not possible as DCO=TACLK=SMCLK can be off !!
void RX_Ready (void)
{
  BitCnt = 0x8;                             // Load Bit counter
  CCTL0 = CM1 + CCIS0 + OUTMOD0 + CAP + CCIE; // Neg Edge, Cap
}

// Timer A0 interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
  CCR0 += Bitime;                           // Add Offset to CCR0

// RX
  if (CCTL0 & CCIS0)                        // RX on CCI0B?
  {
    if( CCTL0 & CAP )                       // Capture mode = start bit edge
    {
    CCTL0 &= ~ CAP;                         // Switch from capture to compare mode
    CCR0 += Bitime_5;
    _BIC_SR_IRQ(SCG1 + SCG0);               // DCO remains on after reti
    }
    else
    {
    RXTXData = RXTXData >> 1;
      if (CCTL0 & SCCI)                     // Get bit waiting in receive latch
      RXTXData |= 0x80;
      BitCnt --;                            // All bits RXed?
      if ( BitCnt == 0)
//>>>>>>>>>> Decode of Received Byte Here <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
      {
      CCTL0 &= ~ CCIE;                      // All bits RXed, disable interrupt
      _BIC_SR_IRQ(LPM3_bits);               // Clear LPM3 bits from 0(SR)
      }
//>>>>>>>>>> Decode of Received Byte Here <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    }
  }
// TX
  else
  {
    if ( BitCnt == 0)
    CCTL0 &= ~ CCIE;                        // All bits TXed, disable interrupt
    else
    {
      CCTL0 |=  OUTMOD2;                    // TX Space
      if (RXTXData & 0x01)
      CCTL0 &= ~ OUTMOD2;                   // TX Mark
      RXTXData = RXTXData >> 1;
      BitCnt --;
    }
  }
}
