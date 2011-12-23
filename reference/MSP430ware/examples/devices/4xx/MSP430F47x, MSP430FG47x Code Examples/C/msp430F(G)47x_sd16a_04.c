//*****************************************************************************
//   MSP430F(G)47x Demo - SD16_A, Single Conversion on Single Channel Polling IFG
//
//  Description: This program uses the SD16_A module to perform a single
//  conversion on a single channel. The SD16_A interrupt flag is polled
//  to determine when a conversion has completed. Test by applying a voltage
//  to CH0 (A0+, A0-) and setting a breakpoint at the line indicated
//  below. Run program until it reaches the breakpoint, then use the
//  debugger's register window to view the conversion results. The conversion
//  result for CH0 is stored in results.
//  ACLK = LFXT1 = 32768 Hz, MCLK = SMCLK = DCO = 32 x ACLK = 1048576 Hz
//  //* An external watch crystal on XIN XOUT is required for ACLK     *//
//  //* Minimum Vcc is required for SD16_A module - see datasheet        *//
//  //* 100nF cap btw Vref and AVss is recommended when using 1.2V ref *//
//
//                MSP430F(G)47x
//            -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//    Vin+ -->|A0+              |
//    Vin- -->|A0-              |
//            |                 |
//            |            VREF |---+
//            |                 |   |
//            |                 |  -+- 100nF
//            |                 |  -+-
//            |                 |   |
//            |            AVss |---+
//            |                 |
//
//  M.Seamen/ P. Thanigai
//  Texas Instruments Inc.
//  September 2008
//  Built with IAR Embedded Workbench V4.11A and CCE V3.2
//*****************************************************************************
#include "msp430xG47x.h"

unsigned int results;

void main(void)
{
  volatile unsigned int i;                  // Use volatile to prevent removal
                                            // by compiler optimization

  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P6SEL |= BIT0+BIT1;			    // Config SD16 inputs 
  
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps
  for (i = 0; i < 10000; i++);              // Delay for 32 kHz crystal to
                                            // stabilize

  SD16CTL = SD16REFON+SD16SSEL0;            // 1.2V ref, SMCLK
  SD16CCTL0 |= SD16SNGL;                    // Single conv
  for (i = 0; i < 0x3600; i++);             // Delay for 1.2V ref startup

  while (1)
  {
    SD16CCTL0 |= SD16SC;                    // Set bit to start conversion
    while ((SD16CCTL0 & SD16IFG)==0);       // Poll interrupt flag
    results = SD16MEM0;                     // Save CH0 results (clears IFG)
    _NOP();                                 // SET BREAKPOINT HERE
  }
}
