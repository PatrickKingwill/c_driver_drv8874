#include "gpio_spy.h"

gpio_state_t pin_states[MAX_GPIOS];

void gpio_spy_init(void)
{
    for (int i = 0; i < MAX_GPIOS; i++)
    {
        pin_states[i] = GPIO_STATE_UNDEFINED;
    }
}

gpio_state_t gpio_spy_get_state(int pin)
{
    if (pin >= MAX_GPIOS || pin < 0)
        return GPIO_STATE_UNDEFINED;
    return pin_states[pin];
}

void gpio_spy_set_state(int pin, gpio_state_t state)
{
    if (pin >= MAX_GPIOS || pin < 0)
        return;
    pin_states[pin] = state;
}