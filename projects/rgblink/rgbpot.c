//includes
#include <msp430x20x2.h>
#include <signal.h> //add for interrupt
//Defines
#define UP 0x00
#define DOWN 0x01
#define HOLD 0x02
#define PERIOD 200 //sets period length-- PERIOD x interval length
//variables
volatile  int millsecs = 0;
volatile  int counter2 = 0;
//volatile  int counter3 = 0;
volatile  int led_red = 1;
volatile  int led_green = 1;
volatile  int led_blue = 1;
volatile  int red = UP;
volatile  int blue = HOLD;
volatile  int green = HOLD;
//start of main
void main(void)
{
//set WDT to interval mode
WDTCTL = WDT_MDLY_0_064;
//pin setup
P1DIR |= BIT5 + BIT4 + BIT3;
P1OUT |= BIT5 + BIT4 + BIT3;
//set interrupts
IE1 |= WDTIE;
eint();
//turn off CPU
_BIS_SR(CPUOFF);
}//end main
//WDT interval interrupt SR
interrupt(WDT_VECTOR) watchdog_timer(void)
{
++millsecs;//period and dutycycle counter
//period logic
if (millsecs == PERIOD) { millsecs= 0; P1OUT |= BIT5 + BIT4 + BIT3; ++counter2; }
//Duty cycle logic
if (millsecs == led_red ) { P1OUT ^= BIT3; }
if (millsecs == led_green) { P1OUT ^= BIT4; }
if (millsecs == led_blue ) { P1OUT ^= BIT5; }
//fade logic
if (counter2 == 254 ) { counter2 =0; //++counter3;
//power timer or how long till it turns off
//if (counter3 == 1000) { P1OUT = 0; _BIS_SR(LPM4_bits);}
switch (red){
case UP: ++led_red;
if (led_red == 199) {red = HOLD; green = UP; blue = DOWN;}
break;
case DOWN: --led_red;
if (led_red == 0) {red = HOLD;}
break;
case HOLD: break;
}//end switch
switch (blue){
case UP:  ++led_blue;
if (led_blue == 199) {blue = HOLD; green = DOWN; red = UP;}
break;
case DOWN: --led_blue;
if (led_blue == 0) {blue = HOLD;}
break;
case HOLD: break;
}//end switch
switch (green){
case UP: ++led_green;
if (led_green == 199) {green = HOLD; red = DOWN; blue = UP;}
break;
case DOWN: --led_green;
if (led_green == 0) {green = HOLD;}
break;
case HOLD: break;
}//end switch
}//end if
}//end interrupt
