//******************************************************************************
//  MSP430F20xx Demo - I2C Slave Transmitter and Receiver
//
//  Description: MSP430 I2C Slave communicates with MSP430 I2C Master using
//  the USI module. 
//  The slave device receives 16 bytes of data from the master device and  
// transmits it back. LED turns on when start condition is detected. Received
// data can be viewed in flash at location 0x1000.
//  ACLK = n/a, MCLK = SMCLK = Calibrated 1MHz
//
//  ***THIS IS THE SLAVE CODE***
//
//                  Slave                      Master
//                                     (example_master430interface.s43)
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
//
//  P. Thanigai
//  Texas Instruments Inc.
//  August 2007
//  Built with IAR Embedded Workbench Version: 3.42A
//******************************************************************************
#include  <msp430x20x2.h>

#include "USI_I2CSlave.h"

int RxCallback(unsigned char);
int TxCallback(int*);
void StartCallback();
unsigned char OwnAddress =0x48;
int ptr_rx = 0x1000;
int ptr_tx = 0x1000;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog
  if (CALBC1_1MHZ ==0xFF || CALDCO_1MHZ == 0xFF)                                     
  {  
    while(1);                               // If calibration constants erased
                                            // do not load, trap CPU!!
  }   
  BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
  DCOCTL = CALDCO_1MHZ;          
  P1DIR |= 0x01;                            // Enable P1.0 as output 
  P1OUT = 0;
  FCTL1 = FWKEY + ERASE;                    // Enable flash erase
  FCTL2 = FWKEY + FSSEL_2 + FN0;            // Flash timing setup
  FCTL3 = FWKEY;                            // Disable lock 
  *(unsigned int *)0x1000 = 0;              // Dummy write to erase flash
  FCTL1 = FWKEY;
  FCTL3 = FWKEY+LOCK;                       // Diasble flash write
  
  /* Initialize USI module in Slave mode */  
  TI_USI_I2C_SlaveInit(OwnAddress,StartCallback,RxCallback,TxCallback);
   while(1)
    {
      __disable_interrupt();
      __bis_SR_register(LPM4_bits + GIE);     // enter LPM, enable interrupts
      __no_operation();
    }   
}

void StartCallback()
{
  P1OUT |= 0x01;                              // start received, turn LED on 
}

int RxCallback(unsigned char RxData)
{
  // Received data byte is stored in flash
  FCTL3 = FWKEY;
  FCTL1 = FWKEY+ WRT;                       // Enable flash write
  *(unsigned char*)ptr_rx = RxData;          // Write data to flash
  ptr_rx++;                                 // Increment Rx pointer
  FCTL1 = FWKEY;                            // Disable flash write
  FCTL3 = FWKEY + LOCK; 
  return TI_USI_STAY_LPM ;                  // stay in LPM
}

int TxCallback(int* TxDataPtr)
{
  // Data byte to be transmitted is passed through reference to the library
 *(unsigned char*)TxDataPtr = *(unsigned char*)ptr_tx;
  ptr_tx++;                                 // Increment tx pointer
  return TI_USI_STAY_LPM ;                  // stay in LPM
}
