#include "mbed.h"

class StepperMotor{

    private:
    // initialise the gpio pins for stepper motor
    DigitalOut coilA1;
    DigitalOut coilA2;
    DigitalOut coilB1;
    DigitalOut coilB2;

    // there are 200 steps in 1 rev and x steps in the length of the acuator
    const int phasePerRev = 50;
    const int totalLengthSteps = 400;

    // the sequence of activation of the coils to get the motor to move clockwise
    const int sequenceClockwise[4][4] = {
        {1,0,1,0},
        {0,1,1,0},
        {0,1,0,1},
        {1,0,0,1}
    };

    const int sequenceAntiClockwise[4][4] = {

        {1,0,0,1},
        {0,1,0,1},
        {0,1,1,0},
        {1,0,1,0}
    };

    protected:

    public:

    // i can make a function to take half steps too.
    // make a fucntion where i can use the potentiometer to change the speed
    StepperMotor(PinName cA1, PinName cA2, PinName cB1, PinName cB2) : coilA1(cA1), coilA2(cA2), coilB1(cB1), coilB2(cB2) {

    }

    void FullStepCW();

    void FullStepACW();
    
    void HalfStep();

    void gameModeOne();

    void stepperOff();
        

};
