//******************************************************************************
//  MSP430x21x1 Demo - Timer_A UART 9600, 1MHz DCO SMCLK
//
//  Description: This program demonstrates a full-duplex 9600-baud UART using
//  Timer_A3 and the DCO. A character is echoed on the Hyperterminal of a
//  a PC. The DCO frequency settings are stored in INFOA flash segment.
//  ACLK = n/a, MCLK = SMCLK = saved DCO 1Mhz
//  //* External watch crystal installed on XIN XOUT is required for ACLK *//
//
//                MSP430F21x1
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//           |             P1.3|--------> Power for MAX3221
//           |   CCI0A/TXD/P1.1|-------->
//           |                 | 9600 8N1
//           |   CCI0B/RXD/P2.2|<--------
//*****************************************************************************
/*
 * ======== Standard MSP430 includes ========
 */
#include <msp430.h>

/*
 * ======== Grace related includes ========
 */
#include <ti/mcu/msp430/csl/CSL.h>

/*
 *  ======== main ========
 */

#define RXD   0x04                          // RXD on P2.2
#define TXD   0x02                          // TXD on P1.1

//   Conditions for 9600 Baud SW UART, DCO = 1MHz
#define Bitime_5  52                        // ~ 0.5 bit length
#define Bitime    104                       // ~ 9615 baud

unsigned int RXTXData;
unsigned char BitCnt;

void TX_Byte(void);
void RX_Ready(void);

void main(int argc, char *argv[])
{
    CSL_init();

    TACCTL0 &= ~CCIE;                           // Explicitly disable GRACE enabled
                                                // interrupt for program specific need

    while(1)
    {
      RX_Ready();                               // UART ready to RX one Byte
      _BIS_SR(LPM4_bits + GIE);                 // Enter LPM4 w/ interr until char RXed
      TX_Byte();                                // TX Back RXed Byte Received
    }
}
// Function Transmits Character from RXTXData Buffer
void TX_Byte (void)
{
  BitCnt = 0xA;                                 // Load Bit counter, 8data + ST/SP
  CCR0 = TAR;                                   // Current state of TA counter
  CCR0 += Bitime;                               // Some time till first bit
  RXTXData |= 0x100;                            // Add mark stop bit to RXTXData
  RXTXData = RXTXData << 1;                     // Add space start bit
  CCTL0 = OUTMOD0 + CCIE;                       // TXD = mark = idle
  while ( CCTL0 & CCIE );                       // Wait for TX completion
}

// Function Readies UART to Receive Character into RXTXData Buffer
// Sync capture not possible as DCO=TACLK=SMCLK can be off !!
void RX_Ready (void)
{
  BitCnt = 0x8;                                 // Load Bit counter
  CCTL0 = CM1 + CCIS0 + OUTMOD0 + CAP + CCIE;   // Neg Edge, Cap
}

unsigned short Timer_A(void)
{
    CCR0 += Bitime;                             // Add Offset to CCR0

    // RX
    if (CCTL0 & CCIS0)                          // RX on CCI0B?
    {
      if( CCTL0 & CAP )                         // Capture mode = start bit edge
      {
        CCTL0 &= ~ CAP;                         // Switch from capture to compare mode
        CCR0 += Bitime_5;
        return (SCG1 + SCG0);                   // DCO reamins on after reti
      }
      else
      {
        RXTXData = RXTXData >> 1;
        if (CCTL0 & SCCI)                       // Get bit waiting in receive latch
          RXTXData |= 0x80;
        BitCnt --;                              // All bits RXed?
        if ( BitCnt == 0)
        //>>>>>>>>>> Decode of Received Byte Here <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
        {
          CCTL0 &= ~ CCIE;                      // All bits RXed, disable interrupt
          return LPM4_bits;                     // Clear LPM4 bits from 0(SR)
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
        CCTL0 |=  OUTMOD2;                      // TX Space
        if (RXTXData & 0x01)
          CCTL0 &= ~ OUTMOD2;                   // TX Mark
        RXTXData = RXTXData >> 1;
        BitCnt --;
      }
    }
    return 0;
}
