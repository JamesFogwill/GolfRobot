
#include "mbed.h"
#include "stdio.h"
#include <cstdio>
#include "iostream"
#include "cstdlib"

class StepperMotor{

    private:
    // initialise the gpio pins for stepper motor
    DigitalOut coilA1;
    DigitalOut coilA2;
    DigitalOut coilB1;
    DigitalOut coilB2;

    // there are 200 steps in 1 rev and x steps in the length of the acuator
    const int phasePerFourSteps = 50;
    const int totalLengthSteps = 1200;
    const int stepsPerRev = 200;

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

    int ballMidPoint[1];
    int boundaries[2];
    int currentPos = 0;

    int data;

    protected:

    public:

    // i can make a function to take half steps too.
    // make a fucntion where i can use the potentiometer to change the speed
    StepperMotor(PinName cA1, PinName cA2, PinName cB1, PinName cB2) : coilA1(cA1), coilA2(cA2), coilB1(cB1), coilB2(cB2) {

    }

    void TestRevCW();
    void TestRevACW();

    bool TestSerial();

    void oldReliable();

    void neverMiss();
    void nMFullStep(int stepsToMove);
    void MoveXStepsCW(int steps);
    void MoveXStepsACW(int steps);

    void stepperOff();

    
    
    //do i make a ramp up function
        

};
