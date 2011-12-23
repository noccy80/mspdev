//***********************************************************************
//  MSP-FET430P140 Demo - Timer_A0, Capture of ACLK/8 using SMCLK
//
//  Description: Input capture of ACLK/8 on P1.1(TA0)
//  Run to breakpoint at the _NOP() instruction to see 16 capture
//  values and the differences.
//  ACLK = 32768Hz, MCLK = SMCLK = default ~800kHz
//  //* An external watch crystal on XIN XOUT is required for ACLK *//	
//
//                MSP430F149
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |        P2.0/ACLK|---+
//            |                 |   |
//            |         P1.1/TA0|<--+
//            |                 |
//            |             P1.0|--->LED

//
//  H. Grewal
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//******************************************************************************

#include  <msp430x14x.h>

unsigned int new_cap=0;
unsigned int old_cap=0;
unsigned int cap_diff=0;

unsigned int diff_array[16];                // RAM array for differences
unsigned int capture_array[16];             // RAM array for captures
unsigned char index=0;
unsigned char count = 0;

void main(void)
{
  volatile unsigned int i;
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  for (i=0; i<20000; i++)                   // Delay for crystal stabilization
  {
  }
  P1DIR = 0x01;                             // Set P1.0 out,1.1 input dir
  P1OUT &= ~0x01;                           // LED off
  P1SEL = 0x02;                             // Set P1.1 to TA0
  P2DIR = 0x01;                             // P2.0-ACLK
  P2SEL |= 0x01;
  BCSCTL1 |= DIVA_3;                        // ACLK/8

  CCTL0 = CM_1 + SCS + CCIS_0 + CAP + CCIE; // Rising edge + CCI0A (P1.1)
                                            // + Capture Mode + Interrupt

  TACTL = TASSEL_2 + MC_2;                  // SMCLK + Continuous Mode

  _BIS_SR(LPM0_bits + GIE);                 // LPM0 + Enable global ints
}

#pragma vector=TIMERA0_VECTOR
__interrupt void TimerA0(void)
{
   new_cap = TACCR0;
   cap_diff = new_cap - old_cap;

   diff_array[index] = cap_diff;            // record difference to RAM array
   capture_array[index++] = new_cap;
   if (index == 16)
   {
     index = 0;
     P1OUT ^= 0x01;                         // Toggle P1.0 using exclusive-OR
   }
   old_cap = new_cap;                       // store this capture value
   count ++;
   if (count == 32)
   {
     count = 0;
     _NOP();                                // SET BREAKPOINT HERE
   }

}
