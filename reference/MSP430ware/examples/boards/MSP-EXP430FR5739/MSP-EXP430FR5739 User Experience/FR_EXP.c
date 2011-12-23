/*******************************************************************************
 *
 * FR_EXP.c
 * User Experience Code for the MSP-EXP430FR5739
 * C Functions File
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/ 
 * 
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * Created: Version 1.0 04/13/2011
 *          Version 1.1 05/11/2011
 *          Version 1.2 08/31/2011
 *  
 ******************************************************************************/
#include "msp430fr5739.h"
#include "FR_EXP.h"

extern volatile unsigned int ADCResult;
extern volatile unsigned char active; 
extern volatile unsigned char ULP;
extern volatile unsigned char mode;
extern volatile unsigned char UserInput;

volatile unsigned char TX_Buffer[7] = {0,0,0,0,0,0,0};
volatile unsigned char ThreshRange[3]={0,0,0};
unsigned char counter =0;
unsigned int WriteCounter = 0;
unsigned int LEDCounter=0;
unsigned char ULPBreakSync =0;
unsigned int ModeAddress=0;
unsigned int CalValue =0;
unsigned int ADCTemp =0;
unsigned char temp = 0;


/**********************************************************************//**
 * @brief  Initializes system 
 * 
 * @param  none 
 *  
 * @return none
 *************************************************************************/
void SystemInit(void)
{
  // Startup clock system in max. DCO setting ~8MHz
  // This value is closer to 10MHz on untrimmed parts  
  CSCTL0_H = 0xA5;                          // Unlock register
  CSCTL1 |= DCOFSEL0 + DCOFSEL1;            // Set max. DCO setting
  CSCTL2 = SELA_1 + SELS_3 + SELM_3;        // set ACLK = vlo; MCLK = DCO
  CSCTL3 = DIVA_0 + DIVS_0 + DIVM_0;        // set all dividers 
  CSCTL0_H = 0x01;                          // Lock Register
  
  // Turn off temp. 
  REFCTL0 |= REFTCOFF; 
  REFCTL0 &= ~REFON;  
  
  // Enable switches
  // P4.0 and P4.1 are configured as switches
  // Port 4 has only two pins    
  P4OUT |= BIT0 +BIT1;                      // Configure pullup resistor  
  P4DIR &= ~(BIT0 + BIT1);                  // Direction = input
  P4REN |= BIT0 + BIT1;                     // Enable pullup resistor
  P4IES &= ~(BIT0+BIT1);                    // P4.0 Lo/Hi edge interrupt  
  P4IE = BIT0+BIT1;                         // P4.0 interrupt enabled
  P4IFG = 0;                                // P4 IFG cleared
    
  // Enable LEDs
  P3OUT &= ~(BIT6+BIT7+BIT5+BIT4);
  P3DIR |= BIT6+BIT7+BIT5+BIT4;
  PJOUT &= ~(BIT0+BIT1+BIT2+BIT3);
  PJDIR |= BIT0 +BIT1+BIT2+BIT3;
    
  // Terminate Unused GPIOs
  // P1.0 - P1.6 is unused
  P1OUT &= ~(BIT0 + BIT1 + BIT2 + BIT3 + BIT5 + BIT6 + BIT7);   
  P1DIR &= ~(BIT0 + BIT1 + BIT2 + BIT3 + BIT5 + BIT6 + BIT7); 
  P1REN |= (BIT0 + BIT1 + BIT2 + BIT3 + BIT5 + BIT6 + BIT7);   
  
  // P1.4 is used as input from NTC voltage divider
  // Set it to output low
  P1OUT &= ~BIT4;      
  P1DIR |= BIT4; 
  
  // P2.2 - P2.6 is unused
  P2OUT &= ~(BIT2 + BIT3 + BIT4 + BIT5 + BIT6);    
  P2DIR &= ~(BIT2 + BIT3 + BIT4 + BIT5 + BIT6); 
  P2REN |= (BIT2 + BIT3 + BIT4 + BIT5 + BIT6);   
  
  // Configure UART pins P2.0 & P2.1
  P2SEL1 |= BIT0 + BIT1;
  P2SEL0 &= ~(BIT0 + BIT1);
  
  // P2.7 is used to power the voltage divider for the NTC thermistor
  P2OUT &= ~BIT7;     
  P2DIR |= BIT7; 

  // P3.0,P3.1 and P3.2 are accelerometer inputs
  P3OUT &= ~(BIT0 + BIT1 + BIT2);   
  P3DIR &= ~(BIT0 + BIT1 + BIT2); 
  P3REN |= BIT0 + BIT1 + BIT2;
    
  // PJ.0,1,2,3 are used as LEDs
  // crystal pins for XT1 are unused
  PJOUT &= ~(BIT4+BIT5);  
  PJDIR &= ~(BIT4+BIT5);
  PJREN |= BIT4 + BIT5;  
}

