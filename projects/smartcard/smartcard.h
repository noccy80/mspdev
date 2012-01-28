#ifndef __SMARTCARD_H__
#define __SMARTCARD_H__

typedef struct _SmartCard {
	long iopin;
	long clkpin;
	long rstpin;
} SmartCard;

void sc_init();
int sc_card_inserted();

/**
 * @brief Resets the card according to ISO7816 3.2.b
 *
 * A card reset is initiated by the interface device, whereupon the card shall
 * respond with an Answer to Reset as describe in 2.4. By the end of the 
 * activation of the contacts (RST is in L, VCC powered and stable, I/O in 
 * reception mode in the interface device, VPP stable at idle level, CLK 
 * provided with a suitable and stable clock), the card answering 
 * asynchronously is ready for reset.
 */
int sd_card_reset();

int sc_read_bit();
void sc_write_bit(int bit);

void sc_set_bit(int bit, int state);
int sc_get_bit(int bit);

void sc_set_app2(int state);
int sc_get_app2();

#endif // __SMARTCARD_H__
