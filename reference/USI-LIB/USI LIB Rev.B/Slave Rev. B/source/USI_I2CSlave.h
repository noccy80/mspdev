#ifndef TI_USI_I2C
#define TI_USI_I2C

#define TI_USI_EXIT_LPM            1
#define TI_USI_STAY_LPM            0

extern void TI_USI_I2C_SlaveInit(unsigned char OwnAddress,void(*StartCallback)(void),int(*RxCallback)(unsigned char),int(*TxCallback)(int*));

#endif
