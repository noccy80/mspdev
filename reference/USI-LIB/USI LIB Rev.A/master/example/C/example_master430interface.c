//******************************************************************************
//  MSP430F20xx Demo - I2C Master Transmitter and Receiver
//
//  Description: MSP430 I2C Master communicates with an MSP430 I2C Slave using
//  the USI module.The master device transmits 16 bytes of data to the slave  
//  device and reads it back. LED turns on if transmitted data = received data.
//  Slave MSP430 device must be enabled connected to the bus before master 
//  begins first transmit operation.
//
//  ACLK = n/a, MCLK = SMCLK = Calibrated 1MHz
//
//  ***THIS IS THE MASTER CODE***
//
//                  Slave                      Master
//          (example_slave430interface.s43)
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
//  Note: Internal pull-ups are used in this example for SDA & SCL
//        MSP430 Slave address = 0x48        
//
//  P. Thanigai
//  Texas Instruments Inc.
//  August 2007
//  Built with IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include  <msp430x20x2.h>

#include "USI_I2CMaster.h"

unsigned char TxData[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
unsigned char RxData[16];
int j,i;
int StatusCallback(unsigned char c);  
void main(void)
{
  WDTCTL = WDTPW+WDTHOLD;                   // disable Watchdog
  if (CALBC1_1MHZ ==0xFF || CALDCO_1MHZ == 0xFF)                                     
  {  
    while(1);                               // If calibration constants erased
                                            // do not load, trap CPU!!
  } 
  BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
  DCOCTL = CALDCO_1MHZ;
  P1DIR |= 0x01;
  P1OUT = 0;
  
  // Initialize USI module, clock ~ SMCLK/128 
  TI_USI_I2C_MasterInit(USIDIV_7+USISSEL_2+USICKPL, StatusCallback); 
  /* Acknowledge polling function - LED blinks continuously until slave device 
  provides an ACK 
 TI_USI_I2CSelect(unsigned char SlaveAddress) */
  while(TI_USI_I2CSelect(0x48))
  { 
    P1OUT ^= 0x01;                          // Toggle LED
    for (i = 0; i < 0x3000; i++);           // Delay
  }
  
  P1OUT =0;                                 // Slave acknowledged, LED off 
  /*Transmit data to the slave MSP430 device
   TI_USI_I2CWrite(SlaveAddress, Length, Multi, TxData) */
  __disable_interrupt();
  TI_USI_I2CWrite(0x48, 16, 0,TxData);
  __bis_SR_register(LPM0_bits + GIE);
  
  /*Read data from the slave MSP430 device
   TI_USI_I2CRead(SlaveAddress, Length, Multi, RxData) */
  __disable_interrupt();
  TI_USI_I2CRead(0x48, 16, 0,RxData); 
  __bis_SR_register(LPM0_bits + GIE);
  
  // check data for validity
  for (j = 0;j<16;j++)
  {
    if (RxData[j]!=j)
    {
      while(1);                             // data invalid   
    }
  }
  P1OUT |= 0x01;                            // data valid, LED on
  while(1);                                 // program ends here
}


int StatusCallback(unsigned char c)
{
 return TI_USI_EXIT_LPM;                       // exit active for next transfer
}