/**********************************************************************//**
 * @brief  Startup LED sequence
 * 
 * @param  none 
 *  
 * @return none
 *************************************************************************/
void StartUpSequence(void) 
{
  unsigned char flag=4,up=1,counter = 0; 
  unsigned char LED_ArrayPJ[] = {0x01,0x02,0x04,0x08};
  unsigned char LED_ArrayP3[] = {0x80,0x40,0x20,0x10};

  while (counter <10) 
    {    
      counter++;
      PJOUT &= ~(BIT0 +BIT1+BIT2+BIT3);
      P3OUT &= ~(BIT4 +BIT5+BIT6+BIT7);    
      if(up)// from the outside - in
        {
          while(flag)
            {
              P3OUT = LED_ArrayP3[flag-1];
              PJOUT = LED_ArrayPJ[flag-1];
              LongDelay();               
              flag--;
            }
            up=0;
        }
      else
        {
          while(flag<4)
            {
              P3OUT = LED_ArrayP3[flag];
              PJOUT = LED_ArrayPJ[flag];
              LongDelay();        
              flag++;
            }
            up = 1;
          }
    } 
  
  // Exit Loop, Clear LEDs
  PJOUT &= ~(BIT0 +BIT1+BIT2+BIT3);
  P3OUT &= ~(BIT4 +BIT5+BIT6+BIT7);    
}

/**********************************************************************//**
 * @brief  Mode 1
 * 
 * @param  none
 *  
 * @return none
 *************************************************************************/
void Mode1(void)
{
  // Check FR_EXP.h for FRAM Scratch Pad locations
  // Setup FRAM Test storage pointer for Modes 1&2
  ModeAddress =  FRAM_TEST_START-MEM_UNIT;        
  // One time initialization of header and footer transmit package
  TX_Buffer[0] = 0xFA;    
  TX_Buffer[6] = 0xFE;  

  // Variable initialization
  active = 1;
  counter = 0;
  WriteCounter=0;
  LEDCounter = 0;
  ULPBreakSync = 0;
  while((mode == MAX_FRAM_WRITE) && (UserInput == 0))
    {
      // 512 byte FRAM Writes  
      // Update ModeAddress        
      if (ModeAddress < FRAM_TEST_END)   
              ModeAddress += MEM_UNIT;     
      else     
              ModeAddress = FRAM_TEST_START; 
      // Use updated mode address for FRAM Write        
      FRAM_Write(ModeAddress);
            
      WriteCounter++;
      LEDCounter++;
      // Every function call writes 512 bytes
      // Every 100KByte write, cycle the LED position                        
      if (LEDCounter > 199) 
        {
          LEDCounter = 0;
          counter++;
          if(counter == 8)
                counter = 0;
        }            
      // Check if LEDs need to be turned off to measure power
      if((ULP ==1) && (UserInput == 0))
        {
          // P3.4- P3.7 are set as output, low
          P3OUT &= ~(BIT4 + BIT5 + BIT6 + BIT7);   
	  P3DIR |= BIT4 + BIT5 + BIT6 + BIT7; 			    
	  
          // PJ.0,1,2,3 are set as output, low
          PJOUT &= ~(BIT0 + BIT1 + BIT2 + BIT3);  
          PJDIR |= BIT0 + BIT1 + BIT2 + BIT3;  
          // send this one time to allow the GUI to freeze the update 
          if(!(ULPBreakSync))
            {
              TXBreak(mode);                                         
              ULPBreakSync++;
            }
          }
      if((ULP ==0) && (UserInput == 0))
        {     
          ULPBreakSync =0;          
          // Update the LED sequence
          // only if no switch press occured (check again)
          LEDSequenceWrite(counter);
          // Send out UART Bytes every 100KB
          if (WriteCounter > 199)
            {
              WriteCounter = 0;
              // Transmit 7 Bytes
              // Prepare mode-specific data
              // Standard header and footer
              TX_Buffer[1] = 0x01; 
              TX_Buffer[2] = counter;
              TX_Buffer[3] = 0x00;
              TX_Buffer[4] = 0x00;
              TX_Buffer[5] = 0x00;
              TXData();                         
            }            
        }  
    }
    //end of while()loop
}

