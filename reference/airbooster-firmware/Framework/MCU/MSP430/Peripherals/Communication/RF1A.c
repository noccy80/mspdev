/**
 *  @file RF1A.c
 *
 *  @brief MSP430 RF1A module peripheral interface definitions.
 *
 *  @author   BB
 *
 *  @version  1.0
 *
 *  @remarks  Rev. 1.0, Initial setup [BB]
 */
#include "RF1A.h"

// RF1A MODULE
////////////////////////////////////////////////////////////////////////////////
#if defined(__MCU_MSP430_RF1A)

// PUBLIC INTERFACE
////////////////////////////////////////////////////////////////////////////////

/**
 *  @details
 */
uint8_t Strobe(uint8_t strobe)
{
  uint8_t statusByte = 0;
  uint16_t  gdo_state;
  
  // Check for valid strobe command 
  if((strobe == 0xBD) || ((strobe >= RF_SRES) && (strobe <= RF_SNOP)))
  {
    // Clear the Status read flag 
    RF1AIFCTL1 &= ~(RFSTATIFG);    
    
    // Wait for radio to be ready for next instruction
    while( !(RF1AIFCTL1 & RFINSTRIFG));
    
    // Write the strobe instruction
    if ((strobe > RF_SRES) && (strobe < RF_SNOP))
    {
      gdo_state = ReadSingleReg(IOCFG2);    // buffer IOCFG2 state
      WriteSingleReg(IOCFG2, 0x29);         // chip-ready to GDO2
      
      RF1AINSTRB = strobe; 
      if ( (RF1AIN&0x04)== 0x04 )           // chip at sleep mode
      {
        if ( (strobe == RF_SXOFF) || (strobe == RF_SPWD) || (strobe == RF_SWOR) ) { }
        else  	
        {
          while ((RF1AIN&0x04)== 0x04);     // chip-ready ?
          // Delay for ~810usec at 1.05MHz CPU clock, see erratum RF1A7
          __delay_cycles(850);	            
        }
      }
      WriteSingleReg(IOCFG2, gdo_state);    // restore IOCFG2 setting
    
      while( !(RF1AIFCTL1 & RFSTATIFG) );
    }
    else		                    // chip active mode (SRES)
    {	
      RF1AINSTRB = strobe; 	   
    }
    statusByte = RF1ASTATB;
  }
  return statusByte;
}

/**
 *  @details
 */
uint8_t ReadSingleReg(uint8_t addr)
{
  uint8_t data_out;
  
  // Check for valid configuration register address, 0x3E refers to PATABLE 
  if ((addr <= 0x2E) || (addr == 0x3E))
    // Send address + Instruction + 1 dummy byte (auto-read)
    RF1AINSTR1B = (addr | RF_SNGLREGRD);    
  else
    // Send address + Instruction + 1 dummy byte (auto-read)
    RF1AINSTR1B = (addr | RF_STATREGRD);    
  
  while (!(RF1AIFCTL1 & RFDOUTIFG) );
  data_out = RF1ADOUTB;                    // Read data and clears the RFDOUTIFG

  return data_out;
}

/**
 *  @details
 */
void WriteSingleReg(uint8_t addr, uint8_t value)
{   
  while (!(RF1AIFCTL1 & RFINSTRIFG));       // Wait for the Radio to be ready for next instruction
  RF1AINSTRB = (addr | RF_SNGLREGWR);	    // Send address + Instruction

  RF1ADINB = value; 			    // Write data in 

  __no_operation(); 
}
        
/**
 *  @details
 */
void ReadBurstReg(uint8_t addr, uint8_t * buffer, uint8_t count)
{
  uint16_t i;
  if(count > 0)
  {
    while (!(RF1AIFCTL1 & RFINSTRIFG));       // Wait for INSTRIFG
    RF1AINSTR1B = (addr | RF_REGRD);          // Send addr of first conf. reg. to be read 
                                              // ... and the burst-register read instruction
    for (i = 0; i < (count-1); i++)
    {
      while (!(RFDOUTIFG&RF1AIFCTL1));        // Wait for the Radio Core to update the RF1ADOUTB reg
      buffer[i] = RF1ADOUT1B;                 // Read DOUT from Radio Core + clears RFDOUTIFG
                                              // Also initiates auo-read for next DOUT byte
    }
    buffer[count-1] = RF1ADOUT0B;             // Store the last DOUT from Radio Core  
  }
}  

/**
 *  @details
 */
void WriteBurstReg(uint8_t addr, uint8_t * buffer, uint8_t count)
{  
  uint8_t i;

  if(count > 0)
  {
    while (!(RF1AIFCTL1 & RFINSTRIFG));       // Wait for the Radio to be ready for next instruction
    RF1AINSTRW = ((addr | RF_REGWR)<<8 ) + buffer[0]; // Send address + Instruction
  
    for (i = 1; i < count; i++)
    {
      RF1ADINB = buffer[i];                   // Send data
      while (!(RFDINIFG & RF1AIFCTL1));       // Wait for TX to finish
    } 
    i = RF1ADOUTB;                            // Reset RFDOUTIFG flag which contains status byte  
  }
}

/**
 *  @details
 */
void ResetRadioCore()
{
  Strobe(RF_SRES);                          // Reset the Radio Core
  Strobe(RF_SNOP);                          // Reset Radio Pointer
}

/**
 *  @details
 */
void WriteSinglePATable(uint8_t value)
{
  while( !(RF1AIFCTL1 & RFINSTRIFG));
  RF1AINSTRW = 0x3E00 + value;              // PA Table single write
  
  while( !(RF1AIFCTL1 & RFINSTRIFG));
  RF1AINSTRB = RF_SNOP;                     // reset PA_Table pointer
}

/**
 *  @details
 */
void WriteBurstPATable(uint8_t * buffer, uint8_t count)
{
  volatile int8_t i = 0; 
  
  while( !(RF1AIFCTL1 & RFINSTRIFG));
  RF1AINSTRW = 0x7E00 + buffer[i];          // PA Table burst write   

  for (i = 1; i < count; i++)
  {
    RF1ADINB = buffer[i];                   // Send data
    while (!(RFDINIFG & RF1AIFCTL1));       // Wait for TX to finish
  } 
  i = RF1ADOUTB;                            // Reset RFDOUTIFG flag which contains status byte

  while( !(RF1AIFCTL1 & RFINSTRIFG));
  RF1AINSTRB = RF_SNOP;                     // reset PA Table pointer
}

// PRIVATE INTERFACE
////////////////////////////////////////////////////////////////////////////////

// NOTE: Private interface definitions go here.

// CALLBACK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

// NOTE: Callback function definitions go here.

// INTERRUPT SERVICE ROUTINES
////////////////////////////////////////////////////////////////////////////////

// NOTE: Interrupt service routine definitions go here.

#endif  // RF1A MODULE