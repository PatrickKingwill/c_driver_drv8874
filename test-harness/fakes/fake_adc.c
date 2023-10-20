#include "fake_adc.h"

float current;

void fake_adc_init()
{
    current = 0.0f;
}

float fake_adc_get_current()
{
    return current;
}

void fake_adc_set_current(float c)
{
    current = c;
}