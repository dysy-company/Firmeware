#include <mbed.h>
#include <unity.h>

DigitalOut led1(LED2, 0);

void setUp(void)
{
  // set stuff up here
}

void tearDown(void)
{
  // clean stuff up here
}

void test_led_builtin_pin_number(void)
{
  TEST_ASSERT_EQUAL(13, LED2);
}

void test_led_state_high(void)
{
  led1.write(1);
  TEST_ASSERT_EQUAL(1, led1.read());
}

void test_led_state_low(void)
{
  led1.write(0);
  TEST_ASSERT_EQUAL(0, led1.read());
}

uint8_t i = 0;
uint8_t max_blinks = 5;

int main()
{
  // NOTE!!! Wait for >2 secs
  // if board doesn't support software reset via Serial.DTR/RTS
  //ThisThread::sleep_for(5000ms);

  UNITY_BEGIN(); // IMPORTANT LINE!
  RUN_TEST(test_led_builtin_pin_number);
  for(int i = 0; i < max_blinks; i++){
    RUN_TEST(test_led_state_high);
    ThisThread::sleep_for(500ms);
    RUN_TEST(test_led_state_low);
    ThisThread::sleep_for(500ms);
  }
  UNITY_END(); // stop unit testing
}