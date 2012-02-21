#include "bcd.h"

const uint8_t bcd_char[10] = {
             //  |x A B C|D E F G 
             //  |8 4 2 1|8 4 2 1
    0x01,    // 0:  1 1 1 1 1 1 0
    0x02,    // 1:  0 1 1 0 0 0 0
    0x04,    // 2:  1 1 0 1 1 0 1
    0x08,    // 3:  1 1 1 1 0 0 1
    0x10,    // 4:  0 1 1 0 0 1 1
    0x20,    // 5:  1 0 1 1 0 1 1
    0x40,    // 6:  1 0 1 1 1 1 1
    0x80,    // 7:  1 1 1 0 0 0 0
    0xFF,    // 8:  1 1 1 1 1 1 1
    0x00,    // 9:  1 1 1 1 0 1 1
};


void bcd_write(int digit) {
/*
	P2DIR = 0xFF;
	P2REN = 0x00;
	P2SEL = 0x00;
	P2SEL2 = 0x00;

	P2OUT = (bcd_char[digit] >> 1);
*/
}
