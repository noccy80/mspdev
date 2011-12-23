//******************************************************************************
//  MSP-FET430P410 Demo - Timer_A, UART 115200 Echo, DCO SMCLK
//
//  Description: Use Timer_A CCR0 hardware output modes and SCCI data latch to
//  implement UART function @ 115k baud. Software does not directly read and
//  write to RX and TX pins, instead proper use of output modes and SCCI data
//  latch are demonstrated. Using these hardware features eliminates ISR
//  latency effects as hardware ensures that input and output bit latching and
//  timing are perfectly synchronised with Timer_A regardless of other
//  software activity. In the Mainloop the UART function readies the UART to
//  receive one character and waits in LPM0 with all activity interrupt driven.
//  After a character has been received, the UART receive function forces exit
//  from LPM0 in the Mainloop which echo's back the received character.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//                MSP430F413
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//           |    P1.0/CCI0A/TX|----------->
//           |                 | 115200 8N1
//           |    P1.1/CCI0B/RX|<-----------
//
//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//*****************************************************************************
#include  <msp430x41x.h>

#define RXD   0x02                          // RXD on P1.1
#define TXD   0x01                          // TXD on P1.0

//  Conditions for 115200 Baud SW UART, SMCLK = 8MHz

#define Bitime_5  0x024       // ~ 0.5 bit length + small adjustment
#define Bitime    0x045       // 8.6 us bit length ~ 115942 baud

unsigned int RXTXData;
unsigned char BitCnt;

void TX_Byte(void);
void RX_Ready(void);


void main (void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  FLL_CTL0 |= DCOPLUS + XCAP14PF;           // DCO+, Configure load caps
  SCFI0 |= FN_4;                            // x2 DCO frequency, 8MHz nominal
  SCFQCTL = 121;                            // (121+1) x 32768 x 2 = 7.99 MHz
  CCTL0 = OUT;                              // TXD Idle as Mark
  TACTL = TASSEL_2 + MC_2;                  // SMCLK, continuous mode

  P1SEL = TXD + RXD;                        // P1.0/1 TA0 for TXD/RXD function
  P1DIR = TXD;                              // TXD output on P1

  // Mainloop
  for (;;)
  {
    RX_Ready();                             // UART ready to RX one Byte
    _BIS_SR(CPUOFF + GIE);                  // Enter LPM0 Until character RXed
    TX_Byte();                              // TX Back RXed Byte Received
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
  CCTL0 = SCS + CCIS0 + OUTMOD0 + CM1 + CAP + CCIE;  // Sync, Neg Edge, Capture
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
      CCTL0 &= ~ CAP;                       // Capture to compare mode
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
        CCTL0 &= ~ CCIE;                    // All bits RXed, disable interrupt
        _BIC_SR_IRQ(CPUOFF);                // Clear LPM0 bits from 0(SR)
      }
//>>>>>>>>>> Decode of Received Byte Here <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    }
  }
  // TX
  else
  {
    if ( BitCnt == 0)
      CCTL0 &= ~ CCIE;                      // All bits TXed, disable interrupt
    else
    {
      CCTL0 |=  OUTMOD2;                    // TX Space
      if (RXTXData & 0x01)
        CCTL0 &= ~ OUTMOD2;                 // TX Mark
      RXTXData = RXTXData >> 1;
      BitCnt --;
    }
  }
}
