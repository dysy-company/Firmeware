#include "Calibration.h"
//default is 50
Calibration::Calibration(int maxPoints){
    this->_sizeOfPoints = -1;
    this->_sizeOfSections = 0;
    this->_maxPoints = (uint32_t)maxPoints;
    this->_points = new point_t[2];
    this->_sections = new section_t[1];
    basic = new BasicElements();
}
Calibration::~Calibration(){
    delete[] this->_points;
    delete[] this->_sections;
    this->_sizeOfPoints = -1;
    delete basic;
}

bool Calibration::checkSize(int size){
    if (size >= 0 && size <= (int)this->_maxPoints){
        return true;
    }else{
        return false;
    }
}

uint32_t Calibration::getMaxPoints(){
    return this->_maxPoints;
}

bool Calibration::getNumberOfSections(int &numberOfSections){
    if(this->_sizeOfSections > 0){
        numberOfSections = this->_sizeOfSections;
        return true;
    }else{
        numberOfSections = -1;
        return false;
    }
}

//delete all points and reallocate points, max number is maxPoints
bool Calibration::setNumberOfPoints(int numberOfPoints){
    if (checkSize(numberOfPoints)){
        delete[] this->_points;
        _points = new point_t[numberOfPoints];
        _sizeOfPoints = numberOfPoints;
        return true;
    }else{
        return false;
    }
}
bool Calibration::getNumberOfPoints(int &numberOfPoints){
    numberOfPoints = this->_sizeOfPoints;
    if(_sizeOfPoints > 0){
        return true;
    }else{
        return false;
    }
}

bool Calibration::setPoints(point_t *points, int length){
    if (this->setNumberOfPoints(length)){
        for(int i = 0; i < length; i++){
            this->_points[i].xRAW = points[i].xRAW;
            this->_points[i].yPhy = points[i].yPhy;
        }
        return true;
    }
    return false;
}
bool Calibration::getPoints(point_t *points, int &length){
        if(this->_sizeOfPoints >= 2){
            for(int i = 0; i < length; i++){
                points[i].xRAW = this->_points[i].xRAW;
                points[i].yPhy = this->_points[i].yPhy;
            }
            return true;
        }else{
            return false;
        }
}

void Calibration::sortPointsByX(){
    point_t temp;
    for (int i = 0; i < _sizeOfPoints - 1; i++) {
        for (int j = 0; j < _sizeOfPoints - i - 1; j++) {
            if (this->_points[j].xRAW > this->_points[j + 1].xRAW) {
                temp.xRAW = this->_points[j].xRAW;
                temp.yPhy = this->_points[j].yPhy;
                this->_points[j].xRAW = this->_points[j + 1].xRAW;
                this->_points[j].yPhy = this->_points[j + 1].yPhy;
                this->_points[j + 1].xRAW = temp.xRAW;
                this->_points[j + 1].yPhy = temp.yPhy;
            }
        }
    }
}

void Calibration::sortPointsByY(){
    point_t temp;
    for (int i = 0; i < _sizeOfPoints - 1; i++) {
        for (int j = 0; j < _sizeOfPoints - i - 1; j++) {
            if (this->_points[j].yPhy > this->_points[j + 1].yPhy) {
                temp.xRAW = this->_points[j].xRAW;
                temp.yPhy = this->_points[j].yPhy;
                this->_points[j].xRAW = this->_points[j + 1].xRAW;
                this->_points[j].yPhy = this->_points[j + 1].yPhy;
                this->_points[j + 1].xRAW = temp.xRAW;
                this->_points[j + 1].yPhy = temp.yPhy;
            }
        }
    }
}

bool Calibration::calculateSections(){
    if(checkSize(this->_sizeOfPoints) && this->_sizeOfPoints >= 2){
        this->sortPointsByX();
        delete[] this->_sections;
        this->_sections = new section_t[this->_sizeOfPoints - 1];
        for (int i = 0; i < this->_sizeOfPoints - 1; i++){
            this->_sections[i].point0.xRAW = this->_points[i].xRAW;
            this->_sections[i].point0.yPhy = this->_points[i].yPhy;
            this->_sections[i].point1.xRAW = this->_points[i + 1].xRAW;
            this->_sections[i].point1.yPhy = this->_points[i + 1].yPhy;
            this->_sections[i].equation.k =      (this->_sections[i].point1.yPhy - this->_sections[i].point0.yPhy) 
                                    /   (this->_sections[i].point1.xRAW - this->_sections[i].point0.xRAW);
            this->_sections[i].equation.b = ((this->_sections[i].point0.xRAW * this->_sections[i].point1.yPhy - this->_sections[i].point1.xRAW * this->_sections[i].point0.yPhy)
                                    /   (this->_sections[i].point1.xRAW - this->_sections[i].point0.xRAW)) * (-1);
        }
        this->_sizeOfSections = this->_sizeOfPoints - 1;
        return true;
    }else{
        if(this->_sizeOfPoints == 0){
            this->_sizeOfSections = 0;
        }
        return false;
    }
}

double Calibration::getCalibratedValue(double xRAWValue){
    if(this->_sizeOfSections >= (uint32_t)1){
        int lastIndex = 0;
        for(uint32_t i = 0; i < this->_sizeOfSections; i++){
            if(this->_sections[i].point1.xRAW >= xRAWValue){
                return (this->_sections[i].equation.k * xRAWValue + this->_sections[i].equation.b);
            }
            lastIndex = i;
        }
        return (this->_sections[lastIndex].equation.k * xRAWValue + this->_sections[lastIndex].equation.b);
    }else{
        return NAN;
    }
}