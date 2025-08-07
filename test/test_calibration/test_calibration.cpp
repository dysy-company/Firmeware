#include <mbed.h>
#include <unity.h>
#include "Calibration.h"

Calibration *calibration;
point_t *calibrationPoints;
double *xRAWValues;

const int calibrationPointsLength = 7;
const int xRAWValuesLength = 7;

void setUp(void)
{
  // set stuff up here
  //calibration = new Calibration(50);
  //calibrationPoints = new point_t[calibrationPointsLength]{0.0, 0.0, -1.1, -1.1, -2.0, -4.0, -4.0,-4.1, 1.0, 3.0, 5.0, 4.0, 7.0, 3.0};
  //xRAWValues = new double[xRAWValuesLength]{-5.0, -4.0, -3.5, -2.0, -1.5, -1.0, 0.0};
}

void tearDown(void)
{
  // clean stuff up here
  delete calibration;
  delete[] calibrationPoints;
  delete[] xRAWValues;
 }

void test1(void){
    //TEST_ASSERT_FALSE(pt1->checkValue(5.01));
    TEST_ASSERT_EQUAL_DOUBLE(5.0, 1.0);
}

void testFindAlgorith(void){
  //calibration->setPoints(calibrationPoints, calibrationPointsLength);
  //calibration->calculateSections();
}

int main()
{
  // NOTE!!! Wait for >2 secs
  // if board doesn't support software reset via Serial.DTR/RTS
  ThisThread::sleep_for(3000ms);

  UNITY_BEGIN(); // IMPORTANT LINE!
  //RUN_TEST(test1);

  UNITY_END(); // stop unit testing
}