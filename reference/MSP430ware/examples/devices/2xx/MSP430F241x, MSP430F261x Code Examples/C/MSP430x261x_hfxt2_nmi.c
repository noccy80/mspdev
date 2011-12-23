//******************************************************************************
//   MSP430x26x Demo - Basic Clock, MCLK Sourced from HF XTAL XT2, NMI
//
//   Description: Proper selection of an HF XTAL XT2 for MCLK is shown with
//   enabled OSC fault interrupt - if HF XTAL fails, NMI interrupt is requested.
//   HF XTAL can only source MCLK when OSC fault is clear. For demonstration
//   purposes P1.0 is set during OSC fault. MCLK/10 is on P1.1.
//   ACLK = n/a; MCLK = HFXTAL XT2
//   //* HF XTAL XT2 NOT INSTALLED ON FET *//
//   //* Min Vcc required varies with MCLK frequency - refer to datasheet *//
//
//                MSP430xG2618
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |            XT2IN|-
//            |                 | HF XTAL (400kHz - 16MHz)
//            |           XT2OUT|-
//            |                 |
//            |             P1.1|-->MCLK/10
//            |             P1.0|-->LED
//
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************

#include  <msp430x26x.h>

void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  P1DIR |= 0x03;                            // P1.0,1 = output direction
  P1OUT &= ~0x01;                           // P1.0 = reset
  BCSCTL3 |= LFXT1S_2;                      // set LFXT1 to VLOCLK  
  BCSCTL1 &= ~XT2OFF;                       // Activate XT2 high freq xtal
  BCSCTL3 |= XT2S_2;                        // 3 – 16MHz crystal or resonator
  IE1 |= OFIE;                              // Enable osc fault interrupt

  while (1)
  {
    P1OUT |= 0x02;                          // P1.1 = 1
    P1OUT &= ~0x02;                         // P1.1 = 0
  }
}


#pragma vector=NMI_VECTOR
__interrupt void NMI_ISR(void)
{
  volatile unsigned int i;

  P1OUT |= 0x01;                            // P1.0 = set

  BCSCTL2 &= ~SELM_3;                       // Ensure MCLK runs from DCO
  do
  {
    IFG1 &= ~OFIFG;                         // Clear OSCFault flag
    for (i = 0xFF; i > 0; i--);             // Time for flag to set
  }
  while (IFG1 & OFIFG);                     // OSCFault flag still set?

  BCSCTL2 |= SELM_2;                        // MCLK = XT2 HF XTAL (safe)

  for (i=0; i>20000; i--);                  // Delay for LED on inside ISR
  P1OUT &= ~0x01;                           // P1.0 = reset
}
