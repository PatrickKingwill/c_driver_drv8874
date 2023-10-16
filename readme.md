C driver for the DRV8874 texas instruments H-bridge motor driver.

### Set Up
You must define a pin_t type which describes a pin for your platform. This is to be defined in user_motor.h
Example for STM32 + HAL:
```
typedef struct
{
  GPIO_TypeDef * port;
  uint16_t pin;
} pin_t;

```

You must implement 3 functions in user_motor.c.
- void gpio_write(pin_t pin, gpio_state_t state)
This takes a pin_t structure and a gpio_state_t value (GPIO_STATE_HIGH, GPIO_STATE_LOW) and should call the appropriate function to set the given pin to the given state.
Example for STM32 + HAL:
```
void gpio_write(pin_t pin, gpio_state_t state)
{
  GPIO_PinState hal_state = state == GPIO_STATE_HIGH ? GPIO_PIN_SET : GPIO_PIN_RESET;
  HAL_GPIO_WritePin(pin.port, pin.pin, hal_state);
}
```

- gpio_state_t gpio_read(pin_t pin)
This takes a pin_t structure, reads it using whatever platform GPIO read function, and then outputs a GPIO_STATE_HIGH or GPIO_STATE_LOW depending on the read value.
Example for STM32 + HAL:
```
gpio_state_t gpio_read(pin_t pin)
{
  GPIO_PinState hal_state = HAL_GPIO_ReadPin(pin.port, pin.pin);
  gpio_state_t gpio_state = hal_state == GPIO_PIN_SET ? GPIO_STATE_HIGH : GPIO_STATE_LOW;
  return gpio_state;
}
```

- float adc_read()
This reads your configured ADC and converts the value to current, then returns this value
Example for STM32 + HAL:
```
float adc_read()
{
  HAL_ADC_Start(&hadc1);
  HAL_ADC_PollForConversion(&hadc1, 1);
  uint16_t raw = HAL_ADC_GetValue(&hadc1);
  float volts_per_lsb = 3.3f / 4096.0f;
  float volts = (float)raw * volts_per_lsb;
  // Bjorn has chosen a resistor value such that 1V = 1A, therefore the voltage can be treated as the current
  return volts;
}
```

### Usage
Once set up, initialise the motor by creating a motor_t struct describing the pinout using previously defined pin_t structs. Pass this struct to the motor_init function and the module is ready to use.
Example for STM32 + HAL:
```
motor_t motor = {
    .enable_pin = {.port = MOTOR_EN_GPIO_Port, .pin = MOTOR_EN_Pin},
    .sleep_pin = {.port = MOTOR_SLEEP_GPIO_Port, .pin = MOTOR_SLEEP_Pin},
    .direction_pin = {.port = MOTOR_DIR_GPIO_Port, .pin = MOTOR_DIR_Pin},
    .fault_pin = {.port = MOTOR_FAULT_GPIO_Port, .pin = MOTOR_FAULT_Pin}
};

motor_init(&motor);
```

motor_init initialises the pin states so that the motor is asleep, disabled and its direction is forward.
To start the motor spinning, do the following:
```
motor_wake(&motor);
motor_enable(&motor);
```