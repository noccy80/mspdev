//*****************************************************************************
//  MSP-FET430P410 Demo - SD16, Single Conversion on a Single Channel Using ISR
//
//  Description: This program uses the SD16 module to perform a single
//  conversion on a single channel. A SD16 interrupt occurs when a
//  conversion has completed. Test by applying a voltage to CH2
//  (A2.0+, A2.0-) and setting a breakpoint at the line indicated below.
//  Run program until it reaches the breakpoint, then use the debugger's
//  watch window to view the conversion result. Conversion result is
//  stored in variable "result".  NOTE: first conversion result won't
//  be available until after reaching breakpoint for the second time.
//  ACLK = LFXT1 = 32768 Hz, MCLK = SMCLK = DCO = 32 x ACLK = 1048576 Hz
//  //* An external watch crystal on XIN XOUT is required for ACLK     *//	
//  //* Minimum Vcc is required for SD16 module - see datasheet        *//
//  //* 100nF cap btw Vref and AVss is recommended when using 1.2V ref *//
//
//                MSP430F427
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
//  H. Grewal
//  Texas Instruments Inc.
//  Feb 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.21A
//*****************************************************************************
#include  <msp430x42x.h>

unsigned int result;

void main(void)
{
  volatile unsigned int i;                  // Use volatile to prevent removal
                                            // by compiler optimization

  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps
  for (i = 0; i < 10000; i++);              // Delay for 32 kHz crystal to
                                            // stabilize

  SD16CTL = SD16REFON+SD16SSEL0;            // 1.2V ref, SMCLK
  SD16CCTL2 |= SD16SNGL+SD16IE ;            // Single conv, enable interrupt
  SD16INCTL2 |= SD16INTDLY0;                // Interrupt on 3rd sample
  for (i = 0; i < 0x3600; i++);             // Delay for 1.2V ref startup

  _EINT();                                  // Enable general interrupts

  while (1)
  {
    SD16CCTL2 |= SD16SC;                    // SET BREAKPOINT HERE
                                            // Set bit to start conversion
    _BIS_SR(LPM0_bits);                     // Enter LPM0
  }
}

#pragma vector=SD16_VECTOR
__interrupt void SD16ISR(void)
{
  switch (SD16IV)
  {
  case 2:                                   // SD16MEM Overflow
    break;
  case 4:                                   // SD16MEM0 IFG
    break;
  case 6:                                   // SD16MEM1 IFG
    break;
  case 8:                                   // SD16MEM2 IFG
    result = SD16MEM2;                      // Save CH2 results (clears IFG)
    break;
  }

  _BIC_SR_IRQ(LPM0_bits);                   // Exit LPM0
}

