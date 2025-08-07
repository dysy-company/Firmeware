#include "points.h"

pointsTest::pointsTest(){

}

pointsTest::~pointsTest(){

}

bool pointsTest::checkValue(double value){
    TEST_ASSERT_EQUAL_DOUBLE(5.0, value);
    if(Unity.CurrentTestFailed){
        return true;
    }else{
        return false;
    }
}