#include "flash.h"

void flash_read(void) {

  char *p;
  p = (char *)0x1001;
  code1 = *p++;
  code2 = *p++;
  code3 = *p++;
  code4 = *p;
  
}
 
void flash_write(void) {
  FCTL2 = FWKEY + FSSEL1 + FN1;     // MCLK/3 for Flash Timing Generator
  flash_clear();            // Block must always be cleared before writing
 
  char *Flash_ptr;
  Flash_ptr = (char *) 0x1001;      //Point to Info Flash segment D
 
  FCTL3 = FWKEY;                            // Clear Lock bit
  FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation
 
  *Flash_ptr++ = entry_code[0];
  *Flash_ptr++ = entry_code[1];
  *Flash_ptr++ = entry_code[2];
  *Flash_ptr++ = entry_code[3];
 
  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
}
 
/*
  note: Info flash must be cleared before writing new values
*/
void flash_clear(void) {
  int *Flash_ptr;
  Flash_ptr = (int *)0x1000;    //Point to Info Flash segment D
 
  FCTL3 = FWKEY;        // Clear Lock bit
  FCTL1 = FWKEY + ERASE;    // Set Erase bit
  *Flash_ptr = 0;       // Dummy write to erase Flash segment D
  FCTL1 = FWKEY;        // Clear WRT bit
  FCTL3 = FWKEY + LOCK;     // Set LOCK bit
}
