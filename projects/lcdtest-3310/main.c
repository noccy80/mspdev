#include <msp430.h>
#include <legacymsp430.h>
#include <string.h>
#include "pcd8544.h"
#include "glyphs.h"

unsigned int p = 0;


// Display buffer

const char* menu[4]  = {
	"Option 1",
	"Option 2",
	"Option 3",
	"Option 4"
};

/**
 * @brief Called from Timer0_A0 ISR.
 * 
 * Updates the display.
 */
void update_display() {
	static int i = 0;
	static int p = 0;
	static int m = 0;
	
	lcd_draw_text_block(menu[0],10,1,(m==0),74);
	lcd_draw_glyph(check[0],2,1);
	
	lcd_draw_text_block(menu[1],10,2,(m==1),74);
	lcd_draw_glyph(check[1],2,2);
	
	lcd_draw_text_block(menu[2],10,3,(m==2),74);
	lcd_draw_glyph(radio[0],2,3);
	
	lcd_draw_text_block(menu[3],10,4,(m==3),74);
	lcd_draw_glyph(radio[1],2,4);
	
	lcd_draw_glyph(bar[0],0,5);
	lcd_tile_glyph(load[p],2,5,80);
	lcd_draw_glyph(bar[1],82,5);
	
	lcd_draw_glyph(batt[i],0,0);
	i++; if (i>3) i=0;
	p++; if (p>3) {
		p=0;
		m++; if (m>3) m=0;
	}

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
