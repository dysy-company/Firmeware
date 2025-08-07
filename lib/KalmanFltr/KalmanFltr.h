#ifndef KALMAN_FILTER_H
#define KALMAN_FILTER_H
#include <mbed.h>

class KalmanFilter1D{
    private:
        double _X0;// predicted state
        double _P0; // predicted covariance
        double _state;
        double _covariance;
        double _K;
        double _F = 1; // factor of real value to previous real value
            /*
                F — переменная описывающая динамику системы, 
                в случае с топливом — это может быть коэффициент 
                определяющий расход топлива на холостых оборотах 
                за время дискретизации (время между шагами алгоритма). 
                Однако помимо расхода топлива, существуют ещё и заправки… 
                поэтому для простоты примем эту переменную равную 1 
                (то есть мы указываем, что предсказываемое значение 
                будет равно предыдущему состоянию).
            */
        double _Q = 2; // measurement noise
            /*
                Q — определение шума процесса является более сложной 
                задачей, так как требуется определить дисперсию процесса, 
                что не всегда возможно. В любом случае, можно подобрать 
                этот параметр для обеспечения требуемого уровня фильтрации.
            */
        double _H = 1; // factor of measured value to real value
            /*
                H - матрица определяющая отношение между измерениями и 
                состоянием системы, пока без объяснений примем 
                эту переменную также равную 1.
            */
        double _R = 15; // environment noise
            /*
                R - ошибка измерения может быть определена испытанием 
                измерительных приборов и определением погрешности их измерения.
            */
    public:
        KalmanFilter1D(double q, double r, double f, double h);
        ~KalmanFilter1D();
        //first set state and covariance for filtering
        void setInitialState(double state, double covariance);
        //process and return last filtered value
        double correct(double data);
        //set F, Q, H, R coefs
        void setCoefs(double f, double q, double h, double r);
        double getF();
        double getQ();
        double getH();
        double getR();
        double getK();
        double getState();
        
};
/*
    Применение...
    double fuelData[1000]; 
    GetData(fuelData);
    filtered = new List<double>();
    KalmanFilter1D kalman = new KalmanFilter1D(f: 1, h: 1, q: 2, r: 15);  задаем F, H, Q и R
    kalman.SetState(fuelData[0], 0.1);  Задаем начальные значение State и Covariance
    foreach(var d in fuelData)
    {
        kalman.Correct(d);  Применяем алгоритм
        filtered.Add(kalman.State);  Сохраняем текущее состояние 
    }
*/
#endif