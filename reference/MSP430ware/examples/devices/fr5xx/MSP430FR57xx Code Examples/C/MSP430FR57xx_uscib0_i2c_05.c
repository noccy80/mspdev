//******************************************************************************
//  MSP430FR57xx Demo - USCI_B0 I2C Slave TX single bytes to MSP430 Master
//
//  Description: This demo connects two MSP430's via the I2C bus. The master
//  reads from the slave. This is the SLAVE code. The TX data begins at 0
//  and is incremented each time it is sent. A stop condition
//  is used as a trigger to increment the outgoing data. 
//  The USCI_B0 TX interrupt is used to know
//  when to TX.
//  ACLK = n/a, MCLK = SMCLK = DCO = 1MHz
//
//                                /|\  /|\
//               MSP430FR5739      10k  10k     MSP430FR5739
//                   slave         |    |        master
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

unsigned char TXData;

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
    // eUSCI configuration
    UCB0CTLW0 |= UCSWRST ;	            //Software reset enabled
    UCB0CTLW0 |= UCMODE_3  + UCSYNC;	    //I2C mode, sync mode
    UCB0I2COA0 = 0x48 + UCOAEN;   	    //own address is 0x48 + enable	
    UCB0CTLW0 &=~UCSWRST;	            //clear reset register
    UCB0IE |=  UCTXIE0 + UCSTPIE; 	    //transmit,stop interrupt enable	
    __bis_SR_register(CPUOFF + GIE);        // Enter LPM0 w/ interrupts
    __no_operation();	 
}


#pragma vector = USCI_B0_VECTOR 
__interrupt void USCIB0_ISR(void)

{
	
switch(__even_in_range(UCB0IV,0x1E)) 
    {
        case 0x00: break; // Vector 0: No interrupts break;
        case 0x02: break; // Vector 2: ALIFG 
        case 0x04: break; // Vector 4: NACKIFG 
        case 0x06: break; // Vector 6: STTIFG         
        case 0x08:       // Vector 8: STPIFG 
          TXData++;
          UCB0IFG &= ~UCSTPIFG;// Clear stop condition int flag          
          break; 
        case 0x0a: break; // Vector 10: RXIFG3 break;
        case 0x0c: break; // Vector 14: TXIFG3 break;
        case 0x0e: break; // Vector 16: RXIFG2 break;
        case 0x10: break; // Vector 18: TXIFG2 break;
        case 0x12: break; // Vector 20: RXIFG1 break;
        case 0x14: break; // Vector 22: TXIFG1 break;
        case 0x16: break; // Vector 24: RXIFG0 break;
        case 0x18: 
           UCB0TXBUF = TXData;                  
           break; // Vector 26: TXIFG0 break;
        case 0x1a: break; // Vector 28: BCNTIFG break;
        case 0x1c: break; // Vector 30: clock low timeout break;
        case 0x1e: break; // Vector 32: 9th bit break;
        default: break;	
	
    }
}


