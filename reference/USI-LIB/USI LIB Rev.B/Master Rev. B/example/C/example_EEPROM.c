//******************************************************************************
// MSP430F20xx Demo - USI I2C interface with AT24C02 EEPROM
// Description: USI module is used in I2C mode to transmit 10 bytes of 
// data to the AT24C02 EEPROM. The data is split into 2 streams of 8 and 2 
// bytes each so it can be prefixed by the page address of the EEPROM device. 
// Data is then continuously read from the EEPROM and stored in RAM. 
// LED turns on if  transmitted data = received data.
//   ACLK = n/a, MCLK = SMCLK = Calibrated 1MHz
//         
//               MSP430F20x2/3              AT24C02A EEPROM
//             -----------------          -----------------
//         /|\|              XIN|-     - | Vcc             |
//          | |                 |        |                 |
//          --|RST          XOUT|-       |                 |
//            |                 |        |                 |
//      LED <-|P1.0             |        |                 |
//            |                 |        |                 |
//            |         SDA/P1.7|------->|SDA              |
//            |         SCL/P1.6|------->|SCL          GND |
//
// Note: Internal pull-ups are used in this example for SDA & SCL
//       EEPROM slave address = 0x50  
//
//  P.Thanigai
//  Texas Instruments Inc.
//  August 2007
//  Built with IAR Embedded Workbench Version: 3.42A
//*****************************************************************************
#include<msp430x20x2.h>

#include "USI_I2CMaster.h"

unsigned char TxData0[] = {0,0,1,2,3,4,5,6,7};
unsigned char TxData1[] = {8,8,9};
unsigned char RxData[10];

int StatusCallback(unsigned char c);  

void main(void)
{
  int j,i;
  
  WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog
  if (CALBC1_1MHZ ==0xFF || CALDCO_1MHZ == 0xFF)                                     
  {  
    while(1);                               // If calibration constants erased
                                            // do not load, trap CPU!!
  } 
  BCSCTL1 = CALBC1_1MHZ;                    // Load DCO constants
  DCOCTL = CALDCO_1MHZ;
  P1DIR |= 0x01;                            // P1.0 as output (LED)
  P1OUT = 0x00;
  
 /* Initialize USI module, clock ~ SMCLK/128 */
 TI_USI_I2C_MasterInit(USIDIV_7+USISSEL_2+USICKPL, StatusCallback); 

  /* Acknowledge polling function - LED blinks continuously until slave device 
  provides an ACK 
 TI_USI_I2CSelect(unsigned char SlaveAddress) */
  while(TI_USI_I2CSelect(0x50))
  { 
    P1OUT ^= 0x01;                          // Toggle LED
    for (i = 0; i < 0x3000; i++);           // Delay
  }
  
  P1OUT =0;                                 // Slave acknowledged, LED off
  /* Transmit data to the EEPROM device, prefixed by page address 0x01 
   TI_USI_I2CWrite(SlaveAddress, Length, Multi, TxData) */
  __disable_interrupt();
  TI_USI_I2CWrite(0x50,9,0,TxData0);
  __bis_SR_register(LPM0_bits + GIE);
  
  /* Acknowledge polling function - loops continuously until slave device 
  provides an ACK */
  while(TI_USI_I2CSelect(0x50));              
  
  /* Transmit data to the EEPROM device, prefixed by page address 0x08 
  TI_USI_I2CWrite(SlaveAddress, Length, Multi, TxData)*/
  __disable_interrupt();
  TI_USI_I2CWrite(0x50, 3, 0, TxData1);
  __bis_SR_register(LPM0_bits + GIE); //*/
  
  /* Acknowledge polling function - loops continuously until slave device 
  provides an ACK */
  while(TI_USI_I2CSelect(0x50));
  
  /* Reset address counter of the EEPROM device by transmitting the page
  address to be read from (0x00) (Dummy write)
  TI_USI_I2CWrite(SlaveAddress, Length, Multi, TxData)*/
  __disable_interrupt();
  TI_USI_I2CWrite(0x50,1, 1,TxData0);
  __bis_SR_register(LPM0_bits + GIE);
   
  
  /* Read data from the EEPROM device, starting at page address 0x00
  TI_USI_I2CRead(SlaveAddress, Length, Multi, RxData)*/ 
  __disable_interrupt();
  TI_USI_I2CRead(0x50, 10, 1,RxData); 
  __bis_SR_register(LPM0_bits + GIE);
  
  /* This function can be used to end any open I2C transaction.
  Use only if I2C transaction was left open previously by setting stop
  condition bit =1 */
  TI_USI_I2CStop();                          

  // check data for validity
  for (j = 0;j<10;j++)
  {
    if (RxData[j]!=j)
    {
      while(1);                             // data invalid, stay in loop  
    }
  } 
  P1OUT |= 0x01;                            // data valid, LED on
  while(1);                                 // program ends here
} 

int StatusCallback(unsigned char c)
{
  return TI_USI_EXIT_LPM;                   // Exit active for next transfer
}
