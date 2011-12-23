//******************************************************************************
//  MSP430x11x1 Demo - Timer_A, Ultra-Low Pwr UART 9600 Echo, 32kHz ACLK
//
//  Description: This program demonstrates a half-duplex 9600-baud UART using
//  Timer_A3 and a 32kHz crystal.  The program will wait in LPM3, echoing back
//  a received character using 8N1 protocol.  The Set_DCO function will
//  calibrate the DCOCLK to ~2MHz which is used as the Timer_A clock.
//  ACLK = LFXT1/8 = 32768/8, MCLK = SMCLK = target DCO
//  //* External watch crystal installed on XIN XOUT is required for ACLK *//	
//
//                MSP430F1121
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//           |   CCI0A/TXD/P1.1|-------->
//           |                 | 9600 8N1
//           |   CCI0B/RXD/P2.2|<--------
//
#define RXD       0x04                      // RXD on P2.2
#define TXD       0x02                      // TXD on P1.1

//   Conditions for 9600 Baud SW UART, DCO ~ 2MHz

#define Bitime_5  104                       // ~ 0.5 bit length
#define Bitime    208                       // ~ 9615 baud
#define DELTA     488                       // Target DCO = DELTA*(4096) ~2MHz

unsigned int RXTXData;
unsigned char BitCnt;

void TX_Byte (void);
void RX_Ready (void);
void Set_DCO (void);

//  M. Buccini
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//*****************************************************************************

#include <msp430x11x1.h>


void main (void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

  BCSCTL1 |= DIVA_3;                        // ACLK = LFXT1CLK/8
  Set_DCO();                                // Set DCO

  CCTL0 = OUT;                              // TXD Idle as Mark
  TACTL = TASSEL_2 + MC_2;                  // SMCLK, continuous mode
  P1SEL = TXD;                              // P1.1/TA0 for TXD function
  P1DIR = TXD;                              // TXD output on P1
  P2SEL = RXD;                              // P2.2/TA0 as RXD input

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

//------------------------------------------------------------------------------
void Set_DCO (void)                         // Set DCO to selected frequency
//------------------------------------------------------------------------------
{
  unsigned int Compare, Oldcapture = 0;

  CCTL2 = CM_1 + CCIS_1 + CAP;              // CAP, ACLK
  TACTL = TASSEL_2 + MC_2 + TACLR;          // SMCLK, cont-mode, clear

  while (1)
  {
    while (!(CCIFG & CCTL2));               // Wait until capture occured
    CCTL2 &= ~CCIFG;                        // Capture occured, clear flag
    Compare = CCR2;                         // Get current captured SMCLK
    Compare = Compare - Oldcapture;         // SMCLK difference
    Oldcapture = CCR2;                      // Save current captured SMCLK
    if (DELTA == Compare) break;            // If equal, leave "while(1)"

    else if (DELTA < Compare)
    {
      DCOCTL--;
      if (DCOCTL == 0xFF)                   // DCO is too fast, slow it down
      {
        if (!(BCSCTL1 == (XT2OFF + DIVA_3)))
        BCSCTL1--;                          // Did DCO role under?, Sel lower RSEL
      }
    }
    else
    {
      DCOCTL++;                             // DCO is too slow, speed it down
      if (DCOCTL == 0x00)
      {
        if (!(BCSCTL1 == (XT2OFF + DIVA_3 + 0x07)))
        BCSCTL1++;                          // Did DCO role over? Sel higher RSEL
      }
    }
  }

  CCTL2 = 0;                                // Stop CCR2
  TACTL = 0;                                // Stop Timer_A
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
    _BIC_SR_IRQ(SCG1 + SCG0);               // DCO reamins on after reti
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
