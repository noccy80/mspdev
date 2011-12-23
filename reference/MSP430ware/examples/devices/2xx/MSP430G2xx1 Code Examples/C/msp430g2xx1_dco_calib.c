//******************************************************************************
//  MSP430G2xx1 Demo - Basic Clock, Output Buffered clocks with preloaded DCO
//                     calibration constants for BCSCTL1 and DCOCTL.
//  
//  Description: Buffer ACLK on P1.0, default SMCLK(DCO) on P1.4 and MCLK/10 on
//  P1.1. DCO is software selectable to 1, 8, 12, or 16Mhz using calibration
//  contstants in INFOA.
//
//  ACLK = LFXT1 = 32768, MCLK = SMCLK = Selectable at 1, 8, 12 or 16Mhz
//  //* External watch crystal installed on XIN XOUT is required for ACLK *//	
//	//* By default, the MSP430 uses XT1 to source ACLK; P2.6/7 configured 
//  //* automatically.
//               MSP430G2xx1
//             -----------------
//         /|\|         P2.6/XIN|-
//          | |                 | 32kHz
//          --|RST     P2.7/XOUT|-
//            |                 |
//            |       P1.4/SMCLK|-->SMCLK = Default DCO
//            |             P1.1|-->MCLK/10 = DCO/10
//            |        P1.0/ACLK|-->ACLK = 32kHz
// 
//  D. Dang
//  Texas Instruments Inc.
//  October 2010
//  Built with IAR Embedded Workbench Version: 3.42A
//******************************************************************************

#include  <msp430g2231.h>

void main(void)
{
  WDTCTL = WDTPW +WDTHOLD;                  // Stop Watchdog Timer
  if (CALBC1_1MHZ ==0xFF || CALDCO_1MHZ == 0xFF)                                     
  {  
    while(1);                               // If calibration constants erased
                                            // do not load, trap CPU!!
  } 
 //1Mhz
  BCSCTL1 = CALBC1_1MHZ;                    // Set range
  DCOCTL = CALDCO_1MHZ;                     // Set DCO step + modulation */

/* //8Mhz
  BCSCTL1 = CALBC1_8MHZ;                    // Set range
  DCOCTL = CALDCO_8MHZ;                     // Set DCO step + modulation */

/* //12Mhz
  BCSCTL1 = CALBC1_12MHZ;                   // Set range
  DCOCTL = CALDCO_12MHZ;                    // Set DCO step + modulation*/

/* //16Mhz
  BCSCTL1 = CALBC1_16MHZ;                   // Set range
  DCOCTL = CALDCO_16MHZ;                    // Set DCO step + modulation*/

  P1DIR |= 0x13;                            // P1.0,1 and P1.4 outputs
  P1SEL |= 0x11;                            // P1.0,4 ACLK, SMCLK output

  while(1)
  {
    P1OUT |= 0x02;    	                    // P1.1 = 1
    P1OUT &= ~0x02;                         // P1.1 = 0
  }
}

