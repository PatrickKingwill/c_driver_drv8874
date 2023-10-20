#include "CppUTest/TestHarness.h"

extern "C" 
{
    #include "../spies/gpio_spy.h"
    #include "../../inc/c_driver_drv8874.h"
    #include "../fakes/fake_adc.h"
    #include <math.h>
}


TEST_GROUP(MotorTest) 
{
    void setup()
    {
        gpio_spy_init();
        motor = {
            .enable_pin = {.pin = 0},
            .sleep_pin = {.pin = 1},
            .direction_pin = {.pin = 2},
            .fault_pin = {.pin = 3}
        };

        motor_init(&motor);
    }

    void teardown()
    {
    }

    bool floats_equal(float a, float b)
    {
        if (fabs(a - b) < 0.0001)
        {
            return true;
        }

        return false;
    }

    motor_t motor;

};

// Zero
// check default state of motor after init 
// the default state is enable = low, sleep = low and direction = forward.
TEST(MotorTest, initial_state_correct)
{
    LONGS_EQUAL(GPIO_STATE_LOW, gpio_spy_get_state(motor.enable_pin.pin));
    LONGS_EQUAL(GPIO_STATE_LOW, gpio_spy_get_state(motor.sleep_pin.pin));
    LONGS_EQUAL(GPIO_STATE_HIGH, gpio_spy_get_state(motor.direction_pin.pin));
}
// One

// enable motor, motor is enabled...
TEST(MotorTest, enable_motor)
{
    motor_enable(&motor);

    LONGS_EQUAL(GPIO_STATE_HIGH, gpio_spy_get_state(motor.enable_pin.pin));
}

// disable motor, motor is disabled
TEST(MotorTest, disable_motor)
{
    motor_disable(&motor);

    LONGS_EQUAL(GPIO_STATE_LOW, gpio_spy_get_state(motor.enable_pin.pin));
}

// sleep motor, motor is sleep
TEST(MotorTest, sleep_motor)
{
    motor_sleep(&motor);

    LONGS_EQUAL(GPIO_STATE_LOW, gpio_spy_get_state(motor.sleep_pin.pin));
}

// wake motor, motor is wake
TEST(MotorTest, wake_motor)
{
    motor_wake(&motor);

    LONGS_EQUAL(GPIO_STATE_HIGH, gpio_spy_get_state(motor.sleep_pin.pin));
}

// set motor to forward, motor is forward
TEST(MotorTest, direction_forward)
{
    motor_forward(&motor);

    LONGS_EQUAL(GPIO_STATE_HIGH, gpio_spy_get_state(motor.direction_pin.pin));
}

// set motor to backwards, motor is backwards
TEST(MotorTest, direction_reverse)
{
    motor_reverse(&motor);

    LONGS_EQUAL(GPIO_STATE_LOW, gpio_spy_get_state(motor.direction_pin.pin));
}

// if not fault, get_fault returns 0
TEST(MotorTest, no_fault)
{
    LONGS_EQUAL(0, motor_get_fault(&motor));
}

// if fault, get_fault returns 1
TEST(MotorTest, yes_fault)
{
    gpio_spy_set_state(motor.fault_pin.pin, GPIO_STATE_LOW);
    LONGS_EQUAL(1, motor_get_fault(&motor));
}

// read current from adc
TEST(MotorTest, read_current_from_adc)
{
    fake_adc_set_current(1.2f);

    float current = motor_get_current(&motor);

    CHECK(floats_equal(1.2f, current));
}
// Many

// enabling motor 1 doesn't enable motor 2
TEST(MotorTest, enable_1_and_2_not_enabled)
{
    motor_t motor_2 = {
        .enable_pin = {.pin = 4},
        .sleep_pin = {.pin = 5},
        .direction_pin = {.pin = 6},
        .fault_pin = {.pin = 7}
    };

    motor_init(&motor_2);

    motor_enable(&motor);

    LONGS_EQUAL(GPIO_STATE_LOW, gpio_spy_get_state(motor_2.enable_pin.pin));
}

