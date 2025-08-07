#ifndef STATIC_TEST_H
#define STATIC_TEST_H

#include <mbed.h>

#include "..//..//include//Global_Variables.h"
#include "SBD.h"


//extern Timer SystemTimer;
extern Timeout delayedAction;

constexpr int maxConditionsSteps = 5;
/**
 * @brief Static Test process class
 * @details This class describe behavior of static test process. Object of this class should call "process" method every tick of main cycle.   
 */
class StaticTest{

public:
    /**
     * @brief Construct a new Static Test object
     * 
     * @param globalVariable current global parameters of test machine.
     */
    StaticTest(globalVariables_t *globalVariable);
    
    /**
     * @brief Destroy the Static Test object
     * 
     */
    ~StaticTest(void);
    
    /**
     * @brief Initialization method of Static Test object. Using to reset variables and reset sample break detection params.
     * 
     */
    void init(void);

    /**
     * @brief Main method that should call every main cycle tick. This method manage steps and conditions of static test procedure.
     * 
     */
    void process(void);

    //double getInitConstDisplMaxVoltage(void);
    //double getInitConstStrainMaxVoltage(void);
    
    /**
     * @brief Get the Init Const Displ Speed value
     * 
     * @return double value of constant dislpacement mode speed value in mm/sec units.  
     */
    double getInitConstDisplSpeed(void);

    /**
     * @brief Get the Init Const Strain Speed value
     * 
     * @return double value of constant strain mode speed value in kN/sec units. 
     */
    double getInitConstStrainSpeed(void);

    /**
     * @brief Get the Init Const Deform Speed object
     * 
     * @return double 
     */
    double getInitConstDeformSpeed(void);

    /**
     * @brief Sample break detection status of sample.
     * 
     */
    SBDStatus_t sampleStatus;

    /**
     * @brief Set the Position Threshold values
     * 
     * @param upperThreshold Positive value of threshold. Units mm.
     * @param lowerThreshold Negative value of threshold. Units mm.
     */
    void setPositionThreshold(double upperThreshold, double lowerThreshold);

    /**
     * @brief Set the Strain Threshold values
     * 
     * @param upperThreshold Positive value of threshold. Units kN.
     * @param lowerThreshold Negative value of threshold. Units kN.
     */
    void setStrainThreshold(double upperThreshold, double lowerThreshold);

    /**
     * @brief Set the Deforamtion Threshold values
     * 
     * @param upperThreshold Positive value of threshold. Units mm.
     * @param lowerThreshold Negative value of threshold. Units mm.
     */
    void setDeformationThreshold(double upperThreshold, double lowerThreshold);

    /**
     * @brief Get the Position Threshold values
     * 
     * @param upperThreshold Current positive value of threshold. Units mm.
     * @param lowerThreshold Current negative value of threshold. Units mm.
     */
    void getPositionThreshold(double &upperThreshold, double &lowerThreshold);

    /**
     * @brief Get the Strain Threshold values
     * 
     * @param upperThreshold Current positive value of threshold. Units kN.
     * @param lowerThreshold Current negative value of threshold. Units kN.
     */
    void getStrainThreshold(double &upperThreshold, double &lowerThreshold);

    /**
     * @brief Get the Deformation Threshold values
     * 
     * @param upperThreshold Current positive value of threshold. Units mm.
     * @param lowerThreshold Current negative value of threshold. Units mm.
     */
    void getDeformationThreshold(double &upperThreshold, double &lowerThreshold);

    void stopTimer();

private:
    globalVariables_t *_globalVariable;
    
    /**
     * @brief Find condition step for current action step.
     * 
     * @param nextIndex current step index
     */
    void findNextPair(int nextIndex);

    /**
     * @brief Save current position, strain, deformation, time.
     * 
     */
    void fixCurrentState(void);

    /**
     * @brief Check current cycles count for vozvrat step value
     * 
     * @param nextIndex current index
     */
    void checkCycles(int nextIndex);

    /**
     * @brief Save current position, strain, deformation
     * 
     */
    void updateValues(void);

    /**
     * @brief Check all steps and convert values units to machine standart units.
     * @details Displacement velocity convert from mm/min to mm/sec.
     * 
     */
    void convertValuesInSteps(void);

    //double initConstDisplMaxVoltage;
    //double initConstStrainMaxVoltage;

    double initConstDisplSpeed;
    double initConstStrainSpeed;
    double initConstDeformSpeed;

    double positionUpperThreshold = 0.02;   //mm
    double positionLowerThreshold = 0.02;   //mm
    double strainUpperThreshold = 1.0;      //kN
    double strainLowerThreshold = 1.0;      //kN
    double deformationUpperThreshold = 0.1; //mm
    double deformationLowerThreshold = 0.1; //mm

    SampleBreakDetection *SBD;
    SampleBreakDetection *SBD_Mode;
    Timer StatTestTimer;
    //void *_caller;

};

#endif