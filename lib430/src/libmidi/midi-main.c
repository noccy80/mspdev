#include "msp430g2231.h"

#define 	CLOCKHZ		16000000 / 8
#define		nNotes		12

#define MIDI_DATA_PIN			BIT7
#define SPEAKER_PIN				BIT2

// Poly not implemented, but this is how 
// many notes can be hit at the same time 
// without forgetting the first
#define MAX_POLYPHONY			5
#define MIDI_CHANNEL			0	// MIDI is 1-indexed so setting this to 0 is midi channel 1
#define USI_COUNTER_LOAD		16

// Synth variables
unsigned int periodSetting = 61156;
const unsigned int synthNotes[nNotes] = {61156, 57723, 54484, 51424, 48539, 45817, 43245, 40816, 38527, 36364, 34322, 32396};

// MIDI Variables
char currentState = 1;
char bitStateCount = 0; 
char nextBitFinal = 0;	
char opcode;
char midiByte;
char rawMidiByte;
char newByte = 0;
char newVelocity;
char newNote;
char notes[MAX_POLYPHONY] = {0};
char velocities[MAX_POLYPHONY] = {0};
char controllerNumber;
char controllerValue;
int noteIndex = 0;
unsigned int USIData = 0;

void updateSynth(char on);
char getNextByte();
void updateState();
void noteOn();
void noteOff();
void controlChange();
void updateControls();
void shiftLeft(char index);
char getNoteIndex(char note);

void main(void)
{
	volatile unsigned long i;
	
	DCOCTL = CALDCO_16MHZ;
	BCSCTL1 = CALBC1_16MHZ;
	BCSCTL2 |= DIVS_2;						// SMCLK = MCLK / 4 = 4MHZ
	
	WDTCTL = WDTPW + WDTHOLD;               // Stop WDT
	_BIS_SR(GIE);							// enable interrupts	
	P1DIR |= BIT2 + BIT0 + BIT6;           	// P1.2 and P1.3 output
	P1OUT = 0;
	CCTL1 = OUTMOD_7;						// CCR1 reset/set
	TACTL = TASSEL_2 + MC_1 + ID_3;         // SMCLK, up mode, /8 = 500KHz
	TACCTL0 |= CCIE;
	CCR0 = 1;
	
	USICKCTL |= USISSEL_3;					// USI CLOCK SOURCE = SMCLK = 4MHZ
	USICKCTL |= USIDIV_5;//5				// DIVIDES SMCLK BY 32 = 31250 * 4 = MIDI SPEC * 4x oversample
	USICTL0 |= USIMST;						// USE THE INTERNAL CLOCK
	USICTL0 |= USIPE7;						// ENABLE USI INPUT PORT 1.7
	USICTL0 |= USILSB;
	USICTL0 &= ~USISWRST;					// START HARDWARE SERIAL RECIEVE
	USICNT |= USI16B;
	
	USICTL1 |= USIIE;						// INTERRUPT WHEN SERIAL CACHE FULL
	
  while(1){
	opcode = getNextByte();
  	if(opcode == (0x90 | MIDI_CHANNEL))
		noteOn();
  	else if(opcode == (0x80 | MIDI_CHANNEL))
		noteOff();
  	else if(opcode == (0xB0 | MIDI_CHANNEL))
  		controlChange();
  }
}

