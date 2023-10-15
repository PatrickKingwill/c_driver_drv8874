#include "CppUTest/TestHarness.h"

extern "C" 
{
    #include "../spies/gpio_spy.h"
}


TEST_GROUP(GPIOSpyTest)
{
    void setup()
    {
        gpio_spy_init();
    }

    void teardown()
    {
    }
};

// Zero
TEST(GPIOSpyTest, initialise_and_gpios_undefined)
{
    LONGS_EQUAL(GPIO_STATE_UNDEFINED, gpio_spy_get_state(0));
}

// One
TEST(GPIOSpyTest, set_state_will_set_state)
{
    gpio_spy_set_state(0, GPIO_STATE_HIGH);

    LONGS_EQUAL(GPIO_STATE_HIGH, gpio_spy_get_state(0));
}

// Many
TEST(GPIOSpyTest, set_state_wont_change_other_pins)
{
    gpio_spy_set_state(0, GPIO_STATE_HIGH);

    LONGS_EQUAL(GPIO_STATE_UNDEFINED, gpio_spy_get_state(1));
}

TEST(GPIOSpyTest, dont_overflow_buffer)
{
    gpio_spy_set_state(MAX_GPIOS + 100, GPIO_STATE_LOW);

    gpio_spy_get_state(MAX_GPIOS + 100);
}