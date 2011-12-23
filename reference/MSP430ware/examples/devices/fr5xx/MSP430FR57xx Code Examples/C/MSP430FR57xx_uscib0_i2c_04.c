//******************************************************************************
//  MSP430FR57xx Demo - USCI_B0 I2C Master RX single bytes from MSP430 Slave
//
//  Description: This demo connects two MSP430's via the I2C bus. The master
//  reads from the slave. This is the MASTER CODE. The data from the slave
//  transmitter begins at 0 and increments with each transfer.  
//  The USCI_B0 RX interrupt is used to know when new data has been received.
//  ACLK = n/a, MCLK = SMCLK = BRCLK =  DCO = 1MHz
//
//                                /|\  /|\
//               MSP430FR5739      10k  10k     MSP430F5739
//                   slave         |    |        master
//             -----------------   |    |   -----------------
//           -|XIN  P1.6/UCB0SDA|<-|----+->|P1.6/UCB0SDA  XIN|-
//            |                 |  |       |                 | 32kHz
//           -|XOUT             |  |       |             XOUT|-
//            |     P1.7/UCB0SCL|<-+------>|P1.7/UCB0SCL     |
//            |                 |          |             P1.0|--> LED
//
//   P. Thanigai
//   Texas Instruments Inc.
//   August 2010
//   Built with CCS V4 and IAR Embedded Workbench Version: 5.10
//******************************************************************************
#include "msp430fr5739.h"
unsigned char RXData;
void main (void)

{
	
    WDTCTL = WDTPW + WDTHOLD;
    // Init SMCLK = MCLk = ACLK = 1MHz
    CSCTL0_H = 0xA5;
    CSCTL1 |= DCOFSEL0 + DCOFSEL1;          // Set max. DCO setting = 8MHz
    CSCTL2 = SELA_3 + SELS_3 + SELM_3;      // set ACLK = MCLK = DCO
    CSCTL3 = DIVA_3 + DIVS_3 + DIVM_3;      // set all dividers to 1MHz
    // Configure pins 
    P1SEL1    |= BIT6 + BIT7;   	    

    UCB0CTLW0 |= UCSWRST;	            //Software reset enabled
    UCB0CTLW0 |= UCMODE_3  + UCMST + UCSYNC;//I2C mode, Master mode, sync
    UCB0CTLW1 |= UCASTP_2;		    //automatic stop generated 
                                            //after UCB0TBCNT is reached
    UCB0BRW    = 0x0008; 		    // baudrate = SMCLK / 8
    UCB0TBCNT |= 0x0001;		    //number of bytes to be received
    UCB0I2CSA  = 0x0048;		    //slave address
    UCB0CTL1  &=~UCSWRST;						
    UCB0IE    |= UCRXIE+UCNACKIE+UCBCNTIE; 	
    P1DIR |= BIT0;

	
    while (1)
    {
      __delay_cycles(2000);
      while (UCB0CTL1 & UCTXSTP);           // Ensure stop condition got sent
      UCB0CTL1 |= UCTXSTT;                  // I2C start condition
      
      __bis_SR_register(CPUOFF+GIE);        // Enter LPM0 w/ interrupt    
    }
}

	
	


#pragma vector = USCI_B0_VECTOR 
__interrupt void USCIB0_ISR(void)
{
	
  switch(__even_in_range(UCB0IV,0x1E))

  {
      case 0x00: break; // Vector 0: No interrupts break;
      case 0x02: break; // Vector 2: ALIFG break;
      case 0x04: 
                 UCB0CTL1 |= UCTXSTT; // I2C start condition
      break; // Vector 4: NACKIFG break;
      case 0x06: break; // Vector 6: STTIFG break;
      case 0x08: break; // Vector 8: STPIFG break;
      case 0x0a: break; // Vector 10: RXIFG3 break;
      case 0x0c: break; // Vector 14: TXIFG3 break;
      case 0x0e: break; // Vector 16: RXIFG2 break;
      case 0x10: break; // Vector 18: TXIFG2 break;
      case 0x12: break; // Vector 20: RXIFG1 break;
      case 0x14: break; // Vector 22: TXIFG1 break;
      case 0x16:   
                  RXData = UCB0RXBUF;    // Get RX data
                  __bic_SR_register_on_exit(CPUOFF); // Exit LPM0                 
                  break; // Vector 24: RXIFG0 break;
      case 0x18: break; // Vector 26: TXIFG0 break;
      case 0x1a: P1OUT ^= BIT0;
                 break; // Vector 28: BCNTIFG break;
      case 0x1c: break; // Vector 30: clock low timeout break;
      case 0x1e: break; // Vector 32: 9th bit break;
      default: break;	
	
  }	
	
}