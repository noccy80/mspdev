/**
 * @file ili9163test.c
 * @brief ILI9163/FTM144D01N 128x128 TFT Test code
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @copyright   Copyright (C) 2012 Simon Inns
 * @author Simon Inns <simon.inns@gmail.com>
 */

#include <avr/io.h>
#include <util/delay.h>

#include "ili9163lcd.h"

int main(void)
{
	lcdInitialise(LCD_ORIENTATION2);
	
	lcdClearDisplay(decodeRgbValue(0, 0, 0));
	
	lcdLine(0, 0, 127, 127, decodeRgbValue(31, 31, 31));
	lcdLine(0, 127, 127, 0, decodeRgbValue(31, 31, 31));
	lcdCircle(64, 64, 32, decodeRgbValue(31, 0, 0));
	lcdCircle(64, 64, 40, decodeRgbValue(0, 31, 0));
	lcdCircle(64, 64, 48, decodeRgbValue(0, 0, 31));
	
	lcdPutS("Hello World!", lcdTextX(4), lcdTextY(0), decodeRgbValue(0, 0, 0), decodeRgbValue(31, 31, 31));
	
	lcdPutS("The quick brown fox jumped over the lazy dog 0123456789", lcdTextX(0), lcdTextY(2), decodeRgbValue(0, 31, 31), decodeRgbValue(0, 0, 0));
	
	lcdFilledRectangle(0, 64, 127, 127, decodeRgbValue(0, 0, 0));
	lcdRectangle(0, 64, 127, 127, decodeRgbValue(31, 31, 31));
	
	// Run the LCD test
	uint8_t ballX = 64, ballY = 96;
	int8_t ballSpeed = 1;
	int8_t xDir = ballSpeed, yDir = ballSpeed;
	
	// Bouncy ball demo
    while(1)
    {
		// Delete the ball
		lcdFilledRectangle(ballX-2, ballY-1, ballX+2, ballY+1, decodeRgbValue(0, 0, 0));
		
		// Delete the bat
		lcdFilledRectangle(ballX-4, 121, ballX+4, 123, decodeRgbValue(0, 0, 0));
		
		// Move the ball
		ballX += xDir;
		ballY += yDir;
		
		// Range check
		if (ballX > 120) xDir = -ballSpeed;
		if (ballX < 7) xDir = ballSpeed;
		
		if (ballY > 120) yDir = -ballSpeed;
		if (ballY < 70) yDir = ballSpeed;
		
		// Plot the ball
		lcdFilledRectangle(ballX-2, ballY-1, ballX+2, ballY+1, decodeRgbValue(31, 31, 31));
		
		// Plot the bat
		lcdFilledRectangle(ballX-4, 121, ballX+4, 123, decodeRgbValue(31, 0, 31));
		
		lcdPutS("Hello World!", lcdTextX(4), lcdTextY(0), decodeRgbValue(0, 0, 0), decodeRgbValue(31, 31, 31));
		_delay_ms(10);
    }
}
