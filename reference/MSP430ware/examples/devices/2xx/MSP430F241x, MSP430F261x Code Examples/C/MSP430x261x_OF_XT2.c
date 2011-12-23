//******************************************************************************
//   MSP430x26x Demo - XT2 Oscillator Fault Detection
//
//   Description: System runs normally in LPM3 with Timer A clocked by
//   ACLK.  TimerA0 interrupt causes an exit from LPM3, and toggles P1.0.
//   If an XT2 oscillator fault occurs, NMI is requested, pausing execution and
//   flashing LED quickly until fault is resolved.  Assumed only XT2 as NMI
//   source - code does not check for other NMI sources. MCLK is buffered on 
//   P5.4. If fault occurs for crystal osc sourcing the MCLK, MCLK is 
//   automatically switched to DCO for its clock source
//   MCLK = XT2 = 8MHz normally, within ISRs MCLK = DCO freq ~1025kHz
//   //* An external 8MHx crystal is required between XT2 and XT2OUT , and
//   an external 32kHz crystal is required between XIN and XOUT.  *//	
//
//             MSP430F261x/241x
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32KHz
//          --|RST          XOUT|-
//            |                 |
//            |            XT2IN|-
//            |                 | 8MHz
//            |           XT2OUT|-
//            |                 |
//            |             P1.0|-->LED
//            |        P5.4/MCLK|-->MCLK = XT2 HFXTAL
//
//  B. Nisarga
//  Texas Instruments Inc.
//  September 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include  <msp430x26x.h>

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  BCSCTL1 &= ~XT2OFF;                       // Activate XT2 high freq xtal
  BCSCTL3 |= XT2S_2;                        // 3 – 16MHz crystal or resonator

  // Wait for xtal to stabilize
  do
  {
  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
  for (i = 0x47FF; i > 0; i--);             // Time for flag to set
  }
  while ((IFG1 & OFIFG));                   // OSCFault flag still set?
  
  BCSCTL2 |= SELM_2;                        // MCLK = XT2 HF XTAL (safe)

  P5DIR |= 0x10;                            // P5.4= output direction
  P5SEL |= 0x10;                            // P5.4= MCLK option select
  
  //Initialize Timer A to generate one-second interrupt
  TACCTL0 = CCIE;                           // TACCR0 interrupt enabled
  TACCR0 = 32767;                           // Set CCR0 to 32767(ACLK=32.768Hz)                                      
  TACTL = TASSEL_1 + MC_1;                  // ACLK, up mode

  P1DIR |= 0x01;                            // Set P1.0 to output direction

// An immediate Osc Fault will occur next
  IE1 |= OFIE;                              // Enable osc fault interrupt


  while(1)
  {
    _BIS_SR(LPM3_bits + GIE);               // Enter LPM3, enable interrupts
    P1OUT ^= 0x01;                          // Toggle P1.0
  }
}

#pragma vector=NMI_VECTOR
__interrupt void nmi_ (void)
{
  volatile unsigned int i;

  do
  {
    IFG1 &= ~OFIFG;                         // Clear OSC Fault flag
    for (i = 0x47FF; i > 0; i--);           // Time for flag to set
    P1OUT ^= 0x01;                          // Toggle P1.0
  }while (IFG1 & OFIFG);                    // OSC Fault flag still set?
  IE1 |= OFIE;                              // Enable Osc Fault
}


// Timer A0 interrupt service routine
#pragma vector=TIMERA0_VECTOR 
__interrupt void Timer_A (void)
{
  _BIC_SR_IRQ(LPM3_bits+GIE);               // Exit LPM3 upon ISR exit
}
