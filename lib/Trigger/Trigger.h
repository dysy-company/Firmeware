#ifndef TRIGGER_H
#define TRIGGER_H

#define TRIGGER_RISE_EDGE       0
#define TRIGGER_FALL_EDGE       1


class Trigger{
    public:
        Trigger(int triggerType);
        ~Trigger();
        //push new state and return trigger state
        bool push(bool currentState);
        //return trigger state
        bool getState();
    private:
        int _triggerType;
        bool _prevState = false;
        bool _currentState = false;
        bool _triggerState = false;
};

#endif