#ifndef GPIO_SPY_H
#define GPIO_SPY_H

#define MAX_GPIOS 16

#include "c_driver_drv8874.h"   

// typedef enum
// {
//     GPIO_STATE_UNDEFINED,
//     GPIO_STATE_LOW,
//     GPIO_STATE_HIGH
// } gpio_state_t;

void gpio_spy_init(void);
gpio_state_t gpio_spy_get_state(int pin);
void gpio_spy_set_state(int pin, gpio_state_t state);

#endif