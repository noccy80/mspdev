//******************************************************************************
//   MSP430F66x Demo - USCI_A0, SPI 3-Wire Master Incremented Data
//
//   Description: SPI master talks to SPI slave using 3-wire mode. Incrementing
//   data is sent by the master starting at 0x01. Received data is expected to
//   be same as the previous transmission.  USCI RX ISR is used to handle
//   communication with the CPU, normally in LPM0. If high, P1.0 indicates
//   valid data reception.  Because all execution after LPM0 is in ISRs,
//   initialization waits for DCO to stabilize against ACLK.
//   
//   ACLK = ~32.768kHz, MCLK = SMCLK = DCO ~ 1048kHz.  BRCLK = SMCLK/2
//
//   Use with SPI Slave Data Echo code example. The master code example uses
//   a GPIO P1.1 to reset the SPI slave state machine.
//
//   Note that UCB0CLK, UCB0SIMO and UCB0SOMI need to be assigned pins via the 
//   PMAP controller.
//
//                     MSP430F66x
//                   -----------------
//               /|\|                 |
//                | |                 |
//                --|RST          P1.0|-> LED
//                  |                 |
//                  |             P2.2|-> Data Out (UCA0SIMO)
//                  |                 |
//                  |             P2.1|<- Data In (UCA0SOMI)
//                  |                 |
//Slave SPI reset <-|P1.1         P2.0|-> Serial Clock Out (UCA0CLK)
//
//
//   Priya Thanigai
//   Texas Instruments Inc.
//   Nov 2009
//   Built with IAR Embedded Workbench Version: 4.20 & Code Composer Studio V4.0
//******************************************************************************
#include <msp430f6638.h>

void Port_Mapping(void);

unsigned char MST_Data,SLV_Data;
unsigned char temp;

void main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
  Port_Mapping();
  
  P2SEL |= BIT0+BIT1+BIT2;                  // Assign P2.0 to UCB0CLK and...
  P2DIR |=  BIT0+BIT1+BIT2;                 // P2.1 UCB0SOMI P2.2 UCB0SIMO

  // LED + Chip select
  P1OUT = 0;
  P1DIR = BIT0 + BIT1;
    
  UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
  UCA0CTL0 |= UCMST+UCSYNC+UCCKPL+UCMSB;    // 3-pin, 8-bit SPI master
                                            // Clock polarity high, MSB
  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  UCA0BR0 = 0x02;                           // /2
  UCA0BR1 = 0;                              //
  UCA0MCTL = 0;                             // No modulation
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  UCA0IE = UCRXIE ;                         // Enable USCI_A0 RX,TX interrupt

  P1OUT |= BIT1;                            // chip select for slave

  __delay_cycles(100);                      // Wait for slave to initialize
 
  MST_Data = 0x01;                          // Initialize data values
  SLV_Data = 0x00;                          //

  while (!(UCA0IFG&UCTXIFG));               // USCI_A0 TX buffer ready?
  UCA0TXBUF = MST_Data;                     // Transmit first character

  __bis_SR_register(LPM0_bits + GIE);       // CPU off, enable interrupts
}

#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
  volatile unsigned int i;

  switch(__even_in_range(UCA0IV,4))
  {
    case 0: break;                          // Vector 0 - no interrupt
    case 2:                                 // Vector 2 - RXIFG
      while (!(UCA0IFG&UCTXIFG));           // USCI_A0 TX buffer ready?

      if (UCA0RXBUF==SLV_Data)              // Test for correct character RX'd
        P1OUT |= 0x01;                      // If correct, light LED
      else
        P1OUT &= ~0x01;                     // If incorrect, clear LED

      MST_Data++;                           // Increment data
      SLV_Data++;
      UCA0TXBUF = MST_Data;                 // SET BREAKPOINT HERE! 
      __delay_cycles(500);
      break;
    case 4:                                 // Vector 4 - TXIFG      
      break;                          
    default: break;
  }
}


void Port_Mapping(void)
{
  // Disable Interrupts before altering Port Mapping registers
  __disable_interrupt();     
  // Enable Write-access to modify port mapping registers
  PMAPPWD = 0x02D52;                        
  
  #ifdef PORT_MAP_RECFG                    
  // Allow reconfiguration during runtime
  PMAPCTL = PMAPRECFG;                     
  #endif  
  
  P2MAP0 = PM_UCA0CLK;
  P2MAP1 = PM_UCA0SOMI;
  P2MAP2 = PM_UCA0SIMO;

  // Disable Write-Access to modify port mapping registers
  PMAPPWD = 0;                              
  #ifdef PORT_MAP_EINT
  __enable_interrupt();                     // Re-enable all interrupts
  #endif  
}
