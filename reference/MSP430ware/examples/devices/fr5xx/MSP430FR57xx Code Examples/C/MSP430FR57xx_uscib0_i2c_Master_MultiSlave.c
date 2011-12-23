//******************************************************************************
//  MSP430FR57xx Demo - USCI_B0 I2C Master TX bytes to Multiple Slaves
//
//  Description: This demo connects two MSP430's via the I2C bus. 
//  The master transmits to 4 different I2C slave addresses 0x0A,0x0B,0x0C&0x0D.
//  Each slave address has a specific related data in the array TXData[].
//  At the end of four I2C transactions the slave address rolls over and begins 
//  again at 0x0A.
//  ACLK = n/a, MCLK = SMCLK = BRCLK = default DCO = ~1.045MHz
//  Use with MSP430FR57xx_uscib0_i2c_MultiSlave.c
//
//                                /|\  /|\
//                MSP430FR5739    10k  10k     MSP430FR5739
//                   slave         |    |         master
//             -----------------   |    |   -----------------
//           -|XIN  P1.6/UCB0SDA|<-|----+->|P1.6/UCB0SDA  XIN|-
//            |                 |  |       |                 |
//           -|XOUT             |  |       |             XOUT|-
//            |     P1.7/UCB0SCL|<-+------>|P1.7/UCB0SCL     |
//            |                 |          |                 |
//
//   P. Thanigai
//   Texas Instruments Inc.
//   August 2010
//   Built with CCS V4 and IAR Embedded Workbench Version: 5.10
//******************************************************************************
#include "msp430fr5739.h"

unsigned char TXData[]= {0xA1,0xB1,0xC1,0xD1};// Pointer to TX data
unsigned char SlaveAddress[]= {0x0A,0x0B,0x0C,0x0D};                         
unsigned char TXByteCtr;
unsigned char SlaveFlag = 0;

void main(void)

{
    WDTCTL = WDTPW + WDTHOLD;
    // Init SMCLK = MCLk = ACLK = 1MHz
    CSCTL0_H = 0xA5;
    CSCTL1 |= DCOFSEL0 + DCOFSEL1;          // Set max. DCO setting = 8MHz
    CSCTL2 = SELA_3 + SELS_3 + SELM_3;      // set ACLK = MCLK = DCO
    CSCTL3 = DIVA_3 + DIVS_3 + DIVM_3;      // set all dividers to 1MHz

    // Configure Pins for I2C
    P1SEL1 |= BIT6 + BIT7;                  // Pin init

    UCB0CTLW0 |= UCSWRST;                   // put eUSCI_B in reset state
    UCB0CTLW0 |= UCMODE_3 + UCMST + UCSSEL_2;// I2C master mode, SMCLk 
    UCB0BRW = 0x8;                          // baudrate = SMCLK / 8
    UCB0CTLW0 &=~ UCSWRST;	            //clear reset register
    UCB0IE |= UCTXIE0 + UCNACKIE;           //transmit and NACK interrupt enable
    SlaveFlag =0;
    while(1)
    {
    UCB0I2CSA = SlaveAddress[SlaveFlag];    // configure slave address
    TXByteCtr = 1;                          // Load TX byte counter              
    while (UCB0CTLW0 & UCTXSTP);            // Ensure stop condition got sent
    UCB0CTLW0 |= UCTR + UCTXSTT;            // I2C TX, start condition

    __bis_SR_register(CPUOFF + GIE);        // Enter LPM0 w/ interrupts
                                            // Remain in LPM0 until all data
                                            // is TX'd
    // Change Slave address
    SlaveFlag++; 
    if (SlaveFlag>3)                        // Roll over slave address
      {
        SlaveFlag =0;
        __delay_cycles(1000);               // Delay between transmissions
      }
   
    }
	
}



	
#pragma vector = USCI_B0_VECTOR 
__interrupt void USCIB0_ISR(void) 
{	
  switch(__even_in_range(UCB0IV,0x1E)) 
  {
        case 0x00: break;                   // Vector 0: No interrupts break;
        case 0x02: break;
        case 0x04:
          UCB0CTLW0 |= UCTXSTT;             //resend start if NACK
          break;                            // Vector 4: NACKIFG break;
        case 0x06: break;                   // Vector 6: STTIFG break;
        case 0x08: break;                   // Vector 8: STPIFG break;
        case 0x0a: break;                   // Vector 10: RXIFG3 break;
        case 0x0c: break;                   // Vector 14: TXIFG3 break;
        case 0x0e: break;                   // Vector 16: RXIFG2 break;
        case 0x10: break;                   // Vector 18: TXIFG2 break;
        case 0x12: break;                   // Vector 20: RXIFG1 break;
        case 0x14: break;                   // Vector 22: TXIFG1 break;
        case 0x16: break;                   // Vector 24: RXIFG0 break;  
        case 0x18: 
	  if (TXByteCtr)                    // Check TX byte counter
          {
            UCB0TXBUF = TXData[SlaveFlag];  // Load TX buffer
            TXByteCtr--;                    // Decrement TX byte counter
          }
          else
          {
            UCB0CTLW0 |= UCTXSTP;           // I2C stop condition
            UCB0IFG &= ~UCTXIFG;            // Clear USCI_B0 TX int flag
            __bic_SR_register_on_exit(CPUOFF);// Exit LPM0
          }
          break;                            // Vector 26: TXIFG0 break;
        default: break;
  }
}
	