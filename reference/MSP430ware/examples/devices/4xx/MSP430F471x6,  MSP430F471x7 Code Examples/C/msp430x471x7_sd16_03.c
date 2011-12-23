//*****************************************************************************
//  MSP430x471xx Demo - SD16, Continuous Conversion on a Single Channel
//
//  Description: This program uses the SD16 module to perform continuous
//  conversions on a single channel. A SD16 interrupt occurs whenever a
//  conversion has completed. Test by applying a voltage to channel 2
//  (A2.0+, A2.0-) and setting a breakpoint at the line indicated below.
//  Run program until it reaches the breakpoint, then use the debugger's
//  watch window to view the conversion results. Conversion results are
//  stored in the array, "results".
//  ACLK = LFXT1 = 32768 Hz, MCLK = SMCLK = DCO = 32 x ACLK = 1048576 Hz
//  //* An external watch crystal on XIN XOUT is required for ACLK     *//	
//  //* For Minimum Vcc required for SD16 module - see datasheet        *//
//  //* 100nF cap btw Vref and AVss is recommended when using 1.2V ref *//
//
//                MSP430x471xx
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//    Vin+ -->|A2.0+            |
//    Vin- -->|A2.0-            |
//            |                 |
//            |            VREF |---+
//            |                 |   |
//            |                 |  -+- 100nF
//            |                 |  -+-
//            |                 |   |
//            |            AVss |---+
//            |                 |
//
//   K. Venkat
//   Texas Instruments Inc.
//   May 2009
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 4.11B
//******************************************************************************
#include  <msp430x471x7.h>
#define   Num_of_Results   8

/* Arrays to store SD16 conversion results */
/* NOTE: arrays need to be global to       */
/*       prevent removal by compiler       */
unsigned int results[Num_of_Results];

void main(void)
{
  volatile unsigned int i;                  // Use volatile to prevent removal
                                            // by compiler optimization

  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps
  for (i = 0; i < 10000; i++);              // Delay for 32 kHz crystal to
                                            // stabilize

  SD16CTL = SD16REFON+SD16SSEL0;            // 1.2V ref, SMCLK
  //SD16INCTL2 |= SD16INTDLY0;                // Interrupt on 3rd sample
  SD16CCTL2 |= SD16IE ;                     // Enable interrupt
  for (i = 0; i < 0x3600; i++);             // Delay for 1.2V ref startup
  
  SD16CCTL2 |= SD16SC;                      // Set bit to start conversion
  __bis_SR_register(LPM0_bits + GIE);          // Enter LPM0 w/ interrupts

}

#pragma vector=SD16A_VECTOR
__interrupt void SD16AISR(void)
{
  static unsigned int index = 0;

  switch (SD16IV)
  {
    case 2:                                   // SD16MEM Overflow
      break;
    case 4:                                   // SD16MEM0 IFG
      break;
    case 6:                                   // SD16MEM1 IFG
      break;
    case 8:                                   // SD16MEM2 IFG
      results[index] = SD16MEM2;              // Save CH2 results (clears IFG)
      if (++index == Num_of_Results)
      {
        index = 0;                            // SET BREAKPOINT HERE
      }
      break;
  }
}


