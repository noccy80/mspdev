# PCD8544-driver for msp430

This is a complete driver for the Philips PCD8544 LCD driver, used
in the Nokia 3310 displays and subsequently in Olimex MOD-LCD3310
LCD extension.

Expected port/pin mappings:

  - D/_C on P2.0
  - SDIN on P2.1
  - SCE  on P2.2
  - SCK  on P2.3
  - RES  on P2.4

If the display on your device is offset by 5 pixels, causing the
top row of the display to be 5 pixels down, then add the define
`PCD8544_FIX_YALIGN` to your project or `-DPCD8544_FIX_YALIGN` to your
compiler flags in the makefile to fix this problem.

When compiled, the driver can link putchar() to lcd_putchar(), allowing it
to integrate with the printf() present in mspgcc. If you do not wish to have
this link put in place, add `-DPCD8544_NO_PRINTF` to the flags in your makefile.

## Defines

  - `PCD8544_FIX_YALIGN` - Fixes offset issue with newer version controllers
  - `PCD8544_NO_PRINTF` - Don't create a putchar() stub for mspgcc:s printf()

## Functions

### Core functions

#### lcd_send()

Send data or command to LCD

    void lcd_send(unsigned char byte,unsigned char dc);

#### lcd_init();

Initialize the LCD

	void lcd_init(void);

#### lcd_clear()

Clear the LCD

	void lcd_clear(void);

#### lcd_clear_line()

Clear a line

	void lcd_clear_line(unsigned char line);

#### lcd_erase()

Erase a region from the display

    void lcd_erase(unsigned char x, unsigned char y, unsigned char width);

#### lcd_cursor()

Set the cursor position

    void lcd_cursor(unsigned char,unsigned char);

#### lcd_contrast()

Set the LCD contrast as a value between 0 and 127.

    void lcd_contrast(char c);

#### lcd_write_byte()

Write a byte to the display at the current position

	void lcd_write_byte(unsigned char b);

### Glyphs and images

Glyphs are arrays of chars, with the first value indicating the width of the
glyph. All glyphs operate on 8 bits (8 rows or 1 text row). 

#### lcd_draw_glyph()

Draws a glyph from a const char

	void lcd_draw_glyph(const char* glyph, unsigned char x, unsigned char y);

#### lcd_tile_glyph()

Tile a glyph from a const char

	void lcd_tile_glyph(const char* glyph, unsigned char x, unsigned char y, unsigned char w);

### Text functions
#### lcd_draw_text()

This function will draw the provided string to the LCD at the specified
position. It will only consume as many columns as the text fills, so if you
want to draw a menu or such, instead see lcd_draw_text_block()

    void lcd_draw_text(const char* string, unsigned char x, unsigned char y);

#### lcd_draw_text_block()

This function will allow for updating menus and the likes, where you need
to remove the text or graphics that was in a spot when updating the menu
entries. Optional inverted text for extra spiffiness.

    void lcd_draw_text_block(const char* string, unsigned char x, unsigned char y, int inverse, int length);

## Credits

Based on code by TopHatHacker (github.com/tophathacker) and rewritten
and commented for tidyness and modularity.

_Licensed under GNU GPL version 3_