#pragma vector=USI_VECTOR
__interrupt void USI(){
	USICNT |= USI_COUNTER_LOAD;
	USIData = USISR;

	char samplingBit;
	
	for(samplingBit = 0; samplingBit < 16; samplingBit++){
		if((USIData & BIT0) ^ currentState){  // if they're not the same
			if(bitStateCount > 2){
				rawMidiByte >>= 1;
				if(currentState)
					rawMidiByte |= BIT7;
				if(nextBitFinal){
					newByte = 1;
					midiByte = rawMidiByte;
					rawMidiByte = 0xFF;
					nextBitFinal = 0;
				}
			}
			currentState ^= BIT0;
			bitStateCount = 1;
		}
		else{
			bitStateCount++;
			if(bitStateCount == 4){
				rawMidiByte >>= 1;
				if(currentState)
					rawMidiByte |= BIT7;
				if(nextBitFinal){
					newByte = 1;
					midiByte = rawMidiByte;
					rawMidiByte = 0xFF;
					nextBitFinal = 0;
				}
				bitStateCount = 0;
			}
		}
		USIData >>= 1;
		if(!newByte && (~rawMidiByte & BIT0))
			nextBitFinal = 1;
	}
}	

void noteOn(){
	do{	
		newNote = getNextByte();
		if(newNote & 0x80){
			newByte = 1;
			break;
		}
		newVelocity = getNextByte();
		if(newVelocity & 0x80){
			newByte = 1;
			break;
		}
		updateState();
	}while(1);
}

void noteOff(){
	do{
		newNote = getNextByte();
		if(newNote & 0x80){
			newByte = 1;
			break;
		}
		newVelocity = 0;
		updateState();
	}while(1);
}

void controlChange(){
	do{	
		controllerNumber = getNextByte();
		if(controllerNumber & 0x80){
			newByte = 1;
			break;
		}
		controllerValue = getNextByte();
		if(controllerValue & 0x80){
			newByte = 1;
			break;
		}
		updateControls();
	}while(1);
}

void updateControls(){
	// stub
//	if(controllerNumber == 1)
	// do something with controllerValue
}		

char getNextByte(){
	char nextByte;
	do{
		P1OUT &= ~BIT0;
		while(!newByte){
		}
		newByte = 0;
		nextByte = midiByte;
	}while((nextByte == 0xFE) || (nextByte == 0xFF));
	P1OUT |= BIT0;
	return nextByte;
}

#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A0 (void){
	CCR0 = periodSetting;
	CCR1 = (CCR0 >> 1);
}

void updateState(){
	if(noteIndex == 0 && newVelocity != 0){
		notes[0] = newNote;
		velocities[0] = newVelocity;
		updateSynth(1);
		noteIndex++;
	}
	else{
		if(newVelocity != 0){
			// add a new note when the poly cache is full, replacing the oldest
			if(MAX_POLYPHONY == noteIndex){
				shiftLeft(0);
				notes[MAX_POLYPHONY - 1] = newNote;
				velocities[MAX_POLYPHONY - 1] = newVelocity;
				updateSynth(1);
			}
			// add a new note
			else{
				notes[noteIndex] = newNote;
				velocities[noteIndex] = newVelocity;
				updateSynth(1);
				noteIndex++;
			}
		}
		else if(getNoteIndex(newNote) < MAX_POLYPHONY){
			shiftLeft(getNoteIndex(newNote));
			noteIndex -= 2;
			if(noteIndex >= 0){
				updateSynth(1);
				noteIndex++;
			}
			else{
				updateSynth(0);
				noteIndex = 0;
			}
		}
	}
}

void shiftLeft(char index){
	int i;
	for(i = index; i < MAX_POLYPHONY - 1; i++){
		notes[i] = notes[i + 1];
		velocities[i] = velocities[i + 1];
	}
}

char getNoteIndex(char note){
	int i;
	for(i = 0; i < MAX_POLYPHONY; i++)
		if(notes[i] == note)
			return i;
	return MAX_POLYPHONY + 1;
}

void updateSynth(char on){
	if(on){
		P1SEL |= 0x0C;
		P1OUT |= BIT6;
	}
	else{
		P1SEL &= ~0x0C;
		P1OUT &= ~BIT6;
	}
		if(noteIndex >= 0 && noteIndex < MAX_POLYPHONY)
			periodSetting = (synthNotes[notes[noteIndex] % 12] >> (notes[noteIndex] / 12));	
}
	