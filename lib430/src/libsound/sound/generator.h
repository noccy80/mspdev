#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#define WAVE_POLYPHONY 4

enum _WAVEFORM {
	WF_SQUARE = 0,
	WF_SINE = 1,
	WF_SAW = 2
};

class Envelope {
protected:
	int step;
	int noteon;
	int note;
	float keymod;
public:
	void noteOn(int note, float keymod);
	void noteOff();
	void reset();
	virtual int read();
};

class AdsrEnvelope: public Envelope {
private:
	int a, d, s, r;
public:
	AdsrEnvelope(int attack, int decay, int sustain, int release);
	int read();
};

class Generator {
public:
	Generator(int wf);
	~Generator();
	void noteOn(int note, int velocity);
	void noteOff();
	void waveSetEnvelope(Envelope* envelope);
	void waveSetWaveform(int wf);
	void waveSetTune(float tunec);
	void waveSetPwm(float pwm);
	void waveSetRingMod(Generator* generator);
	void waveSetRingModValue(float ringmod);
private:
	float value;
	int _wf;
	float tunec;
	float pwm;
	float ringmod;
	Generator* ringmodsrc;
	Envelope* envelope;
};

struct GeneratorList {
	Generator* generator;
	void* next;
};

class SoundMixer {
public:
	SoundMixer();
	~SoundMixer();
	void addGenerator(Generator* generator);
private:
	GeneratorList* generators;
};

#endif
