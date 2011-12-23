//******************************************************************************
//  MSP430F20xx Demo - I2C Master Receiver, single byte
//
//  Description: I2C Master communicates with I2C Slave using
//  the USI. Slave data should increment from 0x00 with each transmitted byte
//  which is verified by the Master.
//  LED off for address or data Ack; LED on for address or data NAck.
//  ACLK = n/a, MCLK = SMCLK = Calibrated 1MHz
//
//  ***THIS IS THE MASTER CODE***
//
//                  Slave                      Master
//          (msp430x20xx_i2c_slave_tx.c)
//               MSP430F20x2/3              MSP430F20x2/3
//             -----------------          -----------------
//         /|\|              XIN|-    /|\|              XIN|-
//          | |                 |      | |                 |
//          --|RST          XOUT|-     --|RST          XOUT|-
//            |                 |        |                 |
//      LED <-|P1.0             |        |                 |
//            |                 |        |             P1.0|-> LED
//            |         SDA/P1.7|------->|P1.7/SDA         |
//            |         SCL/P1.6|<-------|P1.6/SCL         |
//
//  Note: internal pull-ups are used in this example for SDA & SCL
/*
 * ======== Standard MSP430 includes ========
 */
#include <msp430.h>

/*
 * ======== Grace related includes ========
 */
#include <ti/mcu/msp430/csl/CSL.h>

char SLV_data = 0x00;                  // Variable for received data
char SLV_Addr = 0x91;                  // Address is 0x48 << 1 bit + 1 for Read
int I2C_State = 0;                     // State variable

/*
 *  ======== main ========
 */
void main(int argc, char *argv[])
{
	volatile unsigned int i;             // Use volatile to prevent removal
	CSL_init();
	USICTL0 &= ~USISWRST;                // Enable USI
	USICTL1 &= ~USIIFG;                  // Clear pending flag
	_EINT();
	while(1)
	{
		USICTL1 |= USIIFG;                 // Set flag and start communication
		LPM0;                              // CPU off, await USI interrupt
		_NOP();                            // Used for IAR
		for (i = 0; i < 5000; i++);        // Dummy delay between communication cycles
	}

}
unsigned short USI_TXRX(void)
{
	 switch(I2C_State)
	    {
	      case 0: // Generate Start Condition & send address to slave
	              P1OUT |= 0x01;           // LED on: sequence start
	              USISRL = 0x00;           // Generate Start Condition...
	              USICTL0 |= USIGE+USIOE;
	              USICTL0 &= ~USIGE;
	              USISRL = SLV_Addr;       // ... and transmit address, R/W = 1
	              USICNT = (USICNT & 0xE0) + 0x08; // Bit counter = 8, TX Address
	              I2C_State = 2;           // Go to next state: receive address (N)Ack
	              break;

	      case 2: // Receive Address Ack/Nack bit
	              USICTL0 &= ~USIOE;       // SDA = input
	              USICNT |= 0x01;          // Bit counter = 1, receive (N)Ack bit
	              I2C_State = 4;           // Go to next state: check (N)Ack
	              break;

	      case 4: // Process Address Ack/Nack & handle data RX
	              if (USISRL & 0x01)       // If Nack received...
	              { // Prep Stop Condition
	                USICTL0 |= USIOE;
	                USISRL = 0x00;
	                USICNT |=  0x01;       // Bit counter = 1, SCL high, SDA low
	                I2C_State = 10;        // Go to next state: generate Stop
	                P1OUT |= 0x01;         // Turn on LED: error
	              }
	              else                     // Ack received
	              { // Receive Data from slave
	                USICNT |=  0x08;       // Bit counter = 8, RX data
	                I2C_State = 6;         // Go to next state: Test data and (N)Ack
	                P1OUT &= ~0x01;        // LED off
	              }
	              break;

	      case 6: // Send Data Ack/Nack bit
	              USICTL0 |= USIOE;        // SDA = output
	              if (USISRL == SLV_data)  // If data valid...
	              {
	                USISRL = 0x00;         // Send Ack
	                SLV_data++;            // Increment Slave data
	                P1OUT &= ~0x01;        // LED off
	              }
	              else
	              {
	                USISRL = 0xFF;         // Send NAck
	                P1OUT |= 0x01;         // LED on: error
	              }
	              USICNT |= 0x01;          // Bit counter = 1, send (N)Ack bit
	              I2C_State = 8;           // Go to next state: prep stop
	              break;

	      case 8: // Prep Stop Condition
	              USICTL0 |= USIOE;        // SDA = output
	              USISRL = 0x00;
	              USICNT |=  0x01;         // Bit counter = 1, SCL high, SDA low
	              I2C_State = 10;          // Go to next state: generate Stop
	              break;

	      case 10: // Generate Stop Condition
	              USISRL = 0x0FF;          // USISRL = 1 to release SDA
	              USICTL0 |= USIGE;        // Transparent latch enabled
	              USICTL0 &= ~(USIGE+USIOE);// Latch/SDA output disabled
	              I2C_State = 0;           // Reset state machine for next transmission
	              return (LPM0_bits);               // Exit active for next transfer
	    }

	  USICTL1 &= ~USIIFG;                  // Clear pending flag
	  return 0; 							// Resume LPM
}
