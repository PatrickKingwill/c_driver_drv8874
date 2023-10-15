#ifndef C_DRIVER_DRV8874_H
#define C_DRIVER_DRV8874_H
#include "user_motor.h"

/***********************/
/* PUBLIC DEFINITIONS */
/***********************/

/****************/
/* PUBLIC TYPES */
/****************/
typedef struct motor_t
{
    pin_t enable_pin;
    pin_t sleep_pin;
    pin_t direction_pin;
    pin_t fault_pin;

} motor_t;

typedef enum
{
    GPIO_STATE_UNDEFINED,
    GPIO_STATE_LOW,
    GPIO_STATE_HIGH
} gpio_state_t;

/********************/
/* PUBLIC VARIABLES */
/********************/

/********************************/
/* PUBLIC FUNCTION DECLARATIONS */
/********************************/
void gpio_write(pin_t pin, gpio_state_t state);
gpio_state_t gpio_read(pin_t pin);
float adc_read();
void motor_init(motor_t * motor);
void motor_enable(motor_t * motor);
void motor_disable(motor_t * motor);
void motor_sleep(motor_t * motor);
void motor_wake(motor_t * motor);
void motor_forward(motor_t * motor);
void motor_reverse(motor_t * motor);
int motor_get_fault(motor_t * motor);
float motor_get_current(motor_t * motor);
#endif