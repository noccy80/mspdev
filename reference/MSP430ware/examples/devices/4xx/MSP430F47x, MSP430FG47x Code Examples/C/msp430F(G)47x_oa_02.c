//*****************************************************************************
//  MSP430F(G)47x Demo - OA0, Comparator in General-Purpose Mode
//
//  Description: Use OA0 as a comparator in general-purpose mode. In this
//  example, OA0 is configured for general-purpose mode, but used as a
//  comparator. The reference is supplied by DAC12_0 on the "-" input.
//  The "+" terminal is connected to OA0I0.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430F(G)47x
//             -------------------
//         /|\|                XIN|-
//          | |                   |
//          --|RST            XOUT|-
//            |                   |
//     "+" -->|P6.0/OA0I0         |
//            |                   |
//            |          P6.1/OA0O|--> OA0 Output
//            |                   |    Output goes high when
//            |                   |    Input > .6V
//
//  M.Seamen/ P. Thanigai
//  Texas Instruments Inc.
//  September 2008
//  Built with IAR Embedded Workbench V4.11A and CCE V3.2
//*****************************************************************************
#include "msp430xG47x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
											//AVcc reference for DAC12
  DAC12_0CTL = DAC12IR + DAC12AMP_2 + DAC12ENC; 
  DAC12_0DAT = 0x7FF;                       // Reference level = 1.5V
  OA0CTL0 = OAN_3+ OAPM_1;                  // Select inputs, power mode

  LPM3;                                     // LPM3
}
