/**
 * Real Time Clock Interface
 *
 * This code is intended to be compatible with the RTC found on some of the
 * MSP430 series MCUs, while also giving access to a RTC over an I2C bus.
 *
 * Usage example:
 *
 *    RTC_TIME_STRUCT time;
 *    time.year = 11;
 *    time.month = 10;
 *    time.day = 10;
 *    time.hour = 04;
 *    time.minute = 21;
 *    time.second = 0;
 *    rtc_set_time(&time); 
 *
 *
 * @author Christopher Vagnetoft <noccylabs.info>
 * @license GNU General Public License (GPL) v2 or later
 */

#ifndef __rtc_h__
#define __rtc_h__

#include "i2c.h"

typedef struct rtc_time_struct {
	unsigned int year;
	unsigned int month;
	unsigned int day;
	unsigned int dow;
	unsigned int hour;
	unsigned int minute;
	unsigned int second;
} RTC_TIME_STRUCT;

#define RTC_USE_BEST 0
#define RTC_INTEGRATED 1
#define RTC_EMULATED 2
#define RTC_I2C 3

void rtc_init(unsigned char mode, unsigned char i2caddr);
unsigned int rtc_get_time(RTC_TIME_STRUCT* time);
unsigned int rtc_set_time(RTC_TIME_STRUCT* time);
const char* rtc_get_mode();

#endif
