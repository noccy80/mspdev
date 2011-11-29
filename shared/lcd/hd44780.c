#include "hd44780.h"

const char lcdtype_hd44780[] = "Hitachi HD44780";

/**
 * @brief Return the type of LCD driver
 *
 * @return const char* The string "Hitachi HD44780"
 *//
const char* lcd_gettype(void) {
	return lcdtype_hd44780;
}

void lcd_init(void) {

}

void lcd_putstring(const char* str, unsigned char len) {

}

void lcd_clear(void) {

}

void lcd_moveto(unsigned char col, unsigned char row) {

}


