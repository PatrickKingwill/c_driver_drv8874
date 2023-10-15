#include "user_motor.h"
#include "c_driver_drv8874.h"
#include "../test-harness/spies/gpio_spy.h"
#include "../test-harness/fakes/fake_adc.h"

void gpio_write(pin_t pin, gpio_state_t state)
{
    gpio_spy_set_state(pin.pin, state);
}

gpio_state_t gpio_read(pin_t pin)
{
    return gpio_spy_get_state(pin.pin);
}

float adc_read()
{
    return fake_adc_get_current();
}