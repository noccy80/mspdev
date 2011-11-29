#ifndef __HD44780_H__
#ifdef HAS_LCD
#warning LCD Support already compiled in!
#else
#define HAS_LCD

#define LCD_8BIT 1
#define LCD_4BIT 0

const char* lcd_gettype(void);
void lcd_init(void);
void lcd_putstring(const char* str, unsigned char len);
void lcd_clear(void);
void lcd_moveto(unsigned char col, unsigned char row);

#endif // HAS_LCD
#endif // __HD44780_H__
