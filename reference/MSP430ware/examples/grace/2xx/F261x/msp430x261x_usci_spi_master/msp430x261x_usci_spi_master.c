//******************************************************************************
//   msp430x26x Demo - USCI_A0, SPI 3-Wire Master Incremented Data
//
//   Description: SPI master talks to SPI slave using 3-wire mode. Incrementing
//   data is sent by the master starting at 0x01. Received data is expected to
//   be same as the previous transmission.  USCI RX ISR is used to handle
//   communication with the CPU, normally in LPM0. If high, P1.0 indicates
//   valid data reception.  Because all execution after LPM0 is in ISRs,
//   initialization waits for DCO to stabilize against ACLK.
//   ACLK = 32.768kHz, MCLK = SMCLK = DCO ~ 1048kHz.  BRCLK = SMCLK/2
//
//   Use with SPI Slave Data Echo code example.  If slave is in debug mode, P1.1
//   slave reset signal conflicts with slave's JTAG; to work around, use IAR's
//   "Release JTAG on Go" on slave device.  If breakpoints are set in
//   slave RX ISR, master must stopped also to avoid overrunning slave
//   RXBUF.
//
//                    MSP430F261x/241x
//                 -----------------
//             /|\|              XIN|-
//              | |                 |  32kHz xtal
//              --|RST          XOUT|-
//                |                 |
//                |             P3.4|-> Data Out (UCA0SIMO)
//                |                 |
//          LED <-|P1.0         P3.5|<- Data In (UCA0SOMI)
//                |                 |
//  Slave reset <-|P1.1         P3.0|-> Serial Clock Out (UCA0CLK)
//******************************************************************************
/*
 * ======== Standard MSP430 includes ========
 */
#include <msp430.h>

/*
 * ======== Grace related includes ========
 */
#include <ti/mcu/msp430/csl/CSL.h>

/*
 *  ======== main ========
 */

unsigned char MST_Data,SLV_Data;
volatile unsigned int i;

int main(int argc, char *argv[])
{
    WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
    if (CALBC1_1MHZ ==0xFF || CALDCO_1MHZ == 0xFF)
    {
      while(1);                               // If calibration constants erased
                                              // do not load, trap CPU!!
    }

    CSL_init();                     // Activate Grace-generated configuration

    P1OUT &= ~0x02;                           // Now with SPI signals initialized,
    P1OUT |= 0x02;                            // reset slave

    for(i=50;i>0;i--);                        // Wait for slave to initialize

    MST_Data = 0x001;                         // Initialize data values
    SLV_Data = 0x000;                         //

    UCA0TXBUF = MST_Data;                     // Transmit first character

    _BIS_SR(LPM0_bits + GIE);                 // CPU off, enable interrupts
}

void USCIA0RX_ISR(void)
{
    while (!(IFG2 & UCA0TXIFG));              // USART1 TX buffer ready?
    if (UCA0RXBUF==SLV_Data)                  // Test for correct character RX'd
      P1OUT |= 0x01;                          // If correct, light LED
    else
      P1OUT &= ~0x01;                         // If incorrect, clear LED

    MST_Data++;                               // Increment data
    SLV_Data++;
    UCA0TXBUF = MST_Data;                     // Send next value

    for(i=30;i>0;i--);                        // Add time between transmissions to
}                                           // make sure slave can keep up
