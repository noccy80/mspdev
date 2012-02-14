#ifndef __TIMERS_H__
#define __TIMERS_H__

void timer_stop(void* timer);
void timer_set_clock(void* timer, int clock);
void timer_set_iv(void* timer, int iv, long it);


#endif // __TIMERS_H__
