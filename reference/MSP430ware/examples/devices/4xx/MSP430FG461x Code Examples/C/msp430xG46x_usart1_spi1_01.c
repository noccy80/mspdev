//******************************************************************************
//   MSP430xG46x Demo - USART1, SPI Interface to TLC549 8-Bit ADC
//
//   Description:  This program demonstrates USART1 in SPI mode, interfaced to a
//   TLC549 8-bit ADC. If AIN > 0.5(REF+ - REF-), then P5.1 is set, otherwise it
//   is reset.  R15 = 8-bit ADC code.
//   ACLK = 32.768kHz, MCLK = SMCLK = default DCO ~ 1048k, UCLK1 = SMCLK/2
//   //* VCC must be at least 3V for TLC549 *//
//
//                           MSP430xG461x
//                       -----------------
//                   /|\|              XIN|-
//        TLC549      | |                 |
//    -------------   --|RST          XOUT|-
//   |           CS|<---|P4.6             |
//   |      DATAOUT|--->|P4.4/SOMI1       |
// ~>| IN+  I/O CLK|<---|P4.5/UCLK1       |
//
//   Keith Quiring/ M. Mitchell
//   Texas Instruments Inc.
//   March 2006
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include  <msp430xG46x.h>

void main(void)
{
  volatile unsigned int i;
  char data;

  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
  FLL_CTL0 |= XCAP14PF;                     // Configure load caps

  // Wait for xtal to stabilize
  do
  {
  IFG1 &= ~OFIFG;                           // Clear OSCFault flag
  for (i = 0x47FF; i > 0; i--);             // Time for flag to set
  }
  while ((IFG1 & OFIFG));                   // OSCFault flag still set?

  P5DIR |= 0x02;                            // P5.1 as output
  P4SEL |= 0x30;                            // P4.2,3 SPI option select
  P4DIR |= 0x60;                            // P4.3,0 as outputs
  ME2 |= USPIE1;                            // Enable USART1 SPI
  U1TCTL |= CKPH+SSEL1+SSEL0+STC;           // SMCLK, 3-pin mode
  U1CTL |= CHAR+SYNC+MM;                    // 8-bit SPI master
  U1BR0 = 0x02;                             // SMCLK/2 for baud rate
  U1BR1 = 0;                                // SMCLK/2 for baud rate
  U1MCTL = 0;                               // Clear modulation
  U1CTL &= ~SWRST;                          // Initialize USART state machine

  while(1)
  {
    P4OUT &= ~0x40;                         // Enable TLC549 by enabling /CS
    U1TXBUF = 0x00;                         // Dummy write to start SPI
    while (!(IFG2 & URXIFG1));              // USART1 RX buffer ready?

    data = U1RXBUF;                         // data = 00|DATA

    P4OUT |= 0x40;                          // Disable '549 by driving /CS high
    P5OUT &= ~0x02;                         // P5.1 = 0

    if(data>=0x7F)                          // data = AIN > 0.5(REF+ - REF-)?
      P5OUT |= 0x02;                        // P5.2 = 1
  }
}
