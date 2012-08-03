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
`-DPCD8544_FIX_YALIGN` to your compiler flags in the makefile to fix this 
problem. This will also implement a soft wrapping algorithm that automatically
moves on to the correct position when you are writing beyond the visible
width of the row.

When compiled, the driver can link putchar() to lcd_putchar(), allowing it
to integrate with the printf() present in mspgcc. If you do not wish to have
this link put in place, add `-DPCD8544_NO_PRINTF` to the flags in your makefile.

The code has been written for MSPGCC, and it will require you to build the code
against the gnu99 standard allowing inline variable declaration by appending 
`-std=gnu99` to the compiler flags. This is an example of how to define this in
the makefile:

    CXXFLAGS += -std=gnu99 -DPCD8544_FIX_YALIGN

If you are cherrypicking files, don't forget to grab [the common.mk](https://github.com/noccy80/mspdev/blob/master/skeleton/common.mk)
file and modify the included Makefile to include it from it's new location.

## Defines

  - `PCD8544_FIX_YALIGN` - Fixes offset issue with newer version controllers
  - `PCD8544_NO_PRINTF` - Don't create a putchar() stub for mspgcc:s printf()

## Functions

### Core functions

#### lcd_init()

Initialize the LCD. Make sure to set the gpio pin directions before calling this method.

    void lcd_init(void);

#### lcd_send()

Send data or command to LCD

    void lcd_send(unsigned char byte,unsigned char dc);

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

Example:

    // Write 8 set pixels and then 8 cleared pixels
    lcd_write_byte(0xFF);
    lcd_write_byte(0x00);


### Glyphs and images

Glyphs are arrays of chars, with the first value indicating the width of the
glyph. All glyphs operate on 8 bits (8 rows or 1 text row). 

#### lcd_draw_glyph()

Draws a glyph from a const char

    void lcd_draw_glyph(const char* glyph, unsigned char x, unsigned char y);

Example:

    // Draw a battery icon in topleft corner of the display
    lcd_draw_glyph(batteryicon[0], 0, 0);

#### lcd_tile_glyph()

Tile a glyph from a const char

    void lcd_tile_glyph(const char* glyph, unsigned char x, unsigned char y, unsigned char w);

Example:

    // Use a hatch pattern and fill the bottom row of the display.
    const char hatch[3] = { 2, 0x55, 0xAA };
    lcd_tile_glyph(hatch,0,5,83);


### Text functions
#### lcd_draw_text()

This function will draw the provided string to the LCD at the specified
position. It will only consume as many columns as the text fills, so if you
want to draw a menu or such, instead see lcd_draw_text_block()

    void lcd_draw_text(const char* string, unsigned char x, unsigned char y);

Example:

    // Write "Hello World" to the top left corner of the display
    lcd_draw_text("Hello World!", 0, 0);

#### lcd_draw_text_block()

This function will allow for updating menus and the likes, where you need
to remove the text or graphics that was in a spot when updating the menu
entries. Optional inverted text for extra spiffiness.

    void lcd_draw_text_block(const char* string, unsigned char x, unsigned char y, int inverse, int length);

Example:

    // Draw two menu items to the display, make the first inverted
    lcd_draw_text_block("Option #1", 0, 0, 1, 83);
    lcd_draw_text_block("Option #2", 0, 1, 0, 83);


## Credits

Based on example code by TopHatHacker (github.com/tophathacker). 
Greatly rewritten and commented by Noccy (github.com/noccy80).

[noccylabs.info](http://noccylabs.info)

_Licensed under GNU GPL version 3_
