//******************************************************************************
//   MSP430F22x4 Demo - Timer_A, Ultra-Low Pwr Pulse Accumulator
//
//   Description: Timer_A is used as ultra-low power pulse counter. In this
//   example TAR is offset 100 counts, which are acculmulated on INCLK P2.1,
//   with the system in LPM4 - all internal clocks off. After 100 counts, TAR
//   will overflow requesting an interrupt, and waking the system. Timer_A is
//   then reconfigured with SMCLK as clock source in up mode - TACCR1 will then
//   toggle P1.0 every 50000 SMCLK cycles.
//
//                MSP430F22x4
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//        --->|P2.1/TAINCLK P1.0|-->LED
//
//   A. Dannenberg
//   Texas Instruments Inc.
//   October 2006
//   Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR = 0xFF;                             // All P1.x outputs
  P1OUT = 0;                                // All P1.x reset
  P2DIR = 0xFD;                             // All but P2.1 outputs
  P2SEL = 0x02;                             // P2.1 TAINCLK option select
  P2OUT = 0;                                // All P2.x reset
  P3DIR = 0xFF;                             // All P3.x outputs
  P3OUT = 0;                                // All P3.x reset
  P4DIR = 0xFF;                             // All P4.x outputs
  P4OUT = 0;                                // All P4.x reset
  TACTL = TASSEL1 + TASSEL0 + TACLR + TAIE; // Ext. INCLK, interrupt
  TAR = 0xFFFF - 100;                       // Offset until TAR overflow
  TACTL |= MC1;                             // Start Timer_A continuous mode
  __bis_SR_register(LPM4_bits + GIE);       // Enter LPM4 w/ interrupts

  while (1)
  {
    P1OUT ^= 0x01;                          // P1.0 = toggle
    __bis_SR_register(LPM0_bits);           // CPU is not required
  }
}

#pragma vector = TIMERA1_VECTOR
__interrupt void TA1_ISR(void)
{
  switch (TAIV)        // Efficient switch-implementation
  {
    case 2:
      TACCR1 += 50000;                      // Add Offset to TACCR1
      __bic_SR_register_on_exit(LPM0_bits); // CPU active on reti
      break;
    case 10:
      TACTL = TASSEL1 + TACLR;              // SMCLK, clear TAR
      TACCTL1 = CCIE;                       // TACCR1 interrupt enabled
      TACCR1 = 50000;
      TACTL |= MC1;                         // Start Timer_A in continuous
      __bic_SR_register_on_exit(LPM4_bits); // Exit LPM4 on reti
      break;
  }
}




