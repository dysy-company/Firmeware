#include "KalmanFltr.h"

KalmanFilter1D::KalmanFilter1D(double q, double r, double f, double h){
    _Q = q;
    _R = r;
    _F = f;
    _H = h;
}

KalmanFilter1D::~KalmanFilter1D(){

}

void KalmanFilter1D::setInitialState(double state, double covariance)
{
    _state = state;
    _covariance = covariance;
}

double KalmanFilter1D::correct(double data)
{
    //time update - prediction
    _X0 = _F * _state;
    _P0 = (_F * _covariance * _F) + _Q;
    //measurement update - correction
    _K = _H * _P0 / (_H * _P0 * _H + _R);
    _state = _X0 + _K * (data - _H * _X0);
    _covariance = (1 - _K * _H) * _P0;  
    return _state;          
}

double KalmanFilter1D::getState(){
    return _state;
}

double KalmanFilter1D::getF(){
    return _F;
}

double KalmanFilter1D::getH(){
    return _H;
}

double KalmanFilter1D::getK(){
    return _K;
}

double KalmanFilter1D::getQ(){
    return _Q;
}

double KalmanFilter1D::getR(){
    return _R;
}

void KalmanFilter1D::setCoefs(double f, double q, double h, double r){
    _F = f;
    _Q = q;
    _H = h;
    _R = r;
}