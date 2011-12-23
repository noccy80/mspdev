//******************************************************************************
//  MSP430x11x1 Demo - Timer_A, UART 9600 Echo, HF XTAL ACLK
//
//  Description: Use Timer_A CCR0 hardware output modes and SCCI data latch
//  to implement UART function @ 9600 baud. Software does not directly read and
//  write to RX and TX pins, instead proper use of output modes and SCCI data
//  latch are demonstrated. Use of these hardware features eliminates ISR
//  latency effects as hardware insures that output and input bit latching and
//  timing are perfectly synchronised with Timer_A regardless of other
//  software activity. In the Mainloop the UART function readies the UART to
//  receive one character and waits in LPM0 with all activity interrupt driven.
//  After a character has been received, the UART receive function forces exit
//  from LPM0 in the Mainloop which echo's back the received character.
//  ACLK = MCLK = TACLK = HF XTAL = 3.579545MHz
//  //* An external 3.579545Hz XTAL on XIN XOUT is required for ACLK *//	
//
//                MSP430F1121
//            -----------------
//        /|\|              XIN|-
//         | |                 | 3.58Mhz
//         --|RST          XOUT|-
//           |                 |
//           |   CCI0A/TXD/P1.1|-------->
//           |                 | 9600 8N1
//           |   CCI0B/RXD/P2.2|<--------
//
#define RXD       0x04                      // RXD on P2.2
#define TXD       0x02                      // TXD on P1.1

//  Conditions for 9600 Baud HW/SW UART, ACLK = 3.579545MHz

#define Bitime_5  0x0BA                     // ~ 0.5 bit length
#define Bitime    0x175                     // 104 us ~ 9596 baud

unsigned int RXTXData;
unsigned char BitCnt;

void TX_Byte (void);
void RX_Ready (void);

//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//*****************************************************************************

#include <msp430x11x1.h>


void main (void)
{
  volatile unsigned int i;
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

  BCSCTL1 |= XTS;                           // ACLK = LFXT1 = HF XTAL

  do
  {
  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
  for (i = 0xFF; i > 0; i--);               // Time for flag to set
  }
  while ( IFG1 & OFIFG );                   // OSCFault flag still set?

  BCSCTL2 |= SELM_3;                        // MCLK = LFXT1 (safe)

  CCTL0 = OUT;                              // TXD Idle as Mark
  TACTL = TASSEL_1 + MC_2;                  // ACLK, continuous mode
  P1SEL = TXD;                              // P1.1/TA0 for TXD function
  P1DIR = TXD;                              // TXD output on P1
  P2SEL = RXD;                              // P2.2/TA0 as RXD input

// Mainloop
  for (;;)
  {
  RX_Ready();                               // UART ready to RX one Byte
  _BIS_SR(CPUOFF + GIE);                    // Enter LPM0 w/ interr until char RXed
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
void RX_Ready (void)
{
  BitCnt = 0x8;                             // Load Bit counter
  CCTL0 = SCS + CCIS0 + OUTMOD0 + CM1 + CAP + CCIE;   // Sync, Neg Edge, Capture
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
      _BIC_SR_IRQ(CPUOFF);                  // Clear LPM0 bits from 0(SR)
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