/**********************************************************************//**
 * @brief  Mode 2
 * 
 * @param  none
 *  
 * @return none
 *************************************************************************/
void Mode2(void)
{
  // Check FR_EXP.h for FRAM Scratch Pad locations
  // Setup FRAM Test storage pointer for Modes 1&2
  ModeAddress =  FRAM_TEST_START-MEM_UNIT;        
  // One time initialization of header and footer transmit package
  TX_Buffer[0] = 0xFA;    
  TX_Buffer[6] = 0xFE;  
  
  // Variable initialization
  active = 1;                
  counter = 0;
  WriteCounter =0;
  LEDCounter = 0;
  ULPBreakSync = 0;        
  
  // startup tick for ~12kBps writes
  // ACLK = VLO = ~12.5KHz
  // Every write = 512 bytes
  // # of bytes/sec = 512*1/(TACCRx/fvlo)
  TA0CCTL0 = CCIE;                // TACCR0 interrupt enabled
  TA0CCR0 = 350;
  TA0CTL = TASSEL_1 + MC_1;       // ACLK, up mode
  // setup write mode
  while((mode == SLOW_FRAM_WRITE) && (UserInput == 0))
    {
      // VLO stays on in LPM4
      __bis_SR_register(LPM4_bits + GIE);
      __no_operation();
      // wakeup to write a segment                        
      // Check status and Update MODE2_address        
      if (ModeAddress < FRAM_TEST_END)   
            ModeAddress += MEM_UNIT;     
      else 
        { // end of memory  - startover
            ModeAddress = FRAM_TEST_START;
        }
      // Use updated mode address for FRAM Write        
      FRAM_Write(ModeAddress); 
            
      WriteCounter++;
      LEDCounter++;           
      // Every 100KByte write, cycle the LED position  
      // 1 cycle = 512 bytes; 200 cycles = 100KB
      if (LEDCounter > 199)
        {
          LEDCounter = 0;
          counter++;
          if (counter == 8)
            counter = 0;
        }                                 
      if((ULP == 1) && (UserInput == 0))
        {
          // P3.4- P3.7 are set as output, low
	  P3OUT &= ~(BIT4 + BIT5 + BIT6 + BIT7);   
	  P3DIR |= BIT4 + BIT5 + BIT6 + BIT7; 	    
          // PJ.0,1,2,3 are set as output, low
          PJOUT &= ~(BIT0 + BIT1 + BIT2 + BIT3);  
          PJDIR |= BIT0 + BIT1 + BIT2 + BIT3;  
          
          // Transmit break packet for GUI freeze
          if(!(ULPBreakSync))
            {
              TXBreak(mode);                                         
              ULPBreakSync++;
            }
          
        }            
      if((ULP == 0) && (UserInput == 0))
        {
          ULPBreakSync =0;
          // Update the LED sequence & UART output
          // Only if S1 is not pressed; else quit
          LEDSequenceWrite(counter);
          // Send out UART bytes every 2KB
          // No. of bytes = 4 * 512 = 2KB
          if (WriteCounter>3)
            {
              WriteCounter = 0;
              // Transmit 7 Bytes
              // Prepare mode-specific data
              // Standard header and footer
              TX_Buffer[1] = 0x02; 
              TX_Buffer[2] = counter;
              TX_Buffer[3] = 0x00;
              TX_Buffer[4] = 0x00;
              TX_Buffer[5] = 0x00;
              TXData();                                         
            }              
        }     
    }
    // end of while() loop
    // Quitting; because user pressed a switch
    TA0CTL = 0;
    TA0CCTL0 = 0;
}

