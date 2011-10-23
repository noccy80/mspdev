#include "rtc.h"
#include "i2c.h"

unsigned int rtc_get_time(RTC_TIME_STRUCT* time) {

	#ifdef HAS_RTC
		time->hour = RTCHOUR;
		time->minute = RTCMIN;
		time->second = RTCSEC;
		time->dow = 0;
		time->day = 0;
		time->month = 0;
		time->year = 0;
	#else // HAS_RTC
		#ifdef HAS_I2C
			i2c_begin(I2CADDR_RTC);
			i2c_read(I2CRTC_)
			i2c_end();
		#else // HAS_I2C
			time->hour = 0;
			time->minute = 0;
			time->second = 0;
			time->dow = 0;
			time->day = 0;
			time->month = 0;
			time->year = 0;
		#endif // HAS_I2C
	#endif // HAS_RTC
	return 0;

}

unsigned int rtc_set_time(RTC_TIME_STRUCT* time) {

	return 0;

}
