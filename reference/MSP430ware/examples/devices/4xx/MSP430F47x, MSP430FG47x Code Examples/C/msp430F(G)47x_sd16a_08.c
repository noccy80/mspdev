//*****************************************************************************
//   MSP430F(G)47x Demo - SD16_A, Single Conversion on a Channel using buffered input
//
//  Description: This program uses the SD16_A module to perform a single
//  conversion on a single channel. A SD16_A interrupt occurs when a
//  conversion has completed. Test by applying a voltage to CH0
//  (A0+, A0-) and setting a breakpoint at the line indicated below.
//  Run program until it reaches the breakpoint, then use the debugger's
//  watch window to view the conversion result. Conversion result is
//  stored in variable "result".  NOTE: first conversion result won't
//  be available until after reaching breakpoint for the second time.
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

unsigned int result;

void main(void)
{
  volatile unsigned int i;                  // Use volatile to prevent removal
                                            // by compiler optimization

  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P6SEL |= BIT0+BIT1;			    // Config SD16 inputs 
  
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps
  for (i = 0; i < 10000; i++);              // Delay for 32 kHz crystal to
                                            // stabilize

  SD16CTL = SD16REFON+SD16SSEL0;            // 1.2V ref, SMCLK
  SD16CCTL0 |= SD16SNGL+SD16IE+SD16BUF_3;   // Single conv, enable interrupt, high impedance
  SD16INCTL0 |= SD16INTDLY_0;               // Interrupt on 4th sample
  for (i = 0; i < 0x3600; i++);             // Delay for 1.2V ref startup

  while (1)
  {
    SD16CCTL0 |= SD16SC;                    // SET BREAKPOINT HERE
                                            // Set bit to start conversion
    __bis_SR_register(LPM0_bits+GIE);       // Enter LPM0
  }
}

#pragma vector=SD16A_VECTOR
__interrupt void SD16ISR(void)
{
  switch (SD16IV)
  {
  case 2:                                   // SD16MEM Overflow
    break;
  case 4:                                   // SD16MEM0 IFG
    result = SD16MEM0;                      // Save CH0 results (clears IFG)
    break;
  }

  __bic_SR_register_on_exit(LPM0_bits);                   // Exit LPM0
}

