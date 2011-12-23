//******************************************************************************
//  MSP430x26x Demo - USCI_B0 to USCI_B1 I2C RX and TX single bytes
//
//  Description: This demo connects both USCI_B channels on one MSP430 via the 
//  I2C bus. The master (B0) reads from the slave(B1), then the slave (B1) reads
//  from the master (B0). 
//  ACLK = n/a, MCLK = SMCLK = BRCLK = default DCO = ~1.045MHz
//
//                                /|\              /|\
//               MSP430F261x      10k              10k     
//             -----------------   |                |
//           -|XIN  P5.1/UCB0SDA|<-|---+----|       |
//            |                 |           |       |
//           -|XOUT             |           |       |
//            |     P5.2/UCB0SCL|<-+------- | ------|
//            |                 |           |       |
//            |     P3.1/UCB0SDA|<----------|       |
//            |                 |                   |
//            |                 |                   |
//            |     P3.2/UCB0SCL|<------------------|
//            |                 |        
//
//  R. B. Elliott / H. Grewal
//  Texas Instruments Inc.
//  January 2008
//  Built with IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include "msp430x26x.h"


unsigned char RXData, Master_RX, Slave_RX, TXByteCtr = 0;

void Slave_TX_to_RX_Master(void);
void Master_TX_to_RX_Slave(void);
void SlaveUSCIB1TX (void);
void SlaveUSCIB1RX (void);
void MasterUSCIB0TX (void);
void MasterUSCIB0RX (void);

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

  P3SEL |= 0x06;                            // Assign I2C pins to USCI_B0
  P5SEL |= 0x06;                            // Assign I2C pins to USCI_B1
  
   Master_TX_to_RX_Slave();
 __bic_SR_register(GIE);
  
  Slave_TX_to_RX_Master();
  __bic_SR_register(GIE);
  
 Master_TX_to_RX_Slave();
 __bic_SR_register(GIE);
    
while(1);                                   // SET BREAKPOINT HERE

}

// USCI_B0 Data ISR
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
  if (Master_RX == 1)
  {
  RXData = UCB0RXBUF;                       // Get RX data
  __bic_SR_register_on_exit(CPUOFF);        // Exit LPM0
  }
  else{
    if (TXByteCtr)                          // Check TX byte counter
  {
    UCB0TXBUF = 0x22;                       // Load TX buffer
    TXByteCtr--;                            // Decrement TX byte counter
  }
  else
  {
    UCB0CTL1 |= UCTXSTP;                    // I2C stop condition
    IFG2 &= ~UCB0TXIFG;                     // Clear USCI_B0 TX int flag
    __bic_SR_register_on_exit(CPUOFF);      // Exit LPM0
  }
  }
}

// USCI_B1 Data ISR
#pragma vector = USCIAB1TX_VECTOR
__interrupt void USCIAB1TX_ISR(void)
{
  if (Slave_RX == 1) RXData = UCB1RXBUF;    //for slave RX
  else  UCB1TXBUF = 0x55;                   // TX data
  //__bic_SR_register_on_exit(CPUOFF);        
}

// USCI_B1 State ISR
#pragma vector = USCIAB1RX_VECTOR
__interrupt void USCIAB1RX_ISR(void)
{
  UCB1STAT &= ~(UCSTPIFG + UCSTTIFG);       // Clear start condition int flag

}

void Slave_TX_to_RX_Master(void){
  SlaveUSCIB1TX();                          // Set up USCI B1 as slave TX
  MasterUSCIB0RX();                         // Set up USCI B1 as slave TX

   __bis_SR_register(GIE);
  
    while (UCB0CTL1 & UCTXSTP);             // Ensure stop condition got sent
    UCB0CTL1 |= UCTXSTT;                    // I2C start condition
    while (UCB0CTL1 & UCTXSTT);             // Start condition sent?
    UCB0CTL1 |= UCTXSTP;                    // I2C stop condition
    __bis_SR_register(CPUOFF + GIE);        // Enter LPM0 w/ interrupts
    while (UCB0CTL1 & UCTXSTP);             // Ensure stop condition got sent
  
}

void Master_TX_to_RX_Slave(void){

    SlaveUSCIB1RX();
    MasterUSCIB0TX();
     
    __bis_SR_register(GIE);
    TXByteCtr = 1;                          // Load TX byte counter
    while (UCB0CTL1 & UCTXSTP);             // Ensure stop condition got sent
    UCB0CTL1 |= UCTR + UCTXSTT;             // I2C TX, start condition
    __bis_SR_register(CPUOFF + GIE);        // Enter LPM0 w/ interrupts
                                            // Remain in LPM0 until dat is TX'ed
    while (UCB0CTL1 & UCTXSTP);             // Ensure stop condition got sent

}

void SlaveUSCIB1TX (void){
  
  UC1IE &= ~UCB1RXIE;                       // Disable RX interrupt
  UCB1CTL1 |= UCSWRST;                      // Enable SW reset 
  UCB1CTL0 = UCMODE_3 + UCSYNC;             // I2C Slave, synchronous mode
  UCB1I2COA = 0x48;                         // Own Address is 048h
  UCB1CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
  Slave_RX = 0;
  UCB1I2CIE  |= UCSTPIE + UCSTTIE;          // Enable STT and STP interrupt
  UC1IE |= UCB1TXIE;                        // Enable TX interrupt
}

void SlaveUSCIB1RX (void){
  UCB1I2CIE &= ~(UCSTPIE + UCSTTIE);        // Disable STT and STP interrupt
  UC1IE &= ~UCB1TXIE;                       // Disable TX interrupt
  
  UCB1CTL1 |= UCSWRST;                      // Enable SW reset
  UCB1CTL0 = UCMODE_3 + UCSYNC;             // I2C Slave, synchronous mode
  UCB1I2COA = 0x48;                         // Own Address is 048h
  UCB1CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
  Slave_RX = 1;
  UC1IE |= UCB1RXIE;                        // Enable RX interrupt
}

void MasterUSCIB0TX (void){
  
  IE2 &= ~UCB0RXIE;                         // disable RX interrupt
  UCB0CTL1 |= UCSWRST;                      // Enable SW reset
  UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
  UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
  UCB0BR0 = 12;                             // fSCL = SMCLK/12 = ~100kHz
  UCB0BR1 = 0;
  UCB0I2CSA = 0x48;                         // Slave Address is 048h
  UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
  Master_RX = 0;
  IE2 |= UCB0TXIE;                          // Enable TX interrupt
}  


void MasterUSCIB0RX (void){
  IE2 &= ~UCB0TXIE;                         // disable TX interrupt
  UCB0CTL1 |= UCSWRST;                      // Enable SW reset
  UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
  UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
  UCB0BR0 = 12;                             // fSCL = SMCLK/12 = ~100kHz
  UCB0BR1 = 0;
  UCB0I2CSA = 0x048;                        // Slave Address is 048h
  UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
  Master_RX = 1;
  IE2 |= UCB0RXIE;                          // Enable RX interrupt
}