void Mode3(void)
{ 
  
  // One time initialization of header and footer transmit package
  TX_Buffer[0] = 0xFA;    
  TX_Buffer[6] = 0xFE;  
        
  // variable initialization
  active = 1;    
  ADCTemp = 0;
  temp = 0;
  WriteCounter = 0;   
  ULPBreakSync = 0;
  counter = 0;
  
  // One time setup and calibration
  SetupAccel();
  CalValue = CalibrateADC();
  while ((mode == ACCEL_MEAS) && (UserInput == 0))
    {  
      // Take 1 ADC Sample
      TakeADCMeas();
      if (ADCResult >= CalValue)        
        {
          temp = DOWN;
          ADCTemp = ADCResult - CalValue;
        }
      else
        {
          temp = UP;
          ADCTemp = CalValue - ADCResult; 
        }                                       
      if((ULP==1) && (UserInput == 0))
        {
          // P3.4- P3.7 are set as output, low
          P3OUT &= ~(BIT4 + BIT5 + BIT6 + BIT7);   
          P3DIR |= BIT4 + BIT5 + BIT6 + BIT7; 	    
          // PJ.0,1,2,3 are set as output, low
          PJOUT &= ~(BIT0 + BIT1 + BIT2 + BIT3);  
          PJDIR |= BIT0 + BIT1 + BIT2 + BIT3;
          // Transmit break packet for GUI freeze
          if(!(ULPBreakSync))
            {
              TXBreak(mode);                                         
              ULPBreakSync++;
            }              
        }            
      if((ULP==0) && (UserInput == 0))
        {
          ULPBreakSync = 0;
          WriteCounter++;
          if(WriteCounter > 300)
            {
              LEDSequence(ADCTemp,temp);              
              // Every 300 samples   	
              // Transmit 7 Bytes
              // Prepare mode-specific data
              // Standard header and footer
              WriteCounter = 0;
              TX_Buffer[1] = 0x03; 
              TX_Buffer[2] = counter;
              TX_Buffer[3] = 0x00;
              TX_Buffer[4] = 0x00;
              TX_Buffer[5] = 0x00;
              TXData();                                     
            }
        }
     }
    // end while() loop
    // turn off Accelerometer for low power
    ShutDownAccel();
}

void Mode4(void)
{
  // One time initialization of header and footer transmit package
  TX_Buffer[0] = 0xFA;    
  TX_Buffer[6] = 0xFE;  
        
  // variable initialization
  ADCTemp = 0;
  temp = 0;
  WriteCounter = 0;
  active = 1;
  ULPBreakSync = 0;
  counter = 0;
  
  // One time setup and calibration          
  SetupThermistor();
  CalValue = CalibrateADC(); 
  while((mode == TEMP_MEAS) && (UserInput == 0))
    {
      // Take 1 ADC Sample
      TakeADCMeas();
      if (ADCResult >= CalValue)        
        {
          temp = DOWN;
          ADCTemp = ADCResult - CalValue;
        }
      else
        {
          temp = UP;
          ADCTemp = CalValue - ADCResult; 
        }                         
          
      if((ULP==1) && (UserInput == 0))
        {
          // P3.4- P3.7 are set as output, low
          P3OUT &= ~(BIT4 + BIT5 + BIT6 + BIT7);   
	  P3DIR |= BIT4 + BIT5 + BIT6 + BIT7; 	    
          // PJ.0,1,2,3 are set as output, low
          PJOUT &= ~(BIT0 + BIT1 + BIT2 + BIT3);  
	  PJDIR |= BIT0 + BIT1 + BIT2 + BIT3;  
          // Transmit break packet for GUI freeze
          if(!(ULPBreakSync))
            {
              TXBreak(mode);              
              ULPBreakSync++;
            }              
          
        }            
      if((ULP==0) && (UserInput == 0))
        {
          ULPBreakSync = 0;
          WriteCounter++;            
          if(WriteCounter > 300)
            {
              LEDSequence(ADCTemp,temp);
              // Every 300 samples   	
              // Transmit 7 Bytes
              // Prepare mode-specific data
              // Standard header and footer
              WriteCounter = 0;
              TX_Buffer[1] = 0x04; 
              TX_Buffer[2] = counter;
              TX_Buffer[3] = 0x00;
              TX_Buffer[4] = 0x00;
              TX_Buffer[5] = 0x00;
              TXData();                                     
          } 
        }
      }
    // turn off Thermistor bridge for low power      
    ShutDownTherm();


}

/**********************************************************************//**
 * @brief  Performs 512 byte FRAM Write
 * 
 * @param  StartAddress: For FRAM Write
 *  
 * @return none
 *************************************************************************/
