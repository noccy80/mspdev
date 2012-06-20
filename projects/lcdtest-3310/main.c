#include <msp430.h>
#include <legacymsp430.h>
#include <string.h>
#include "pcd8544.h"
#include "glyphs.h"

unsigned int p = 0;


// Display buffer

const char* str[5]  = {
	"              ",
	"  Loading...  ",
	" Please wait  ",
	"              ",
	"              "
};

/**
 * @brief Called from Timer0_A0 ISR.
 * 
 * Updates the display.
 */
void update_display() {
	static int i = 0;
	for (int q = 0; q < 5; q++) {
		lcd_draw_text(str[q],0,q+1);
	}
	lcd_draw_glyph(batt[i],0,0);
	i++; if (i>3) i=0;

}

/**
 * @brief Draws a hatch pattern on the display.
 * 
 */
void draw_hatch() {
	// draw cross pattern
	lcd_cursor(0,0);
	char v = 0xAA;
	for(int x=0;x<((84*48)/4);x++) {
		lcd_write_byte(v);
		v ^= 0xFF;
	}
}	

/**
 * @brief Main function
 * 
 */
int main(void) {

	WDTCTL = WDTPW + WDTHOLD; // Stop WDT

	// Initialize clock to 12MHz DCO
	BCSCTL1 = CALBC1_12MHZ;    // Set range
	DCOCTL = CALDCO_12MHZ;     // Set DCO step + modulation
	// Additional clock settings
	BCSCTL2 = 0xF8;


	//Set ACLK to use internal VLO (12 kHz clock)
	BCSCTL3 |= LFXT1S_2;
	//BCSCTL3 = LFXT1S_0 + XCAP_3;

	//Set TimerA to use auxiliary clock in UP mode
	TACTL = TASSEL_1 | MC_1;
	TACCTL0 = CCIE;
		
	// Set up timer for display updates
	TACCR0 = 1200;

	// Initialize LCD and enable global interrupts
	lcd_init();
	//draw_hatch();
	eint(); // _BIS_SR(GIE);

	for(;;); // buffer_flush();
	
}

interrupt(TIMER0_A0_VECTOR) ta0isr() {
	
	update_display();
	
}
