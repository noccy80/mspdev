#ifndef __MSPLIB_H__
#define __MSPLIB_H__

// Port Base
#define PORT1 P1IN
#define PORT2 P2IN
#define PORT3 P3IN
// Relative offsets
#define GPIO_BASE_IN 0
#define GPIO_BASE_OUT 1
#define GPIO_BASE_DIR 2
#define GPIO_BASE_IE 3
#define GPIO_BASE_RESISTORS 7

static void __inline__ brief_pause(register unsigned int n)
{
    __asm__ __volatile__ (
		"1: \n"
		" dec	%[n] \n"
		" jne	1b \n"
        : [n] "+r"(n));
}

#endif // __MSPLIB_H__