void FRAM_Write(unsigned int StartAddress)
{
  unsigned long *FRAM_write_ptr; 
  unsigned long data = 0x12345678;
  unsigned int i=0;
  
  //Incase FRAM Write Address is corrupted, exit loop
  if((StartAddress >= FRAM_TEST_START) && (StartAddress < FRAM_TEST_END))
  {
  	// Setup FRAM pointer
  	FRAM_write_ptr = (unsigned long *) StartAddress;
  	
  	// Write 128 * 4 = 512 bytes
  	for ( i= 0; i<128; i++)
  	  {
    	*FRAM_write_ptr++ = data;
      }
  }
}

/**********************************************************************//**
 * @brief  LED Toggle Sequence for FRAM Writes
 * 
 * @param  
 * sequence flag
 *
 * @return none
 *************************************************************************/
void LEDSequenceWrite(unsigned char flag)
{
  // The LED sequence fills p based on flag value
  unsigned char LED_ArrayPJ[] = {0x08,0x0C,0x0E,0x0F};
  unsigned char LED_ArrayP3[] = {0x80,0xC0,0xE0,0xF0};
   
  // LED Sequencing for FRAM writes  
  if (flag <4)
    {
      PJOUT &= ~(BIT0 +BIT1+BIT2+BIT3);
      P3OUT &= ~(BIT4 +BIT5+BIT6+BIT7);     
      P3OUT |= LED_ArrayP3[flag];            
    }
  else
    {
      PJOUT &= ~(BIT0 +BIT1+BIT2+BIT3);                  
      P3OUT &= ~(BIT4 +BIT5+BIT6+BIT7);
      // Keep the entire P3 array on
      P3OUT |= LED_ArrayP3[3];      
      PJOUT |= LED_ArrayPJ[flag-4];
    }           
}

/**********************************************************************//**
 * @brief  Calibrate thermistor or accelerometer
 * 
 * @param  none 
 *  
 * @return none
 *************************************************************************/
unsigned int CalibrateADC(void)
{
  unsigned char CalibCounter =0;
  unsigned int Value = 0;

  // Disable interrupts & user input during calibration
  DisableSwitches();            
  while(CalibCounter <50)
    {
      P3OUT ^= BIT4;
      CalibCounter++;
      while (ADC10CTL1 & BUSY); 
      ADC10CTL0 |= ADC10ENC | ADC10SC ;       // Start conversion 
      __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
      __no_operation(); 
      Value += ADCResult;
    }
    Value = Value/50;
    // Reenable switches after calibration
    EnableSwitches();
    return Value;
}

/**********************************************************************//**
 * @brief  Take ADC Measurement
 * 
 * @param  none 
 *  
 * @return none
 *************************************************************************/
void TakeADCMeas(void)
{  
  while (ADC10CTL1 & BUSY); 
  ADC10CTL0 |= ADC10ENC | ADC10SC ;       // Start conversion 
  __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
  __no_operation();                       // For debug only
}

/**********************************************************************//**
 * @brief  Initializes Accelerometer
 * 
 * @param  none 
 *  
 * @return none
 *************************************************************************/
void SetupAccel(void)
{  
  //Setup  accelerometer
  // ~20KHz sampling
  //Configure GPIO
  ACC_PORT_SEL0 |= ACC_X_PIN + ACC_Y_PIN + ACC_Z_PIN;    //Enable A/D channel inputs
  ACC_PORT_SEL1 |= ACC_X_PIN + ACC_Y_PIN + ACC_Z_PIN;
  ACC_PORT_DIR &= ~(ACC_X_PIN + ACC_Y_PIN + ACC_Z_PIN);
  ACC_PWR_PORT_DIR |= ACC_PWR_PIN;              //Enable ACC_POWER
  ACC_PWR_PORT_OUT |= ACC_PWR_PIN;

  // Allow the accelerometer to settle before sampling any data 
  __delay_cycles(200000);   
  
  //Single channel, once, 
  ADC10CTL0 &= ~ADC10ENC;                        // Ensure ENC is clear
  ADC10CTL0 = ADC10ON + ADC10SHT_5;  
  ADC10CTL1 = ADC10SHS_0 + ADC10SHP + ADC10CONSEQ_0 + ADC10SSEL_0;  
  ADC10CTL2 = ADC10RES;    
  ADC10MCTL0 = ADC10SREF_0 + ADC10INCH_12;
  ADC10IV = 0x00;                          // Clear all ADC12 channel int flags  
  ADC10IE |= ADC10IE0;
  
  // Setup Thresholds for relative difference in accelerometer measurements
  ThreshRange[0]=25;
  ThreshRange[1]=50;
  ThreshRange[2]=75;
}

