//*****************************************************************************
//   MSP430F(G)47x Demo - SD16_A, Using the Integrated Battery Sensor
//
//  Description: This example shows how to use the SD16_A module's integrated
//  Battery sensor (connected to input channel 5) to measure VCC.
//  A single conversion is initiated and then the CPU is disabled by entering
//  LPM0. Once the conversion has completed, a SD16_A interrupt occurs and
//  stores the result in variable "ADCresult".  LED lights if battery is low
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
//            |A5+              | ( A5+, A5- connected internally )
//            |A5-              |
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

#define LOW_BAT 0xB999                      // ~3V

static unsigned int ADCresult;

void main(void)
{
  volatile unsigned int i;                  // Use volatile to prevent removal
                                            // by compiler optimization
  P4OUT &= ~0x40;
  P4DIR |= 0x40;

  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps
  for (i = 0; i < 10000; i++);              // Delay for 32 kHz crystal to
                                            // stabilize

  SD16CTL = SD16REFON+SD16SSEL0+SD16DIV_3;  // 1.2V ref, SMCLK/8
  SD16CCTL0 |= SD16SNGL+SD16IE ;            // Single conv, enable interrupt
  SD16INCTL0 |= SD16INCH_5;                 // Select Channel A5
  for (i = 0; i < 0x3600; i++);             // Delay for 1.2V ref startup

  while (1)
  {
    SD16CCTL0 |= SD16SC;                    // Set bit to start conversion
    __bis_SR_register(LPM0_bits+GIE);       // Enter LPM0
   if( ADCresult < LOW_BAT )
   {
    P4OUT |= 0x40;
   }
   else
   {
     P4OUT &= ~0x40;
   }
    _NOP();                                 //SET BREAKPOINT HERE
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
    ADCresult = SD16MEM0;                   // Save results (clears IFG)
    break;
  }

  __bic_SR_register_on_exit(LPM0_bits);                   // Exit LPM0
}


