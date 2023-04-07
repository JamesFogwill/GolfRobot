/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "Motor.h"
#include "stdio.h"
#include <cstdio>

//Serial(USBTX,USBRX);

int main()
{
    StepperMotor myMotor(PF_13, PE_9, PE_11, PF_14);

    //--------------test functions--------------
    //myMotor.FullStepCW();
    //myMotor.FullStepACW();
    //myMotor.HalfStep();

    //cout<<"Test"<<endl;
    
    myMotor.gameModeOne();
    myMotor.stepperOff();

}
