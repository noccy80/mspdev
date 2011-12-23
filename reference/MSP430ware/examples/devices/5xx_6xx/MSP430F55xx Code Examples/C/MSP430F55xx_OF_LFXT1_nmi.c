//******************************************************************************
//  MSP430F552x Demo - LFXT1 Oscillator Fault Detection
//
//  Description: System runs normally in LPM3 with with basic timer clocked by
//  32kHz ACLK with a 1 second interrupt. P1.0 is normally toggled every
//  1 second inside basic timer interrupt. If an LFXT1 oscillator fault occurs,
//  NMI is requested forcing exit from LPM3. P1.0 is toggled rapidly by
//  software as long as LFXT1 oscillator fault is present. Assuumed only
//  LFXT1 as NMI source - code does not check for other NMI sources.
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//
//           MSP430F5529
//         -----------------
//    /|\ |              XIN|-
//     |  |                 | 32kHz
//     ---|RST          XOUT|-
//        |                 |
//        |             P1.0|-->LED
//
//   Bhargavi Nisarga
//   Texas Instruments Inc.
//   April 2009
//   Built with CCSv4 and IAR Embedded Workbench Version: 4.21
//******************************************************************************

#include <msp430f5529.h>

volatile unsigned int i;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

  // Set up XT1
  P5SEL |= BIT4+BIT5;                       // Select XT1
  UCSCTL6 &= ~(XT1OFF);                     // XT1 On
  UCSCTL6 |= XCAP_3;                        // Internal load cap

  P1DIR |= BIT0;                            // P1.0 output

  RTCCTL01 = RTCTEV_3;
  RTCPS0CTL = RT0PSDIV_7;                   // Set RTPS0 to /256
  RTCPS1CTL = RT1IP_6 + RT1PSIE + RT1SSEL_3;// Set RT1IP to /4, enable
                                            // RT1PS interrupt and select
                                            // RTOPS output as clock

  SFRIE1 = OFIE;                            // Enable osc fault interrupt

  __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3, enable interrupts
  __no_operation();                         // For debugger
}


// RTC Interrupt Service Routine
#pragma vector=RTC_VECTOR
__interrupt void RTC_ISR(void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0
  RTCCTL01 &= ~RTCTEVIFG;
  RTCPS1CTL &= ~RT1PSIFG;
}

#pragma vector=UNMI_VECTOR
__interrupt void UNMI_ISR(void)
{
  do
  {
    UCSCTL7 &= ~(XT1LFOFFG + DCOFFG);       // Clear XT1 & DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear OSC Fault flag
    for (i = 0x0FFF; i > 0; i--);           // Time for flag to set????
    P1OUT ^= BIT0;                          // Toggle P1.0 
  }while ( (SFRIFG1 & OFIFG) );
}
