#ifndef __MSPLIB_H__
#define __MSPLIB_H__

#define __mainloop while(1)

static void __inline__ brief_pause(register unsigned int n)
{
    __asm__ __volatile__ (
		"1: \n"
		" dec	%[n] \n"
		" jne	1b \n"
        : [n] "+r"(n));
}

#endif // __MSPLIB_H__
