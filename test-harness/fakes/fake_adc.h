#ifndef FAKE_ADC_H
#define FAKE_ADC_H

void fake_adc_init();
float fake_adc_get_current();
void fake_adc_set_current(float c);

#endif