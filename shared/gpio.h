#ifndef __GPIO_H__
#define __GPIO_H__

#define GPIO(port,pin) (port << 5) | (pin - 1)
#define GPIO_INPUT     1
#define GPIO_OUTPUT    2
#define GPIO_PULLUP    4
#define GPIO_PULLDOWN  8

void gpio_set_mode(uint8_t gpiopin, uint8_t direction);
uint8_t gpio_get_mode(uint8_t gpiopin);)

#define GPIO_NO_INTERRUPT   0
#define GPIO_INTERRUPT      1
#define GPIO_INT_RISING     2
#define GPIO_INT_FALLING    4

void gpio_set_interrupt(uint8_t gpiopin, uint8_t intmode);

gpio_set_mode(GPIO(0,1), GPIO_INPUT | GPIO_PULLUP);
gpio_set_interrupt(GPIO(0,1), GPIO_INTERRUPT | GPIO_INT_RISING);




#endif // __GPIO_H__
