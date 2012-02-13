#include "arduino.h"
#include <wdt.h>
#include <msplib.h>

int constrain(int val, int min, int max) {
	return ((val<min)?min:((val>max)?max:val));
}

int map(int val, int amin, int amax, int bmin, int bmax) {
	int anum = (amax - amin);
	int bnum = (bmax - bmin);
	float mul = bnum / anum;
	int ret = bmin + ((val - amin) * mul);
	return ret;
}
