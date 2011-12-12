
#include  <msp430x20x3.h>

#include <iomacros.h>
#include <msp430/common.h>
#include <msp430/usi.h>

#define __MSP430_HAS_PORT1__
#include <msp430/gpio.h>
#include <signal.h>

#include "i2c.h"

//State of usi machine
volatile unsigned char usi_state;

//buffer for inputs from master
//unsigned char usi_buffer[ 8 ];

//pointer used internally by usi
unsigned char* usi_buf_ptr= 0;

//flag reflecting control bit r/w
unsigned char usi_read_write;

//command byte from master
unsigned char usi_command;

interrupt ( PORT1_VECTOR ) PORT1_6_I2C( void )
//void PORT1_6_I2C( void )
{
	if( P1IFG & BIT6 ) //hack for I2C awk on input
	{
		//clear interrupt enable
		P1IE&= ~BIT6;
		//clear flag
		P1IFG&= ~BIT6;
		//release output now that clock is low
		//if anything but output
		if( ! ( usi_state & USISTATE_OUTPUT ) )
			USICTL0&= ~USIOE;
	}

	if( P1IFG & BIT7 ) //hack for I2C STOP
	{
		//clear flag
		P1IFG&= ~BIT7;
		
		if( USICTL1 & USISTP
			&& ! ( usi_state & USISTATE_OUTPUT ) ) //STOP detected
		{
			//clear interrupt enable
			P1IE&= ~BIT7;
			initialize_i2c( );//reset USI
		}
	}
}

void initialize_i2c( void )
{
	USICTL0= USIPE6 | USIPE7 | USISWRST;//Port, I2C slave, hold reset
	USICTL1= USII2C | USISTTIE;			//Enable I2C mode, disable counter
	USICKCTL= USICKPL;					//Setup clock polarity
	USICNT= USISCLREL;					//SCL released
	//Initialize State machine and sit idle until START condition
	usi_state= USISTATE_NULL;
	USICTL0&= ~USISWRST;				// Clear Reset of USI
}

interrupt ( USI_VECTOR ) usi_interrupt( void )
{
	if( USICTL1 & USISTTIFG ) // START recieved....
	{
		USICTL1&= ~USISTTIFG;		// Clear START flag...
		USICNT= 0x08 | USISCLREL;	//  Clears USISCLREL
	    usi_state= USISTATE_RCVADR;	//Next is recieve address
	    USICTL1|= USIIE;			// Enable Counter Interrupt

	    //Clock is low, set up to monitor for STOP condition
		P1IFG&= ~BIT7; //make sure flag is clear
		P1IES&= ~BIT7; //interrupt on rising edge of I2C SDA
		P1IE|= BIT7; //enable interrupt for rising edge on SDA

		return;
	}
	//awk is a special case not for switch
	if( usi_state & USISTATE_AWK )
	{
		if( usi_state & USISTATE_OUTPUT )
		{
			if( USISRL ) //master said no more
			{
				initialize_i2c( );//reset USI, Wait for next start
				return;
			}
			USISRL= *usi_buf_ptr++; //Load output byte
			USICTL0|= USIOE; //Take SDA.
		}
		else //Input in progress, control, command or data
		{
			P1IES|= BIT6; //interrupt on falling edge of SCL
			P1IFG&= ~BIT6; //make sure flag is clear
			P1IE|= BIT6; //enable interrupt for input awk hack
			if( usi_state & USISTATE_OUTPUT_AWK )
			{
				USISRL= *usi_buf_ptr++; //Load output byte
				usi_state= USISTATE_OUTPUT;
			}
		}
		USICNT= 0x08 | USISCLREL;
		usi_state&= ~USISTATE_AWK;
		return;
	}
	switch( usi_state )
	{
	case USISTATE_RCVADR:
	{
		//Is it _not_ our address?
		if( USISRL >> 1 != USI_OURADDRESS )
		{
			initialize_i2c( );//reset USI, Wait for next start
			return;
		}
		//else our address, check the r/w bit next
		if( USISRL & 0x01 )
			usi_read_write= USI_RW_READ;
		else
			usi_read_write= USI_RW_WRITE;

		USISRL= 0;					//Zero to awk
		USICNT= 0x01 | USISCLREL;	//One bit to awk
		USICTL0|= USIOE;			//Take SDA.
		
		//Next is to recieve command word
		usi_state= USISTATE_COMMAND | USISTATE_AWK;

		LPM0_EXIT;
		return;
	}
	case USISTATE_COMMAND:
	{
		usi_command= USISRL;
		if( ! i2c_super_command( ) ) //super said don't awk
		{
			initialize_i2c( );
			return;
		}
		//super should have set pointer
		//next is to read or write data, to/from master
		if( usi_read_write ) //read is true
			usi_state= USISTATE_OUTPUT_AWK | USISTATE_AWK;
		else
			usi_state= USISTATE_INPUT | USISTATE_AWK;

		//This is a call?????
		USICTL0|= USIOE;			//Take SDA.
		USISRL= 0;					//Zero to awk
		USICNT= 0x01 | USISCLREL;	//One bit to awk
		return;
	}
	case USISTATE_INPUT:
	{
		*usi_buf_ptr++= USISRL;
		
		//Do awk
		USICTL0|= USIOE; //Take SDA.
		
		usi_state|= USISTATE_AWK;
		USISRL= 0;					//Zero to awk
		USICNT= 0x01 | USISCLREL;
		return;
	}
	case USISTATE_OUTPUT:
	{
		USICTL0&= ~USIOE; //Release SDA.
		
		usi_state|= USISTATE_AWK;
		USISRL= 0;
		USICNT= 0x01 | USISCLREL;
		return;
	}
	}//switch(...)!!!!!!
	
	//Should never get here!!!!!!
	initialize_i2c( );
}