/**********************************************************************//**
 * @brief  ShutDownAccel
 * 
 * @param  none 
 *  
 * @return none
 *************************************************************************/
void ShutDownAccel(void)
{  
  ACC_PORT_SEL0 &= ~(ACC_X_PIN + ACC_Y_PIN + ACC_Z_PIN);
  ACC_PORT_SEL1 &= ~(ACC_X_PIN + ACC_Y_PIN + ACC_Z_PIN);
  ACC_PORT_DIR &= ~(ACC_X_PIN + ACC_Y_PIN + ACC_Z_PIN);
  ACC_PWR_PORT_DIR &= ~ACC_PWR_PIN;            
  ACC_PWR_PORT_OUT &= ~ACC_PWR_PIN;
  ADC10CTL0 &= ~(ADC10ENC + ADC10ON);
  ADC10IE &= ~ADC10IE0;
  ADC10IFG = 0;
}

/**********************************************************************//**
 * @brief  Setup thermistor
 * 
 * @param  none 
 *  
 * @return none
 *************************************************************************/
void SetupThermistor(void)
{
  // ~16KHz sampling
  //Turn on Power
  P2DIR |= BIT7;
  P2OUT |= BIT7;
  
  // Configure ADC
  P1SEL1 |= BIT4;  
  P1SEL0 |= BIT4; 
  
  // Allow for settling delay 
  __delay_cycles(50000);
  
  // Configure ADC
  ADC10CTL0 &= ~ADC10ENC; 
  ADC10CTL0 = ADC10SHT_7 + ADC10ON;        // ADC10ON, S&H=192 ADC clks
  // ADCCLK = MODOSC = 5MHz
  ADC10CTL1 = ADC10SHS_0 + ADC10SHP + ADC10SSEL_0; 
  ADC10CTL2 = ADC10RES;                    // 10-bit conversion results
  ADC10MCTL0 = ADC10INCH_4;                // A4 ADC input select; Vref=AVCC
  ADC10IE = ADC10IE0;                      // Enable ADC conv complete interrupt
  
  // Setup Thresholds for relative difference in Thermistor measurements
  ThreshRange[0]=15;
  ThreshRange[1]=25;
  ThreshRange[2]=45;
}

/**********************************************************************//**
 * @brief  ShutDownTherm
 * 
 * @param  none 
 *  
 * @return none
 *************************************************************************/
void ShutDownTherm(void)
{
  // Turn off Vcc
  P2DIR &= ~BIT7;
  P2OUT &= ~BIT7;
  
  // Turn off ADC Channel
  P1SEL1 &= ~BIT4;  
  P1SEL0 &= ~BIT4; 
 
 // Turn off ADC
  ADC10CTL0 &= ~(ADC10ENC + ADC10ON);
  ADC10IE &= ~ADC10IE0;
  ADC10IFG = 0;    
}

/**********************************************************************//**
 * @brief  LED Toggle Sequence
 * 
 * @param  
 * DiffValue Difference between calibrated and current measurement
 * temp Direction of difference (positive or negative)
 * @return none
 *************************************************************************/
void LEDSequence(unsigned int DiffValue, unsigned char temp)
{  
  // The same scale is used for cold & hot and tilt up/down
  // only the thresholds are different
  P3OUT |= BIT4;                            // Light up the middle LEDs
  PJOUT |= BIT3;
  
  if(DiffValue < ThreshRange[0])            // Very close to CAL value
    {
      P3OUT |= BIT4;                          
      PJOUT |= BIT3;
      PJOUT &= ~(BIT0+BIT1+BIT2);
      P3OUT &= ~(BIT7+BIT6+BIT5);
      counter = 0x34;
    }
  
  if ((DiffValue >=ThreshRange[0]) && (DiffValue < ThreshRange[1]))
    {
      // Light up one LED  	
      if(temp == UP)                        // Tilt up, temp up
        {
          PJOUT |= BIT2;
          PJOUT &= ~(BIT1+BIT0);
          P3OUT &= ~(BIT7+BIT6+BIT5);
          counter = 5;
        }
      else                                  // Tilt down, temp down
        {
          PJOUT &= ~(BIT0+BIT1+BIT2);
          P3OUT |= BIT5; 
          P3OUT &= ~(BIT6+BIT7);
          counter = 2;
        }
    }
  if ((DiffValue >= ThreshRange[1]) && (DiffValue < ThreshRange[2]))
    {
      // Light up two LEDs  	    
      if(temp == UP)                        // Tilt up 2, temp up 2
        {
          PJOUT |= BIT2 + BIT1;
          PJOUT &= ~(BIT0);
          P3OUT &= ~(BIT7+BIT6+BIT5);
          counter = 6;
        }
      else                                  // Tilt down 2, temp down 2
        {
          PJOUT &= ~(BIT2+BIT1+BIT0);
          P3OUT |= BIT5 + BIT6; 
          P3OUT &= ~(BIT7);
          counter = 1;
        }
    }
  if (DiffValue > ThreshRange[2])
    {
      // Light up three LEDs  	        	
      if(temp == UP)                        // Tilt up 3, temp up 3
        {
          PJOUT |= BIT2 + BIT1 + BIT0;
          P3OUT &= ~(BIT7+BIT6+BIT5);
          counter = 7;
        }
      else                                  // Tilt down 3, temp down 3
        {
          P3OUT |= BIT5+BIT6+BIT7;
          PJOUT &= ~(BIT2+BIT1+BIT0);
          counter = 0;
        }
    }
}

