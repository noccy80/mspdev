
#include "pcd8544.h"
#include "font5x8.h"

#ifndef PCD8544_FIX_YALIGN
#warning If your display is offset by 5 pixels, add -DPCD8544_FIX_YALIGN to CXXFLAGS
#endif
 
void lcd_send(unsigned char data, unsigned char cd) {
 
	volatile unsigned char bits;
	unsigned short cnt=8;
	// assume clk is hi
	// Enable display controller (active low).
	SCEPORT &= ~SCE;  //RESET SCE

	// command or data
	if(cd == LCD_SEND_DATA) {
		DCPORT |= DC;  //set to send data
	} else {  // reset to send command
		DCPORT &= ~DC;
	}

	///// SEND SPI /////
	bits=0x80; // bits is mask to select bit to send. select bit msb first

	//send data
	while (0<cnt--) {
		// put bit on line
		// cycle clock
		SCKPORT &= ~SCK;
		if ((data & bits)>0) SDINPORT |= SDIN; else SDINPORT &= ~SDIN;
		//Delay(1);
		SCKPORT |= SCK;
		//Delay(2);
		// SHIFT BIT MASK 1 right
		bits >>= 1;
	}

	// Disable display controller.
	SCEPORT |= SCE;
 
}
 
void lcd_clear(void) {
	for (int i=0;i<LCD_ROWS;i++) { // number of rows
		lcd_cursor(0,i);
		for (int j=0;j<LCD_X_RES;j++)  // number of columns
			lcd_send(0x00, LCD_SEND_DATA);
	}
}
 
void lcd_clear_line(unsigned char l) {
	lcd_cursor(0,l);
	for (int j=0;j<LCD_X_RES;j++)  // number of columns
		lcd_send(0x00, LCD_SEND_DATA);
}
 
void lcd_init(void) {

 	// set up ports and initialize to output
 	P2DIR = 0xFF;

	// Reset LCD
	SCEPORT &= ~SCE;          // RESET SCE to enable
	// toggle RES
	RESPORT |= RES;           // Set RES
	char l;
	for(l=0;l<100;l++)
	l=l;
	RESPORT &= ~RES;          // reset RES
	for(l=0;l<100;l++)
	l=l;
	RESPORT |= RES;           // Set RES

	// Cycle Clock
	SCKPORT &= ~SCK;
	SCKPORT |= SCK;

	// Disable display controller.
	SCEPORT |= SCE;           // bring high to disable 

	for(l=0;l<100;l++)
	l=l;

	// Send sequence of command
	lcd_send( 0x21, LCD_SEND_COMMAND );  // LCD Extended Commands.
	// lcd_send( 0xC8, LCD_SEND_COMMAND );  // Set LCD Vop (Contrast).
	lcd_send( 0x80 | 0x70, LCD_SEND_COMMAND );  // Set LCD Vop (Contrast).
	lcd_send( 0x06, LCD_SEND_COMMAND );  // Set Temp coefficent to 2.
	lcd_send( 0x13, LCD_SEND_COMMAND );  // LCD bias mode 1:100.
	#ifdef PCD8544_FIX_YALIGN
	lcd_send( 0x45, LCD_SEND_COMMAND );  // LCD blank - Shift LCD 5 up (row starts at 1)
	#endif
	lcd_send( 0x20, LCD_SEND_COMMAND );  // LCD Standard Commands, Horizontal addressing mode.
	lcd_send( 0x40, LCD_SEND_COMMAND );  // LCD blank
	lcd_send( 0x08, LCD_SEND_COMMAND );  // LCD blank
	lcd_send( 0x0C, LCD_SEND_COMMAND );  // LCD in inverse mode.

	lcd_clear();
 
}
 
void lcd_contrast(char c) {
	lcd_send( 0x21, LCD_SEND_COMMAND );  // LCD Extended Commands.
	lcd_send( c, LCD_SEND_COMMAND );  // Set LCD Vop (Contrast).
	lcd_send( 0x20, LCD_SEND_COMMAND );  // LCD Standard Commands, Horizontal addressing mode.
}
 
void lcd_cursor(unsigned char x, unsigned char y) {
    lcd_send(0x80|x,LCD_SEND_COMMAND);
	#ifdef FIX_YALIGN
    lcd_send(0x40|(y+1),LCD_SEND_COMMAND);
	#else
    lcd_send(0x40|y,LCD_SEND_COMMAND);
	#endif
}
 
void lcd_draw_glyph(const char* glyph, unsigned char x, unsigned char y) {
	lcd_cursor(x,y);
	for (int c = 0; c < glyph[0]; c++) {
		lcd_send(glyph[c+1], LCD_SEND_DATA);
	}
}

void lcd_draw_text(const char* string, unsigned char x, unsigned char y) {
	lcd_cursor(x,y);
	for (int c = 0; c < strlen(string); c++) {
		for (int n = 0; n < 6; n++) {
			lcd_send(font5x8[(unsigned char)string[c]][n], LCD_SEND_DATA);
		}
	}

}
