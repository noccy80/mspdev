//******************************************************************************
//  MSP430x21x1 Demo - Timer_A UART 19200 TX, 1MHz DCO
//
//  Description: This program demonstrates a half-duplex 19200-baud UART using
//  Timer_A3 and a the DCO.  The program will wait in LPM0 sending the
//  string 'Hello World' with 112ms interval between characters as timed by a
//  WDT interrupt. The Set_DCO subroutine will calibrate the DCOCLK
//  to ~1Mhz.
//  ACLK = LFXT1/8 = 32768/8, MCLK = SMCLK = target DCO
//  //* External watch crystal installed on XIN XOUT is required for ACLK *//	
//
//               MSP430F21x1
//            -----------------
//        /|\|              XIN|-
//         | |                 | 32kHz
//         --|RST          XOUT|-
//           |                 |
//           |             P1.3|--------> Power for MAX3221
//           |   CCI0A/TXD/P1.1|--------> "Hello World"
//           |                 | 19200 8N1
//           |   CCI0B/RXD/P2.2|<--------
//
//   M.Buccini / A. Dannenberg
//   Texas Instruments, Inc
//   July 2005
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.30A
//*****************************************************************************

#include <msp430x21x1.h>

#define RXD   0x04                          // RXD on P2.2
#define TXD   0x02                          // TXD on P1.1

//   Conditions for 19200 Baud SW UART, DCO = 1048576MHz
#define Bitime_5  27                        // ~ 0.5 bit length
#define Bitime    55                        // ~ 19200 baud
#define DELTA     256                       // Target DCO = DELTA*(4096)

unsigned int RXTXData;
unsigned char BitCnt;
unsigned char i = 0;

void TX_Byte(void);
void Set_DCO(void);

static const char string1[] = { "Hello World\r\n" };

void main (void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

  BCSCTL1 |= DIVA_3;                        // ACLK = LFXT1CLK/8
  TACTL = TASSEL_2 + MC_2 + TACLR;          // SMCLK, cont-mode, clear
  Set_DCO();                                // Set DCO

  WDTCTL = WDT_MDLY_32;                     // WDT 16ms*8, ACLK, interval timer
  IE1 |= WDTIE;                             // Enable WDT interrupt

  CCTL0 = OUT;                              // TXD Idle as Mark
  P1SEL = TXD;                              // P1.1/TA0 for TXD function
  P1DIR = TXD;                              // TXD output on P1
  P2SEL = RXD;                              // P2.2/TA0 as RXD input

  P1DIR |= 0x08;                            // Power MAX3221
  P1OUT |= 0x08;                            //

// Mainloop
  for (;;)
  {
    _BIS_SR(LPM0_bits + GIE);               // Enter LPM3
    RXTXData = string1[i];
    TX_Byte();                              // TX
    i++;
    if (i > sizeof string1-1) i = 0;
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

// Set DCO to selected frequency
void Set_DCO(void)
{
  unsigned int Compare, Oldcapture = 0;

  BCSCTL1 |= DIVA_3;                        // ACLK= LFXT1CLK/8
  CCTL2 = CM_1 + CCIS_1 + CAP;              // CAP, ACLK

  while (1)
  {
    while (!(CCIFG & CCTL2));               // Wait until capture occured
    CCTL2 &= ~CCIFG;                        // Capture occured, clear flag
    Compare = CCR2;                         // Get current captured SMCLK
    Compare = Compare - Oldcapture;         // SMCLK difference
    Oldcapture = CCR2;                      // Save current captured SMCLK

    if (DELTA == Compare) break;            // If equal, leave "while(1)"
    else if (DELTA < Compare)               // DCO is too fast, slow it down
    {
      DCOCTL--;
      if (DCOCTL == 0xFF)
      {
        if (!(BCSCTL1 == (XT2OFF + DIVA_3)))
        BCSCTL1--;                          // Did DCO roll under?, Sel lower RSEL
      }
    }
    else
    {
      DCOCTL++;
      if (DCOCTL == 0x00)
        {
          if (!(BCSCTL1 == (XT2OFF + DIVA_3 + 0x0F)))
          BCSCTL1++;                        // Did DCO roll over? Sel higher RSEL
        }
    }
  }
  CCTL2 = 0;                                // Stop CCR2
}

// Timer A0 interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
  CCR0 += Bitime;                           // Add Offset to CCR0

// TX
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

#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer (void)
{
    _BIC_SR_IRQ(LPM0_bits);                 // Clear LPM3 bits from 0(SR)
}
