#include "c_driver_drv8874.h"

/***********************/
/* PRIVATE DEFINITIONS */
/***********************/

/*****************/
/* PRIVATE TYPES */
/*****************/

/*********************/
/* PRIVATE VARIABLES */
/*********************/

/*********************************/
/* PRIVATE FUNCTION DECLARATIONS */
/*********************************/

/********************************/
/* PRIVATE FUNCTION DEFINITIONS */
/********************************/

/*******************************/
/* PUBLIC FUNCTION DEFINITIONS */
/*******************************/
void motor_init(motor_t * motor)
{
    motor_sleep(motor);
    motor_disable(motor);
    motor_forward(motor);
}

void motor_enable(motor_t * motor)
{
    gpio_write(motor->enable_pin, GPIO_STATE_HIGH);
}

void motor_disable(motor_t * motor)
{
    gpio_write(motor->enable_pin, GPIO_STATE_LOW);
}

void motor_sleep(motor_t * motor)
{
    gpio_write(motor->sleep_pin, GPIO_STATE_LOW);
}

void motor_wake(motor_t * motor)
{
    gpio_write(motor->sleep_pin, GPIO_STATE_HIGH);
}

void motor_forward(motor_t * motor)
{
    gpio_write(motor->direction_pin, GPIO_STATE_HIGH);
}

void motor_reverse(motor_t * motor)
{
    gpio_write(motor->direction_pin, GPIO_STATE_LOW);
}

int motor_get_fault(motor_t * motor)
{
    gpio_state_t fault_state = gpio_read(motor->fault_pin);
    if (fault_state == GPIO_STATE_HIGH || fault_state == GPIO_STATE_UNDEFINED)
        return 0;
    return 1;
}

float motor_get_current(motor_t * motor)
{
    return adc_read();
}

//void motor_forward(motor_t * motor)

// Interface 
/**
 * motor_init(time_function, pin_write_function, pwm_write_function, sleep_pin)
 * motor_sleep()
 * motor_get_current()
 * motor_get_fault()
 * motor_enable()
 * motor_go(int32 speed)
 * 
*/