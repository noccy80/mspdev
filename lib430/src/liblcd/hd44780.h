#ifndef __HD44780_H__
#define __HD44780_H__

#include <msp430.h>
#include <legacymsp430.h>
#include <stdint.h>

#include "wiring.h"

/**
 * @brief Definitions for the Hitachi HD44780 series LCD display
 *
 * Based on code from Hive76
 * https://groups.google.com/forum/#!topic/hive76-discussion/4PNA7SmirK0
 */

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

/**
 * @brief Control structure for interfacing the Hitachi HD44780
 *
 */
typedef struct _HD44780 {
	uint8_t _rs_pin; ///< LOW: command.  HIGH: character.

	uint8_t _enable_pin; /// activated by a HIGH pulse.
	uint8_t _data_pins[8];
	uint8_t _fourbit;

	uint8_t _displayfunction;
	uint8_t _displaycontrol;
	uint8_t _displaymode;

	uint8_t _initialized;

	uint8_t _numlines,_currline;
} HD44780;

/**
 * @brief Initialize the display
 *
 * @param HD44780* lcd The previously created control structure
 * @param int rs The RS pin.
 * @param int enable The enable pin.
 * @param int db4 Data pin 4
 * @param int db5 Data pin 5
 * @param int db6 Data pin 6
 * @param int db7 Data pin 7 
 */
void HD44780_init(HD44780* lcd, int rs, int enable, int db4, int db5, int db6, int db7);

/**
 * @brief
 *
 */
void HD44780_begin(HD44780 *lcd, uint8_t cols, uint8_t lines);

/**
 * @brief
 *
 */
void HD44780_send(HD44780 *lcd, uint8_t value, uint8_t mode);

/**
 * @brief Write 4 bits to the HD44780
 *
 */
void HD44780_write4bits(HD44780 *lcd, uint8_t value);

/**
 * @brief Pulse the enable pin, telling the HD44780 to read the pins.
 *
 */
void HD44780_pulseEnable(HD44780 *lcd);

/**
 * @brief Clear the display
 *
 */
void HD44780_clear(HD44780 *lcd);

/**
 * @brief Enable the display
 *
 */
void HD44780_display(HD44780 *lcd);

/**
 * @brief Print a byte to the display
 *
 */
void HD44780_print_byte(HD44780 *lcd, uint8_t b);

/**
 * @brief Print a string to the display
 *
 */
void HD44780_print_string(HD44780 *lcd, const char c[]);

/**
 * @brief Write a character to the HD44780
 *
 */
inline void HD44780_write(HD44780 *lcd, uint8_t value) {
	HD44780_send(lcd, value, HIGH);
}

/**
 * @brief Send a command to the HD44780
 *
 */
inline void HD44780_command(HD44780 *lcd, uint8_t value) {
	HD44780_send(lcd, value, LOW);
}

#endif // __HD44780_H__
