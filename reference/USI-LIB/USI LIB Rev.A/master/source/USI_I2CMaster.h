#ifndef TI_USI_I2C
#define TI_USI_I2C

#define TI_USI_EXIT_LPM            1
#define TI_USI_STAY_LPM            0

extern void TI_USI_I2C_MasterInit(unsigned char ClockConfig, int(*StatusCallback)(unsigned char) );
extern unsigned char TI_USI_I2CSelect(unsigned char SlaveAddress);
extern unsigned char TI_USI_I2CRead(unsigned char SlaveAddress, unsigned int Length, unsigned char Multi, void* RxData);
extern unsigned char TI_USI_I2CWrite(unsigned char SlaveAddress, unsigned int Length, unsigned char Multi,void* TxData);
extern void TI_USI_I2CStop(void);

#endif
