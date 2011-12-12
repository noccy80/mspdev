
//I2C_Master.h

/*
use i2cm_out(...) and i2cm_in(...) between calls to i2cm_start(...) and i2cm_stop(...)

typical use(...) 
{
//this is an example of reading the config register of a DS1631
//in this case 'device' is a select number of 0000xxx0
//This example is incomplete in that the bus is not left with a
//stop condition if something goes wrong

	i2cm_start( );
	
	if( i2cm_out( 0x90 | device ) ) //send write control byte
		return;
	
	else if( i2cm_out( 0xac ) )//send config command byte
		return;
	
	i2cm_start( );//device wants start again to read
	
	if( i2cm_out( 0x91 | device ) ) //send read control byte
		return;
	
	i2cm_in( buf, 1 ); //input the config byte to 'buf'

	i2cm_stop( );
	//device was not busy or failed...
	//set sucsess flag if needed before return
	
} typical use end......


with mspgcc compiled for optimum code size this is about 256 bytes

*/

/*
Defines the port to be used like:
#define I2C_MASTER_REN P1REN
#define I2C_MASTER_DIR P1DIR
#define I2C_MASTER_OUT P1OUT
#define I2C_MASTER_IN  P1IN
//port pins
#define IC2_MASTER_SCL BIT2
#define I2C_MASTER_SDA BIT3
//Start and Stop delay, most devices need this
#define I2C_MASTER_SDLY		0x20
//for long lines or very fast MCLK, unremark and set
//#define I2C_MASTER_DDLY		0x02
//#define I2C_MASTER_UDLY
*/

//Declarations
//sends a start condition
//will set sda and scl high and delay before start
void i2cm_start( void );

//send stop condition
//will set sda low before delay and stop
void i2cm_stop( void );

//Output one byte
//assumes sda and scl low and leaves sda, scl low if ack.
//returns true if no ack from device
unsigned char i2cm_out( register unsigned int data );

//input count of bytes into buf[ ]
//Assumes scl low and leaves scl low
//sends ack to device until last byte then no ack
void i2cm_in( unsigned char* buf, int count );

/*
HE_util.h included for:
static void __inline__ brief_pause( register unsigned int n )
{
__asm__ __volatile__ (
		"1: \n"
		" dec %[n] \n"
		" jne 1b \n" : [n] "+r"(n)
		);
}

*/
