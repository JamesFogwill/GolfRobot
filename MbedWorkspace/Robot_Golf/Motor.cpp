#include "mbed.h"
#include "Motor.h"

void StepperMotor::FullStepCW(){

// loop 200 times as there are 200 steps in 1 rotation.
    for(int i = 0; i <= phasePerRev; i++){
        for(int j = 0; j <= 3; j++){

            coilA1.write(sequenceClockwise[j][0]);
            coilA2.write(sequenceClockwise[j][1]);
            coilB1.write(sequenceClockwise[j][2]);
            coilB2.write(sequenceClockwise[j][3]);

            wait_us(1000);
        }
    }
}

void StepperMotor::FullStepACW(){

// loop 200 times as there are 200 steps in 1 rotation.
    for(int i = 0; i <= phasePerRev; i++){
        for(int j = 0; j <= 3; j++){

            coilA1.write(sequenceAntiClockwise[j][0]);
            coilA2.write(sequenceAntiClockwise[j][1]);
            coilB1.write(sequenceAntiClockwise[j][2]);
            coilB2.write(sequenceAntiClockwise[j][3]);

            wait_us(1000);
        }
    }
}

void StepperMotor::HalfStep(){

//loop 400 times as we are half stepping.
    for(int i = 0; i == (phasePerRev*2); i++){

        coilA1.write(1);
        wait_us(1000);// 1ms
        coilB1.write(1);
        wait_us(1000);
        coilA1.write(0);
        wait_us(1000);
        coilB1.write(0);
        wait_us(1000);
    }

}

void StepperMotor::gameModeOne(){

    while (true) {
        for(int revsCW = 0; revsCW <= 5; revsCW++){

             FullStepCW();

        }
        for(int revsACW = 0; revsACW <= 5; revsACW++){

            FullStepACW();
        }
    }
}

void StepperMotor::stepperOff(){

    coilA1.write(0);
    coilB2.write(0);
    coilB1.write(0);
    coilB2.write(0);

}