#include "sound/generator.h"

AdsrEnvelope::AdsrEnvelope(int attack, int decay, int sustain, int release) {
	this->a = attack;
	this->d = decay;
	this->s = sustain;
	this->r = release;
}

void Envelope::noteOn(int note, float keymod) {
	this->note = note;
	this->keymod = keymod;
	this->step = 0;
	this->noteon = 1;
}

void Envelope::noteOff() {
	this->noteon = 0;
}

int AdsrEnvelope::read() {
	return 0;
}
