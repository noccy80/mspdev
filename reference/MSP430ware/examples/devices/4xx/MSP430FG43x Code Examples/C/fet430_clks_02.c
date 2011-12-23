//*****************************************************************************
//  MSP-FET430P430 Demo - FLL+, Output 32kHz XTAL + HF XTAL + Internal DCO
//
//  Description: This program demonstrates using an external 32kHz crystal to
//  supply the internal ACLK, and using a high speed crystal or resonator to
//  supply SMCLK. The MLCK for the CPU is supplied by the DCO. The 32kHz
//  crystal connects to pins Xin and Xout. The high frequency crystal or
//  resonator connects to pins XT2in and XT2out. The DCO clock is generated
//  internally and calibrated by the FLL+ from the 32kHz crystal. The
//  resulting ACLK is brought out pin P1.5, SMCLK is brought out on P1.4,
//  and MCLK is brought out on pin P1.1.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//  //* External matching capacitors must be added for the high *//
//  //* speed crystal or resonator as required.                 *//
//
//                MSP430FG439
//             -----------------
//        /|\ |              XIN|-
//         |  |                 | 32kHz
//         ---|RST          XOUT|-
//            |                 |
//            |                 |
//            |            XT2IN|-
//            |                 | HF XTAL or Resonator (add capacitors)
//            |           XT2OUT|-
//            |                 |
//            |                 |
//            |        P1.5/ACLK|--> ACLK = 32768 Hz
//            |                 |
//            |       P1.4/SMCLK|--> SMCLK = High Freq XTAL or Resonator
//            |                 |
//            |        P1.1/MCLK|--> MCLK = 1048576 Hz (Default DCO)
//            |                 |
//            |                 |
//
//  M. Morales
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//*****************************************************************************
#include  <msp430xG43x.h>

void main(void)
{
  volatile unsigned int i;                  // Use volatile to prevent removal
                                            // by compiler optimization

  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps
  for (i = 0; i < 10000; i++);              // Delay for 32 kHz crystal to
                                            // stabilize
  do
  {
    IFG1 &= ~OFIFG;                         // Clear osc fault flag
    for (i = 0; i < 1000; i++);             // Delay for osc to stabilize
  } while(IFG1 & OFIFG);                    // Check to see if osc flag is set

  FLL_CTL1 = SELS;                          // XT2 on, SMCLK = XT2CLK

  P1DIR = 0x32;                             // Set P1.5,4,1 as outputs
  P1SEL = 0x32;                             // Select P1.5,4,1 as clk option

  while(1);                                 // Loop in place
}
