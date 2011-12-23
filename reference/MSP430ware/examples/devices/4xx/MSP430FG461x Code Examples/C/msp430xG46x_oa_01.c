//*****************************************************************************
//  MSP430xG46x Demo - OA0, Comparator Mode
//
//  Description: Configure OA0 for Comparator mode. In this example, OA0 is
//  configured as a comparator. The comparator reference is connected to
//  the "-" input and comes from the integrated R ladder. The reference level
//  is selected with the OAFBR bits. The "+" terminal is connected to OA0I0.
//  ACLK = 32.768kHz, MCLK = SMCLK = default DCO
//
//                MSP430xG461x
//             -------------------
//         /|\|                XIN|-
//          | |                   |
//          --|RST            XOUT|-
//            |                   |
//     "+" -->|P6.0/OA0I0         |
//            |                   |
//            |          P6.1/OA0O|--> OA0 Output
//            |                   |    Output goes high when
//            |                   |    Input > (0.25 * AVcc)
//
// K. Quiring / A. Dannenberg
// Texas Instruments Inc.
// June 2007
// Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//*****************************************************************************
#include  <msp430xG46x.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  OA0CTL0 = OAPM_1 + OAADC1;                // Select inputs, power mode
  OA0CTL1 = OAFC_3 + OAFBR_1 + OARRIP;      // Comparator mode,
                                            // "-" connected to AVcc * 4/16,
                                            // limited range (see datasheet)
  __bis_SR_register(LPM3_bits + GIE);       // LPM3
}
