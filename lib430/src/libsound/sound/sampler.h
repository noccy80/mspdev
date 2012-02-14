#ifndef __SAMPLER_H__
#define __SAMPLER_H__

#define MAX_SAMPLES 64
#define MAX_POLYPHONY 8

class SamplePlayer {
public:
	SamplePlayer();
private:
	void* sample_data[MAX_SAMPLES];
	int current_sample;
	float voice_pos[MAX_POLYPHONY];
};



#endif
