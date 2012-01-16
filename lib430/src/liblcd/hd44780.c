#include "hd44780.h"

void HD44780_send(HD44780 *lcd, uint8_t value, uint8_t mode) {
	digitalWrite(lcd->_rs_pin, mode);
	HD44780_write4bits(lcd, value>>4);
	HD44780_write4bits(lcd, value);
}




void HD44780_init(HD44780* lcd, int rs, int enable, int db4, int db5, int db6, int db7) {
	lcd->_rs_pin = rs;
	lcd->_enable_pin = enable;

	lcd->_data_pins[4] = db4;
	lcd->_data_pins[5] = db5;
	lcd->_data_pins[6] = db6;
	lcd->_data_pins[7] = db7; 

	pinMode(rs, OUTPUT);
	pinMode(enable, OUTPUT);

	lcd->_displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
}

void HD44780_begin(HD44780 *lcd, uint8_t cols, uint8_t lines) {
	if (lines > 1) {
		lcd->_displayfunction |= LCD_2LINE;
	}
	lcd->_numlines = lines;
	lcd->_currline = 0;


	// SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
	// according to datasheet, we need at least 40ms after power rises above 2.7V
	// before sending commands. Arduino can turn on way befer 4.5V so we'll wait 50
	delayMicroseconds(50000); 
	// Now we pull both RS and R/W low to begin commands
	digitalWrite(lcd->_rs_pin, LOW);
	digitalWrite(lcd->_enable_pin, LOW);

	//put the LCD into 4 bit or 8 bit mode
	if (! (lcd->_displayfunction & LCD_8BITMODE)) {
		// this is according to the hitachi HD44780 datasheet
		// figure 24, pg 46

		// we start in 8bit mode, try to set 4 bit mode
		HD44780_write4bits(lcd, 0x03);
		delayMicroseconds(4500); // wait min 4.1ms

		// second try
		HD44780_write4bits(lcd, 0x03);
		delayMicroseconds(4500); // wait min 4.1ms

		// third go!
		HD44780_write4bits(lcd, 0x03); 
		delayMicroseconds(150);

		// finally, set to 8-bit interface
		HD44780_write4bits(lcd, 0x02); 
	} else {
		// this is according to the hitachi HD44780 datasheet
		// page 45 figure 23

		// Send function set command sequence
		HD44780_command(lcd, LCD_FUNCTIONSET | lcd->_displayfunction);
		delayMicroseconds(4500);  // wait more than 4.1ms

		// second try
		HD44780_command(lcd, LCD_FUNCTIONSET | lcd->_displayfunction);
		delayMicroseconds(150);

		// third go
		HD44780_command(lcd, LCD_FUNCTIONSET | lcd->_displayfunction);
	}

	// finally, set # lines, font size, etc.
	HD44780_command(lcd, LCD_FUNCTIONSET | lcd->_displayfunction);  

	// turn the display on with no cursor or blinking default
	lcd->_displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;  
	HD44780_display(lcd);

	// clear it off
	HD44780_clear(lcd);

	// Initialize to default text direction (for romance languages)
	lcd->_displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	// set the entry mode
	HD44780_command(lcd, LCD_ENTRYMODESET | lcd->_displaymode);

}

void HD44780_write4bits(HD44780 *lcd, uint8_t value) {
	int i;
	for (i = 0; i < 4; i++) {
		pinMode(lcd->_data_pins[4+i],OUTPUT);
		digitalWrite(lcd->_data_pins[4+i], (value >> i) & 0x01);
	}

	HD44780_pulseEnable(lcd);
}


void HD44780_pulseEnable(HD44780 *lcd) {
	digitalWrite(lcd->_enable_pin, LOW);
	delayMicroseconds(2);    
	digitalWrite(lcd->_enable_pin, HIGH);
	delayMicroseconds(2);    // enable pulse must be >450ns
	digitalWrite(lcd->_enable_pin, LOW);
	delayMicroseconds(100);   // commands need > 37us to settle
}

void HD44780_clear(HD44780 *lcd) {
	HD44780_command(lcd, LCD_CLEARDISPLAY);  // clear display, set cursor position to zero
	delayMicroseconds(2000);  // this command takes a long time!
}

void HD44780_display(HD44780 *lcd) {
	lcd->_displaycontrol |= LCD_DISPLAYON;
	HD44780_command(lcd, LCD_DISPLAYCONTROL | lcd->_displaycontrol);
}

void HD44780_print_byte(HD44780 *lcd, uint8_t b) {
	HD44780_write(lcd, b);
}

void HD44780_print_string(HD44780 *lcd, const char c[]) {
	while (*c)
	HD44780_print_byte(lcd, *c++);
}

void HD44780_setCursor(HD44780 *lcd, uint8_t col, uint8_t row) {
	int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 }; 
	if ( row > lcd->_numlines ) { 
		row = lcd->_numlines-1;    // we count rows starting w/0 
	} 

	HD44780_command(lcd, LCD_SETDDRAMADDR | (col + row_offsets[row])); 
} 

void HD44780_scrollDisplayLeft(HD44780 *lcd) {
	HD44780_command(lcd, LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT); 
} 

void HD44780_scrollDisplayRight(HD44780 *lcd) {
	HD44780_command(lcd, LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT); 
}
