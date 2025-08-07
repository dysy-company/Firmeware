#ifndef SPEED_CALIBRATION_H
#define SPEED_CALIBRATION_H

#include <mbed.h>
#include "..//Calibration/Calibration.h"
#include "..//BasicElements/BasicElements.h"
#include "..//InternalFlash/InternalFlash.h"
#include "..//InternalFlashDMA/InternalFlashDMA.h"
#include "..//..//include//Shared_Params.h"

extern BasicElements basic;
extern InternalFlash internalFlash;
extern InternalFlashDMA internalFlashDMA;

typedef struct speedCalibrationParams{
    double speed;//mm/sec
    double Kp;
    double Ki;
    double Kd;
    double maxDeviation;//mm
} speedCalibrationParams_t;

class SpeedCalibration{
    public:
        SpeedCalibration(int maxPoints);
        ~SpeedCalibration();
        void getPositionPoints(void);
        void getStrainPoints(void);
        bool setNumberOfPoints(int numberOfPoints);
        bool getNumberOfPoints(int &numberOfPoints);
        bool setPoints(speedCalibrationParams_t *params, int length);
        bool getPoints(speedCalibrationParams_t *params, int &length);
        uint32_t getMaxPoints();
        void getValue(double speed, double &Kp, double &Ki, double &Kd, double &maxDeviation);
        void sortBySpeed(void);
        void setFlashOperationType(uint32_t flashOperationType);
        void setPointsToFlash(speedCalibrationParams_t *params, int size);
        void getPointsSizeFromFlash(int *size);
        void getPointsFromFlash(speedCalibrationParams_t *params, int size);
        void setStrainPointsToFlash(speedCalibrationParams_t *params, int size);
        void getStrainPointsSizeFromFlash(int *size);
        void getStrainPointsFromFlash(speedCalibrationParams_t *params, int size);
        void setCalculatingProcess(uint8_t calculatingProcess);
        uint8_t getCalculatingProcess(void);

    private:
        speedCalibrationParams_t *_params;
        uint32_t _maxPoints;
        int _sizeOfPoints;
        bool checkSize(int size);
        uint32_t _flashOperationType = FLASH_OPERATION_CPU;
        uint8_t calculatingProcess = true;

};

#endif