/**********************************************************************//**
 * @brief  Disables Switches
 * 
 * @param  none 
 *  
 * @return none
 *************************************************************************/
void DisableSwitches(void)
{
  // disable switches
  P4IFG = 0;                                // P4 IFG cleared    
  P4IE &= ~(BIT0+BIT1);                     // P4.0 interrupt disabled
  P4IFG = 0;                                // P4 IFG cleared  
}

/**********************************************************************//**
 * @brief  Enables Switches 
 * 
 * @param  none 
 *  
 * @return none
 *************************************************************************/
void EnableSwitches(void)

{
  P4IFG = 0;                                // P4 IFG cleared  
  P4IE = BIT0+BIT1;                         // P4.0 interrupt enabled
}

/**********************************************************************//**
 * @brief  Sets up the Timer A1 as debounce timer 
 * 
 * @param  delay: pass 0/1 to decide between 250 and 750 ms debounce time 
 *  
 * @return none
 *************************************************************************/
void StartDebounceTimer(unsigned char delay)

{  
  // default delay = 0
  // Debounce time = 1500* 1/8000 = ~200ms
  TA1CCTL0 = CCIE;                          // TACCR0 interrupt enabled
  if(delay)
  	TA1CCR0 = 750;
  else
    TA1CCR0 = 1500;
  TA1CTL = TASSEL_1 + MC_1;                 // ACLK, up mode    
}

/**********************************************************************//**
 * @brief  Long Delay
 * 
 * @param  none 
 *  
 * @return none
 *************************************************************************/
void LongDelay()
{
  __delay_cycles(250000);
  __no_operation();
}

/**********************************************************************//**
 * @brief  Transmit 7 bytes
 * 
 * @param  none 
 *  
 * @return none
 *************************************************************************/
void TXData()
{
  unsigned char counter = 0;
	
  // Configure UART 0
  UCA0CTL1 |= UCSWRST; 
  UCA0CTL1 = UCSSEL_2;                      // Set SMCLK as UCLk 
  UCA0BR0 = 52 ;                              // 9600 baud
  // 8000000/(9600*16) - INT(8000000/(9600*16))=0.083
  UCA0BR1 = 0; 
  // UCBRFx = 1, UCBRSx = 0x49, UCOS16 = 1 (Refer User Guide)
  UCA0MCTLW = 0x4911 ;                      
                                            
  UCA0CTL1 &= ~UCSWRST;                     // release from reset
  while(counter<7)
  {
    while (!(UCA0IFG&UCTXIFG));             // USCI_A0 TX buffer ready?
    UCA0TXBUF = TX_Buffer[counter];
    counter++;
  }	
}


/**********************************************************************//**
 * @brief  Transmit the break sequence
 * 
 * @param  mode at the time of ULP switch press
 *  
 * @return none
 *************************************************************************/
void TXBreak(unsigned char ModeSelect)
{
  // One time initialization of header and footer transmit package
  TX_Buffer[0] = 0xFA;    
  TX_Buffer[6] = 0xFE;  
  
  // Prepare the reset sequence
  TX_Buffer[1] = 0x55;
  TX_Buffer[2] = 0x55;
  TX_Buffer[3] = 0x55;
  TX_Buffer[4] = 0x55;
  TX_Buffer[5] = ModeSelect/2;
  
  TXData();

}   

