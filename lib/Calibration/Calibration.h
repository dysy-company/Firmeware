#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <mbed.h>
#include "..//BasicElements/BasicElements.h"

typedef struct equation{
    double k;
    double b;
}equation_t;

typedef struct point{
    double xRAW;
    double yPhy;
}point_t;

typedef struct section{
    point_t point0;
    point_t point1;
    equation_t equation;
}section_t;



class Calibration{
    public:
        Calibration(int maxPoints);
        ~Calibration();
        bool setNumberOfPoints(int numberOfPoints);
        bool getNumberOfPoints(int &numberOfPoints);
        bool setPoints(point_t *points, int length);
        bool getPoints(point_t *points, int &length);
        bool calculateSections();
        double getCalibratedValue(double xRAWValue);
        uint32_t getMaxPoints();
        bool getNumberOfSections(int &numberOfSections);
    private:
        point_t *_points;
        section_t *_sections;
        int _sizeOfPoints;
        uint32_t _maxPoints;
        uint32_t _sizeOfSections;
        bool checkSize(int size);
        void sortPointsByX();
        void sortPointsByY();
        BasicElements *basic;
};

#endif