#ifndef C_DRIVER_DRV8874_H
#define C_DRIVER_DRV8874_H
#include "user_motor.h"

/***********************/
/* PUBLIC DEFINITIONS */
/***********************/

/****************/
/* PUBLIC TYPES */
/****************/

/**
 * @brief Describes the pins of the motor.
*/
typedef struct motor_t
{
    pin_t enable_pin;
    pin_t sleep_pin;
    pin_t direction_pin;
    pin_t fault_pin;
} motor_t;

/**
 * @brief Describes GPIO states.
*/
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

/**
 * @brief Prototype for generic GPIO write. Implemented in user_motor.c.
 * 
 * @param pin - User defined pin to write to.
 * @param state - Value to write to pin.
*/
void gpio_write(pin_t pin, gpio_state_t state);

/**
 * @brief Prototype for generic GPIO read. Implemented in user_motor.c.
 * 
 * @param pin - User defined pin to read from.
 * 
 * @return Value read from pin.
*/
gpio_state_t gpio_read(pin_t pin);

/**
 * @brief Prototype for generic ADC read. Implemented in user_motor.c.
 * 
 * @return Value from from ADC.
*/
float adc_read();

/**
 * @brief Intialises the motor. Ensures GPIOs are set so that motor is asleep, disabled and in "forwards" mode.
 * 
 * @param motor - Pointer to motor struct.
*/
void motor_init(motor_t * motor);

/**
 * @brief Enables the motor. If not asleep, motor will start turning according to set direction.
 * 
 * @param motor - Pointer to motor struct.
*/
void motor_enable(motor_t * motor);

/**
 * @brief Disables the motor. Motor will brake and then stop.
 * 
 * @param motor - Pointer to motor struct.
*/
void motor_disable(motor_t * motor);

/**
 * @brief Sleeps the motor.
 * 
 * @param motor - Pointer to motor struct.
*/
void motor_sleep(motor_t * motor);

/**
 * @brief Wakes the motor.
 * 
 * @param motor - Pointer to motor struct.
*/
void motor_wake(motor_t * motor);

/**
 * @brief Changes the motor direction to forward.
 * 
 * @param motor - Pointer to motor struct.
*/
void motor_forward(motor_t * motor);

/**
 * @brief Changes the motor direction to reverse.
 * 
 * @param motor - Pointer to motor struct.
*/
void motor_reverse(motor_t * motor);

/**
 * @brief Retreives the motor's fault value.
 * 
 * @param motor - Pointer to motor struct.
 * 
 * @return Value of fault. 0 means no fault, 1 means fault.
*/
int motor_get_fault(motor_t * motor);

/**
 * @brief Gets the motors current draw.
 * 
 * @param motor - Pointer to motor struct.
 * 
 * @return Current draw in amps.
*/
float motor_get_current(motor_t * motor);

#endif