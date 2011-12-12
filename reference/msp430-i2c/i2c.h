

/*
 Todo.
 	Some devices on the bus may use restarts
 	without a stop. This condition is not handled...
 	
 	
 */

//our address
#define		USI_OURADDRESS		( 0xB0 >> 1 )

//waiting for start
#define 	USISTATE_NULL		0x00

//doing awknowlege bit
//this is clear through switch
#define		USISTATE_AWK		0x01

//recieving device address
#define 	USISTATE_RCVADR		0x02

//New 1-10-09; We require a command byte
#define		USISTATE_COMMAND	0x04

//We are inputing data from master
#define		USISTATE_INPUT		0x10

//ack command before output state
#define		USISTATE_OUTPUT_AWK	0x20

//We are outputing data to master
#define		USISTATE_OUTPUT		0x40

// The read/write states
#define USI_RW_WRITE			0x00
#define USI_RW_READ				0x01

//State of usi machine
extern volatile unsigned char usi_state;

//The command byte recieved from master
extern unsigned char usi_command;

//The control word is sent with r/w
extern unsigned char usi_read_write;

//pointer used internally by usi
//This is set by the super, requested by this code
extern unsigned char* usi_buf_ptr;

//Define these in user...............

//A command byte was recieved by i2c slave
unsigned char i2c_super_command( );

//..................................

//Call this in main at initialization
void initialize_i2c( void );

//Call this in PORT1_VECTOR interrupt
//void PORT1_6_I2C( void );


