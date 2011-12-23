//******************************************************************************
//  MSP430x26x Demo - Basic Clock, Output Buffered SMCLK, ACLK and MCLK/10
//
//  Description: Buffer ACLK on P5.6, SMCLK(DCO) on P5.5, MCLK on P5.4 and 
//  MCLK/10 on P5.3.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = CALxxx_8MHZ = 8MHz
//  //* External watch crystal on XIN XOUT is required for ACLK *//
//
//            MSP430F261x/241x
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P5.6|-->ACLK = 32kHz
//            |             P5.5|-->SMCLK = 8MHz
//            |             P5.4|-->MCLK = DCO
//            |             P5.3|-->MCLK/10
//
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include "msp430x26x.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop Watchdog Timer
  if (CALBC1_8MHZ ==0xFF || CALDCO_8MHZ == 0xFF)                                     
  {  
    while(1);                               // If calibration constants erased
                                            // do not load, trap CPU!!
  }  
  BCSCTL1 = CALBC1_8MHZ;                    // Set DCO to 8MHz
  DCOCTL = CALDCO_8MHZ;
  P5DIR |= 0x78;                            // P5.6,5,4,3 outputs
  P5SEL |= 0x70;                            // P5.6,5,4 options

  while (1)                                 // 10 MCLK cycle loop
  {
    P5OUT |= 0x08;                          // P5.3 = 1
    P5OUT &= ~0x08;                         // P5.3 = 0
  }
}
