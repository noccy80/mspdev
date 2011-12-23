//*****************************************************************************
//  MSP430x47xx Demo - SD16, Single Conversion on Single Channel Polling IFG
//
//  Description: This program uses the SD16 module to perform a single
//  conversion on a single channel. The SD16 interrupt flag for CH2 is polled
//  to determine when a conversion has completed. Test by applying a voltage
//  to CH2 (A2.0+, A2.0-) and setting a breakpoint at the line indicated
//  below. Run program until it reaches the breakpoint, then use the
//  debugger's register window to view the conversion results. The conversion
//  result for CH2 is stored in R12.
//  ACLK = LFXT1 = 32768 Hz, MCLK = SMCLK = DCO = 32 x ACLK = 1048576 Hz
//  //* An external watch crystal on XIN XOUT is required for ACLK     *//	
//  //* For minimum Vcc required for SD16 module - see datasheet        *//
//  //* 100nF cap btw Vref and AVss is recommended when using 1.2V ref *//
//
//                MSP430x47xx
//            -----------------
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
//  P. Thanigai / K.Venkat
//  Texas Instruments Inc.
//  November 2007
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.42A
//*****************************************************************************
#include  <msp430x47x4.h>

unsigned int results;

void main(void)
{
  volatile unsigned int i;                  // Use volatile to prevent removal
                                            // by compiler optimization

  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps
  for (i = 0; i < 10000; i++);              // Delay for 32 kHz crystal to
                                            // stabilize

  SD16CTL = SD16REFON+SD16SSEL0;            // 1.2V ref, SMCLK
  SD16CCTL2 |= SD16SNGL;                    // Single conv
  for (i = 0; i < 0x3600; i++);             // Delay for 1.2V ref startup

  while (1)
  {
    SD16CCTL2 |= SD16SC;                    // Set bit to start conversion
    while ((SD16CCTL2 & SD16IFG)==0);       // Poll interrupt flag for CH2
    results = SD16MEM2;                     // Save CH2 results (clears IFG)
    _NOP();                                 // SET BREAKPOINT HERE
  }
}
