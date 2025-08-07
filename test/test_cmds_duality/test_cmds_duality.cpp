#include <mbed.h>
#include <unity.h>
#include "..//include//Enums//Commands.h"

void test_command_duality(uint32_t cmd)
{
  
  TEST_ASSERT_EQUAL(0, led1.read());
}

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