/**
 * config.h - configure baud rates, MCLK frequency
 *
 * License: Do with this code what you want. However, don't blame
 * me if you connect it to a heart pump and it stops.  This source
 * is provided as is with no warranties. It probably has bugs!!
 * You have been warned!
 *
 * Author: Rick Kimball
 * email: rick@kimballsoftware.com
 * Version: 1.00 Initial version 05-12-2011
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#define F_CPU  16000000     // use calibrated 16MHZ clock

#ifdef __MSPGCC__
#define _enable_interrupts() __bis_status_register(GIE)
#define _disable_interrupts() __bic_status_register(GIE)
#endif

#endif
