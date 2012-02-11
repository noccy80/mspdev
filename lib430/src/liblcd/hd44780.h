/**
 * @file hd44780.h
 * @brief Hitachi HD44780 Driver (Header file)
 *
 * Based on code from Hive76
 * https://groups.google.com/forum/#!topic/hive76-discussion/4PNA7SmirK0
 */

#ifndef __HD44780_H__
#define __HD44780_H__

#include <msp430.h>
#include <legacymsp430.h>
#include <stdint.h>

#include <arduino.h>

// commands
#define LCD_CLEARDISPLAY     0x01
#define LCD_RETURNHOME       0x02
#define LCD_ENTRYMODESET     0x04
#define LCD_DISPLAYCONTROL   0x08
#define LCD_CURSORSHIFT      0x10
#define LCD_FUNCTIONSET      0x20
#define LCD_SETCGRAMADDR     0x40
#define LCD_SETDDRAMADDR     0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT       0x00
#define LCD_ENTRYLEFT        0x02
#define LCD_ENTRYSHIFTINCR   0x01
#define LCD_ENTRYSHIFTDECR   0x00

// flags for display on/off control
#define LCD_DISPLAYON        0x04
#define LCD_DISPLAYOFF       0x00
#define LCD_CURSORON         0x02
#define LCD_CURSOROFF        0x00
#define LCD_BLINKON          0x01
#define LCD_BLINKOFF         0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE      0x08
#define LCD_CURSORMOVE       0x00
#define LCD_MOVERIGHT        0x04
#define LCD_MOVELEFT         0x00

// flags for function set
#define LCD_8BITMODE         0x10
#define LCD_4BITMODE         0x00
#define LCD_2LINE            0x08
#define LCD_1LINE            0x00
#define LCD_5x10DOTS         0x04
#define LCD_5x8DOTS          0x00

/**
 * @brief Control structure for interfacing the Hitachi HD44780
 *
 */
typedef struct _HD44780 {
	uint8_t _rs_pin; ///< @var Register Select pin. Low for command and high for character. (RS)
	uint8_t _enable_pin; ///< @var Enable strobe pin (E)
	uint8_t _data_pins[8]; ///< @var The 8 data pins, only 5-8 used in 4-bit mode (DB1-DB7)

	uint8_t _displayfunction;
	uint8_t _displaycontrol;
	uint8_t _displaymode; ///< @var Display mode flags

	uint8_t _initialized; ///< @var Non-zero after successful initialization
	
	uint8_t _numlines; ///< @var Number of lines
	uint8_t _currline; ///< @var Current line
} HD44780;

/**
 * @const hd44780_row_offset
 * @brief The offsets in ram for each row.
 */
const int hd44780_row_offset[] = { 0x00, 0x40, 0x14, 0x54 };

/**
 * @brief Check the busy flag.
 *
 * The datasheets outline checking the busy flag after each operation. However,
 * an alternative method is to wait for a specific number of µS before moving
 * on to the next command or byte.
 *
 * If you wish to make liblcd check the busy flag between operations you
 * should compile it with HD44780_BUSYCHECK=1 defined. Otherwise, it will be
 * built 
 *
 * @return int Non-zero if the LCD is busy.
 */
int hd44780_check_busy(HD44780* lcd);

/**
 * @brief Initialize the display
 *
 * @todo This function need to be rewritten. The structure can be defined prior to calling.
 *
 * @param HD44780* lcd The previously created control structure
 * @param int rs The RS pin.
 * @param int enable The enable pin.
 * @param int db4 Data pin 4
 * @param int db5 Data pin 5
 * @param int db6 Data pin 6
 * @param int db7 Data pin 7
 * @return int Non-zero on success.
 */
int HD44780_init(HD44780* lcd, int rs, int enable, int db4, int db5, int db6, int db7);

/**
 * @brief 
 *
 * The Character Generator RAM (CGRAM) can hold custom glyphs that can be
 * displayed on the display. This method is used to write a glyph to the
 * RAM.
 * 
 * @todo More indepth info on how the glyphs are laid out
 */
void hd44780_write_cgram(HD44780* lcd, int offset, int data);

/**
 * @brief Read data from the CGRAM.
 *
 * The Character Generator RAM (CGRAM) can hold custom glyphs that can be
 * displayed on the display. This method is used to read a glyph from the
 * RAM.
 * 
 * @todo More indepth info on how the glyphs are laid out
 */
int hd4470_read_cgram(HD44780* lcd, int offset, int bytes, char* data);

/**
 * @brief
 *
 */
void HD44780_begin(HD44780 *lcd, uint8_t cols, uint8_t lines);

/**
 * @brief
 *
 */
void hd44780_send(HD44780 *lcd, uint8_t value, uint8_t mode);

/**
 * @brief Write 4 bits to the HD44780
 *
 */
void HD44780_write4bits(HD44780 *lcd, uint8_t value);

/**
 * @brief Pulse the enable pin, telling the HD44780 to read the pins.
 *
 */
void hd44780_strobeenable(HD44780 *lcd);

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
 * @brief Print a string to the display.
 *
 * @param HD44780* lcd The LCD control structure
 * @param const char* c The character string to print
 */
void HD44780_print_string(HD44780 *lcd, const char* c);

/**
 * @brief Write a character to the HD44780
 * @inline
 *
 * @param HD44780* lcd The LCD control structure
 */
inline void HD44780_write(HD44780 *lcd, uint8_t value) {
	hd44780_send(lcd, value, HIGH);
}

/**
 * @brief Send a command to the HD44780
 *
 * @param HD44780* lcd The LCD control structure
 * @param const char* c The character string to print
 */
inline void HD44780_command(HD44780 *lcd, uint8_t value) {
	hd44780_send(lcd, value, LOW);
}

#endif // __HD44780_H__
