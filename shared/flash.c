#include "flash.h"

void flash_read(uint16_t addr, void* sdata, uint16_t size) {

	// addr = 0x1001
	// sdata = struct to copy to
	// size = num bytes to copy
	memcpy((char*)addr, sdata, size);

}

void flash_write(uint16_t addr, void* sdata, uint16_t size) {

	FCTL2 = FWKEY + FSSEL1 + FN1;     // MCLK/3 for Flash Timing Generator
	flash_clear(addr);            // Block must always be cleared before writing

	FCTL3 = FWKEY;                            // Clear Lock bit
	FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation

	memcpy((char*)sdata, (char*)&addr, size);

	FCTL1 = FWKEY;                            // Clear WRT bit
	FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
}

/*
  note: Info flash must be cleared before writing new values
*/
void flash_clear(uint16_t addr) {

	char* dp = (char*)&addr;

	FCTL3 = FWKEY;        // Clear Lock bit
	FCTL1 = FWKEY + ERASE;    // Set Erase bit
	dp = 0;       // Dummy write to erase Flash segment D
	FCTL1 = FWKEY;        // Clear WRT bit
	FCTL3 = FWKEY + LOCK;     // Set LOCK bit
}
