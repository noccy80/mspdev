/**
 * @file main.c
 * 
 * NoccyOne - MSP430 based software synthesizer with arpeggiator.
 *
 * To Be Implemented:
 *   - Use ints and floats internally for all calculations.
 *   - Add proper waveforms
 *   - 8bit->16bit down/upsampling
 *   - Use all 3 ccr for timer1 for 3 notes polyphony.
 *
 * @author Christopher Vagnetoft <noccylabs.info>
 * @license GNU General Public License 3.0
 */
 
#include <msp430.h>
#include <legacymsp430.h>

volatile int osc_on = 0;
volatile int pwm_base = 0;
volatile int pwm_phase = 0;
volatile int samples = 2;

/*
 * Frequency map.
 *
 * This needs to be redone and pre-calculated to the appropriate timer intervals
 * for increased precision.
 */
const int freq[] = { 
	0,    16,   17,   18,   19,   20,   21,   23,   24,   25, 
	27,   29,   30,   32,   34,   36,   38,   41,   43,   46, 
	49,   51,   55,   58,   61,   65,   69,   73,   77,   82, 
	87,   92,   98,   103,  110,  116,  123,  130,  138,  146, 
	155,  164,  174,  185,  196,  207,  220,  233,  246,  261, 
	277,  293,  311,  329,  349,  369,  392,  415,  440,  466, 
	493,  523,  554,  587,  622,  659,  698,  739,  783,  830, 
	880,  932,  987,  1046, 1108, 1174, 1244, 1318, 1396, 1479, 
	1567, 1661, 1760, 1864, 1975, 2093, 2217, 2349, 2489, 2637, 
	2793, 2959, 3135, 3322, 3520, 3729, 3951, 4186, 4434, 4698, 
	4978
};

/*
 * Square wave
 *  __    __   
 * |  |  |  |  
 * |  |__|  |__
 */
const int w_sqr[] = { 
	255,  255,  255,  255,  255,  255,  255,  255,  255,  255, 
	0,    0,    0,    0,    0,    0,    0,    0,    0,    0
};
/*
 * Saw wave
 *
 * |\ |\ |\ |\
 * | \| \| \| \
 */
const int w_saw[] = {
	255,  241,  228,  214,  201,  187,  174,  161,  147,  134, 
	120,  107,  93,   80,   67,   53,   40,   26,   13,   0

};
/*
 * Hacksaw
 *
 * |\_ |\_ |\_
 * |  \|  \|  \
 */
const int w_hacksaw[] = {
	0xFF, 0xF8, 0xF0, 0xE8, 0xE0, 0xA8, 0xA0, 0x98, 0x90, 0x88, 
	0x80, 0x78, 0x70, 0x68, 0x60, 0x28, 0x20, 0x18, 0x10, 0x08
};
/*
 * Sine wave
 *
 *  _     _     _
 * / \   / \   / \
 *    \_/   \_/
 */
const int w_sine[] = {
	128,  150,  190,  220,  255,  255,  220,  190,  150,  128,  
	110,  90,   60,   30,   0,    0,    30,   60,   90,   110
};

int* lfo = &w_sine;
int* osc = &w_hacksaw;

/*
 * Demo melody
 */
const int melody[] = { 
	0,    0,    0,    0,
};
const int melody2[] = { 
	40,   40,   40,   40,
	38,   0,    38,   0,
	35,   0,    35,   0,
	38,   0,    0,    0,
	40,   40,   40,   40,
	38,   0,    38,   0,
	35,   0,    0,    0,
	0,    0,    0,    0,
};
const int melodyold[] = { 
	25,   37,   20,   37, 
	24,   36,   19,   36, 
	20,   32,   15,   32, 
	18,   30,   13,   32, 
};
const int melody_steps = 32;

/*
 * Arpeggiator sequence,  and the number of steps. Arp LP defines the virtual
 * split.
 */
const int arp_seq[] = {0, 5};
const int arp_seqold[] = {0,  4,  7,  12};
const int arp_steps = 3;
const int arp_lp = 26;

/*
 * Do not touch
 */
volatile int arp_step = 0;

void init_timer() {

	//Set ACLK to use internal VLO (12 kHz clock)
	BCSCTL3 |= LFXT1S_0;

	//Set TimerA to use auxiliary clock in UP mode
	TACTL = TASSEL_1 | MC_1;
	//Enable the interrupt for TACCR0 match
	TACCTL0 = CCIE;
	TACCR0 = 2000;

	WRITE_SR(GIE);		


}

void note_on(int hz) {
	
	int tcr;
	// Set TACCR0 which also starts the timer. At 12 kHz,  counting to 12000
	// should output an LED change every 1 second. Try this out and see how
	// inaccurate the VLO can be
	osc_on = 1;
	tcr = (12000 / hz);
	tcr = tcr / samples;
	pwm_base = tcr;
	TACCR0 = tcr;

}

void note_off() {

	osc_on = 0;
}

int main(void) {

	int n,  m;
	int note;
	int t = 10;

	WDTCTL = WDTPW + WDTHOLD;;
	P1DIR |= BIT0 | BIT2 | BIT6;

	init_timer();
	do {
		for(n = 0; n < 32; n++) {
			if (++t>3) { t = 0; P1OUT |= BIT0; }
			// The number of iterations to do per note
			for(m = 0; m < 8; m++) {
				note = melody[n];
				if (note>0) {
					P1OUT |=BIT6;
					// If the note is above the arpeggio virtual split...
					if (note>arp_lp) {
						// Step through the arpeggio sequence
						arp_step = (arp_step + 1) % arp_steps;
						note_on(freq[note+arp_seq[arp_step]]);
					} else {
						// Play the actual note
						note_on(freq[note]);
					}
					P1OUT &= ~(BIT6);
				} else {
					__delay_cycles(7000);
				}
				// Delay a little bit (15k * 0.005µS)
				__delay_cycles(8000);
				P1OUT &= ~(BIT6|BIT0);
			}
			// Stop playing the note
			note_off();
			// Delay some more between notes
			for(m = 0; m < 5; m++) {
				__delay_cycles(4000);
			}
		}
		
	} while(1);

	note_off();
}

interrupt(TIMER0_A0_VECTOR) ta0isr(void) {

	static int oscstep = 0;

	if (osc_on)	{
		oscstep=oscstep+(20/samples);
		if (oscstep>20) oscstep = 0;
		if (osc[oscstep] > 128) {
			P1OUT |= BIT2;
			//TACCR0 = pwm_base * (1.0+(pwm_phase/128));
		} else {
			P1OUT &= ~BIT2;
			//TACCR0 = pwm_base * (1.0-(pwm_base * (pwm_phase/128)));
		}
	}

}
