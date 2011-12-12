#include "i2cmaster.h"

//Send data byte out on bang i2c, return false if ack
//Assumes start has been set up or a next byte
//so  both lines are assumed low
// **Lower byte of 'data' is sent**
unsigned char i2cm_out( register unsigned int data )
{
	volatile unsigned int i= 0; //will be register
	//output eight bits of 'data'
	for( ; i < 8; ++i )
	{
		//send the data bit
		if( data & 0x80 )
			I2C_MASTER_DIR&= ~I2C_MASTER_SDA;
		else
			I2C_MASTER_DIR|= I2C_MASTER_SDA;
		
		//shift next data bit
		data<<= 1;

//Toggle SCL, first high
		I2C_MASTER_DIR&= ~I2C_MASTER_SCL;
		
#ifdef I2C_MASTER_UDLY
		brief_pause( I2C_MASTER_DDLY );
#endif //I2C_MASTER_UDLY

		//Set SCL Low
		I2C_MASTER_DIR|= I2C_MASTER_SCL;
	}

	//make sure SDA inputs
	I2C_MASTER_DIR&= ~I2C_MASTER_SDA;

	//Set  SCL High
	I2C_MASTER_DIR&= ~I2C_MASTER_SCL;

	//get the ack bit, true if ack
	uint16_t ack= !( I2C_MASTER_IN & I2C_MASTER_SDA );
	
	if( ack ) //leave SDA in last state!
		I2C_MASTER_DIR|= I2C_MASTER_SDA;

	//Set SCL Low
	I2C_MASTER_DIR|= I2C_MASTER_SCL;

	return ack;
}

//Assumes the IC2_MASTER_SCL is low
void i2cm_in( unsigned char* buf, int count )
{
	unsigned char data;
	for( ; count--; )
	{
		data= 0;
		//Release SDA
		I2C_MASTER_DIR&= ~I2C_MASTER_SDA;

		volatile unsigned int i= 0;
		for( ; i < 8; ++i )
		{
			//Set Clock High
		I2C_MASTER_DIR&= ~I2C_MASTER_SCL;
			
			//shift the bit over
			data= data << 1;
		
			if( I2C_MASTER_IN & I2C_MASTER_SDA )
				data|= 0x01;
			
			//Set Clock Low
			I2C_MASTER_DIR|= I2C_MASTER_SCL;
		}
		//put the input data byte into the buffer, inc buffer pointer
		*buf++= data;
		
		//No Ack after last byte
		if( count )
			I2C_MASTER_DIR|= I2C_MASTER_SDA;

//Toggle SCL, first high
		I2C_MASTER_DIR&= ~I2C_MASTER_SCL;
		
#ifdef I2C_MASTER_UDLY
		brief_pause( I2C_MASTER_DDLY );
#endif //I2C_MASTER_UDLY

		//Set SCL Low
		I2C_MASTER_DIR|= I2C_MASTER_SCL;
	}
}

void i2cm_start( void )
{
	//Make sure both pins are high
	I2C_MASTER_DIR&= ~( I2C_MASTER_SDA | I2C_MASTER_SCL );
	//Set output low here so'I2C Master Init' is not needed
	I2C_MASTER_OUT&= ~( I2C_MASTER_SDA | I2C_MASTER_SCL );
	
	//Set SDALow, pause in case both pins were not high
    brief_pause( I2C_MASTER_SDLY );
	I2C_MASTER_DIR|= I2C_MASTER_SDA;
	
	//Set SCL Low
    brief_pause( I2C_MASTER_SDLY );
	I2C_MASTER_DIR|= I2C_MASTER_SCL;
}

//Assumes SCL is low
void i2cm_stop( void )
{
	//make sure SDA is low
	I2C_MASTER_DIR|= I2C_MASTER_SDA;
	
	//SCL to high, pause in case SDA was high
    brief_pause( I2C_MASTER_SDLY );
	I2C_MASTER_DIR&= ~I2C_MASTER_SCL;
	//SDA to high
    brief_pause( I2C_MASTER_SDLY );
	I2C_MASTER_DIR&= ~I2C_MASTER_SDA;
}

