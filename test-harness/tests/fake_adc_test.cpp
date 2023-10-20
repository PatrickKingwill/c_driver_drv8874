#include "CppUTest/TestHarness.h"

extern "C" 
{
    #include "../fakes/fake_adc.h"
    #include <math.h>
}


TEST_GROUP(FakeADCTest)
{
    void setup()
    {
        fake_adc_init();
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
};

// Zero
TEST(FakeADCTest, initialise_and_gpios_undefined)
{
    CHECK(floats_equal(0.0f, fake_adc_get_current()));
}

TEST(FakeADCTest, set_current_equals_get_current)
{
    fake_adc_set_current(1.23f);

    CHECK(floats_equal(1.23f, fake_adc_get_current()));
}