//******************************************************************************
//  MSP430F14x Demo - Timer_A, Ultra-Low Pwr UART 2400 Echo, 32kHz ACLK
//
//  Description: Use Timer_A CCR1 hardware output modes and CCR0 SCCI data latch
//  to implement UART function @ 2400 baud. Software does not directly read and
//  write to RX and TX pins, instead proper use of output modes and SCCI data
//  latch are demonstrated. Use of these hardware features eliminates ISR
//  latency effects as hardware insures that output and input bit latching and
//  timing are perfectly synchronised with Timer_A regardless of other
//  software activity. In the Mainloop the UART function readies the UART to
//  receive one character and waits in LPM3 with all activity interrupt driven.
//  After a character has been received, the UART receive function forces exit
//  from LPM3 in the Mainloop which echo's back the received character.
//  ACLK = TACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO
//  //* An external watch crystal is required on XIN XOUT for ACLK *//	
//
//               MSP430F14x
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//           |         TXD/P2.3|-------->
//           |                 | 2400 8N1
//           |   CCI0B/RXD/P2.2|<--------
//

#define RXD       0x04                      // RXD on P2.2

#define TXD       0x08                      // TXD on P2.3
//   Conditions for 2400 Baud SW UART, ACLK = 32768

#define Bitime_5  0x06                      // ~ 0.5 bit length + small adjustment
#define Bitime    0x0E                      // 427us bit length ~ 2341 baud

unsigned int RXTXData;
unsigned char BitCnt;

void TX_Byte (void);
void RX_Ready (void);

//  R. B. Elliott / H. Grewal
//  Texas Instruments Inc.
//  November 2007
//  Built with IAR Embedded Workbench Version: 3.42A
//******************************************************************************

#include  <msp430x14x.h>


void main (void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  CCTL1 = OUT;                              // TXD Idle as Mark
  TACTL = TASSEL_1 + MC_2;                  // ACLK, continuous mode
  P2SEL = TXD + RXD;                        // *******

  P2DIR = TXD;                              //

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
  while (CCR1 != TAR)                       // Prevent async capture
    CCR1 = TAR;                             // Current state of TA counter
  CCR1 += Bitime;                           // Some time till first bit
  RXTXData |= 0x100;                        // Add mark stop bit to RXTXData
  RXTXData = RXTXData << 1;                 // Add space start bit
  CCTL1 =  CCIS0 + OUTMOD0 + CCIE;          // TXD = mark = idle
  while ( CCTL1 & CCIE );                   // Wait for TX completion
}


// Function Readies UART to Receive Character into RXTXData Buffer
void RX_Ready (void)
{
  BitCnt = 0x8;                             // Load Bit counter
  CCTL0 = SCS + OUTMOD0 + CM1 + CAP + CCIE + CCIS_1;   // Sync, Neg Edge, Cap
}

// Timer A0 interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
  CCR0 += Bitime;                           // Add Offset to CCR0

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
//>>>>>>>>>> Decode of Received Byte Here <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
      {
      CCTL0 &= ~ CCIE;                      // All bits RXed, disable interrupt
      _BIC_SR_IRQ(LPM3_bits);               // Clear LPM3 bits from 0(SR)
      }
//>>>>>>>>>> Decode of Received Byte Here <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    }
  }
}

// Timer_A3 Interrupt Vector (TAIV) handler
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A1(void)
{
  switch( TAIV )
  {
    case  2:  
      _NOP();
        CCR1 += Bitime;                     // Add Offset to CCR0

// TX
  if (CCTL1 & CCIS0)                        // TX on CCI0B?
  {
    if ( BitCnt == 0){
    CCTL1 &= ~ CCIE;                        // All bits TXed, disable interrupt
    }
    else
    {
      CCTL1 |=  OUTMOD2;                    // TX Space
      if (RXTXData & 0x01)
      CCTL1 &= ~ OUTMOD2;                   // TX Mark
      RXTXData = RXTXData >> 1;
      BitCnt --;
    }
  }
      break;                                // CCR1 not used
    case  4:  break;                        // CCR2 not used
    case 10:  P1OUT ^= 0x01;                // overflow
              break;
  }
}
