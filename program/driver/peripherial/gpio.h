#ifndef __GPIO_H__
#define __GPIO_H__

#define LED_1 GPIOD, GPIO_PIN_4 //blue
#define LED_2 GPIOD, GPIO_PIN_5 //green
#define LED_3 GPIOD, GPIO_PIN_6 //red

#define gpio_on(pin) HAL_GPIO_WritePin(pin, GPIO_PIN_SET)
#define gpio_off(pin) HAL_GPIO_WritePin(pin, GPIO_PIN_RESET)

void gpio_init(void);

#endif
