//******************************************************************************
//  MSP430F22x4 Demo - USCI_B0 I2C Master to TMP100, Set P5.1 if Temp > 28C
//
//  Description: I2C interface to TMP100 temperature sensor in 9-bit mode.
//  Timer_A CCR0 interrupt is used to wake up and read the two bytes of
//  the TMP100 temperature register every 62ms. If the temperature is greater
//  than 28C, P1.0 is set, else reset. CPU is operated in LPM0. I2C speed
//  is ~100kHz.
//  ACLK = n/a, MCLK = SMCLK = TACLK = BRCLK = default DCO = ~1.2MHz
//
//         /|\           /|\ /|\
//          |   TMP100   10k 10k     MSP430F22x4
//          |   -------   |   |   -------------------
//          +--|Vcc SDA|<-|---+->|P3.1/UCB0SDA    XIN|-
//          |  |       |  |      |                   |
//          +--|A1,A0  |  |      |               XOUT|-
//             |       |  |      |                   |
//          +--|Vss SCL|<-+------|P3.2/UCB0SCL   P1.0|---> LED
//         \|/  -------          |                   |
//
//  Andreas Dannenberg
//  Texas Instruments Inc.
//  September 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include "msp430x22x4.h"

unsigned int RxByteCtr;
unsigned int RxWord;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // P1.0 output
  P3SEL |= 0x06;                            // Assign I2C pins to USCI_B0
  UCB0CTL1 |= UCSWRST;                      // Enable SW reset
  UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
  UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
  UCB0BR0 = 12;                             // fSCL = SMCLK/12 = ~100kHz
  UCB0BR1 = 0;
  UCB0I2CSA = 0x4e;                         // Set slave address
  UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
  IE2 |= UCB0RXIE;                          // Enable RX interrupt
  TACTL = TASSEL_2 + MC_2;                  // SMCLK, contmode

  while (1)
  {
    RxByteCtr = 2;                          // Load RX byte counter
    UCB0CTL1 |= UCTXSTT;                    // I2C start condition
    __bis_SR_register(CPUOFF + GIE);        // Enter LPM0, enable interrupts
                                            // Remain in LPM0 until all data
                                            // is RX'd

    if (RxWord < 0x1d00)                    // >28C?
      P1OUT &= ~0x01;                       // No, P1.0 = 0
    else
      P1OUT |= 0x01;                        // Yes, P1.0 = 1

    __disable_interrupt();
    TACCTL0 |= CCIE;                        // TACCR0 interrupt enabled
    __bis_SR_register(CPUOFF + GIE);        // Enter LPM0, enable interrupts
                                            // Remain in LPM0 until TACCR0
                                            // interrupt occurs
    TACCTL0 &= ~CCIE;                       // TACCR0 interrupt disabled
  }
}

#pragma vector = TIMERA0_VECTOR
__interrupt void TA0_ISR(void)
{
  __bic_SR_register_on_exit(CPUOFF);        // Exit LPM0
}

// The USCIAB0TX_ISR is structured such that it can be used to receive any
// 2+ number of bytes by pre-loading RxByteCtr with the byte count.
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
  RxByteCtr--;                              // Decrement RX byte counter

  if (RxByteCtr)
  {
    RxWord = (unsigned int)UCB0RXBUF << 8;  // Get received byte
    if (RxByteCtr == 1)                     // Only one byte left?
      UCB0CTL1 |= UCTXSTP;                  // Generate I2C stop condition
  }
  else
  {
    RxWord |= UCB0RXBUF;                    // Get final received byte,
                                            // Combine MSB and LSB
    __bic_SR_register_on_exit(CPUOFF);      // Exit LPM0
  }
}

