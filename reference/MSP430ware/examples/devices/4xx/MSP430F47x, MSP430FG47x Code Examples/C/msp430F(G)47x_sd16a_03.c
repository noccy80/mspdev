//*****************************************************************************
//   MSP430F(G)47x Demo - SD16_A, Continuous Conversion on a Single Channel
//
//  Description: This program uses the SD16_A module to perform continuous
//  conversions on a single channel. A SD16_A interrupt occurs whenever a
//  conversion has completed. Test by applying a voltage to CH0
//  (A0+, A0-) and setting a breakpoint at the line indicated below.
//  Run program until it reaches the breakpoint, then use the debugger's
//  watch window to view the conversion results. Conversion results are
//  stored in the array, "results".
//  ACLK = LFXT1 = 32768 Hz, MCLK = SMCLK = DCO = 32 x ACLK = 1048576 Hz
//  //* An external watch crystal on XIN XOUT is required for ACLK     *//
//  //* Minimum Vcc is required for SD16_A module - see datasheet        *//
//  //* 100nF cap btw Vref and AVss is recommended when using 1.2V ref *//
//
//                MSP430F(G)47x
//             -----------------
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


#define   Num_of_Results   8

/* Arrays to store SD16_A conversion results */
unsigned int results[Num_of_Results];

void main(void)
{
  volatile unsigned int i;                  // Use volatile to prevent removal
                                            // by compiler optimization

  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps
  
  P6SEL |= BIT0+BIT1;			    // Config SD16 inputs 
  
  for (i = 0; i < 10000; i++);              // Delay for 32 kHz crystal to
                                            // stabilize

  SD16CTL = SD16REFON+SD16SSEL0;            // 1.2V ref, SMCLK
  SD16INCTL0 |= SD16INTDLY_0;               // Interrupt on 4th sample
  SD16CCTL0 |= SD16IE ;                     // Enable interrupt
  for (i = 0; i < 0x3600; i++);             // Delay for 1.2V ref startup

  SD16CCTL0 |= SD16SC;                      // Set bit to start conversion
  __bis_SR_register(LPM0_bits+GIE);         // Enter LPM0

}

#pragma vector=SD16A_VECTOR
__interrupt void SD16ISR(void)
{
  static unsigned int index = 0;

  switch (SD16IV)
  {
  case 2:                                   // SD16MEM Overflow
    break;
  case 4:                                   // SD16MEM0 IFG
    results[index] = SD16MEM0;              // Save CH0 results (clears IFG)

    if (++index == Num_of_Results)
    {
      index = 0;                            // SET BREAKPOINT HERE
    }
    break;
  }
}

