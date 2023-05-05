#include "SetUp.h"

using namespace std;

extern SerialClass mySerial;

bool StepperMotor::TestSerial(){

    data = mySerial.serialRead();
    if(data==2){
        TestRevCW();
        stepperOff();
        return true;
    }
    return false;
    //mySerial.serialWrite(data);
}

void StepperMotor::TestRevCW(){

// loop 200 times as there are 200 steps in 1 rotation.

    for(int i = 0; i <= phasePerFourSteps; i++){
        for(int j = 0; j <= 3; j++){

            coilA1.write(sequenceClockwise[j][0]);
            coilA2.write(sequenceClockwise[j][1]);
            coilB1.write(sequenceClockwise[j][2]);
            coilB2.write(sequenceClockwise[j][3]);

            wait_us(1000);
        }
    }
}

void StepperMotor::TestRevACW(){

// loop 200 times as there are 200 steps in 1 rotation.
    for(int i = 0; i <= phasePerFourSteps; i++){
        for(int j = 0; j <= 3; j++){

            coilA1.write(sequenceAntiClockwise[j][0]);
            coilA2.write(sequenceAntiClockwise[j][1]);
            coilB1.write(sequenceAntiClockwise[j][2]);
            coilB2.write(sequenceAntiClockwise[j][3]);

            wait_us(1000);
        }
    }
}

void StepperMotor::oldReliable(){

    while (true) {
        for(int revsCW = 0; revsCW <= 5; revsCW++){

             TestRevCW();

        }
        for(int revsACW = 0; revsACW <= 5; revsACW++){

            TestRevACW();
        }
    }
}

void StepperMotor::neverMiss(){
    //I NEED TO MAKE IT SO THAT QT STARTS WHEN THIS OPTION IS PRESSED
    //I can have QT looping a start menu to recieve the option number from mbed.
    
    //--------------------------------------------------
    // waits for the boundary coordinates from QT then prints them
    //boundaries[0] = mySerial.serialRead();
    //boundaries[1] = mySerial.serialRead();
    
    cout<<"The boundary positions are:"<<endl;
    cout<<"Top: "<<boundaries[0]<<endl;
    cout<<"Bottom: "<<boundaries[1]<<endl;
    int i = 0;   

    
    //-----------TEST CODE-------------
    boundaries[0] = 310;
    boundaries[1] = 90;
    //ballMidPoint[0] = 100;
    ballMidPoint[0] = mySerial.serialRead();
    
    i = 1;
    while(true){
        
        // reads the position of the ball from Qt if there are coordinates being transmitted and print them
        cout<<"Begin playing"<<endl;

        //comment out to test
        /*
        if (pc.read(ballMidPoint,1)) {
            cout<<ballMidPoint[0]<<endl;
        }
        */
        //create a for loop to test the changing ballmidpoint
        
        ballMidPoint[0] = mySerial.serialRead();

        if(ballMidPoint[0] >= boundaries[1] && ballMidPoint[0] <= boundaries[0]){
            
            //take the boundary coordinates to find the range the golfball can travel in the y axis
            //this can be done outside the while loop.
            int golfRange = boundaries[0] - boundaries[1];
            //finds the scale factor between the golf greens range and the total steps of the actuator
            float scaleFactor = (float)totalLengthSteps/golfRange;
            //finds the balls coordinate scaled to the range
            int scaledBallPos = ballMidPoint[0] - boundaries[1];
            //calculates the exact step position of the motor for that ball coordinate
            int stepPos = round(scaledBallPos * scaleFactor);
            // calculates the total steps the motor needs to move to reach the new position
            int movement = stepPos - currentPos;
            //update the current position to be the new position
            currentPos = stepPos;
            nMFullStep(movement);
            
        }        
        
    i = 0;    
    }   
}

void StepperMotor::nMFullStep(int stepsToMove){

    //the motor moves clockwise
    if (stepsToMove > 0) {
        
        MoveXStepsCW(stepsToMove);
    }
    //if the motor needs to move ant clockwise move that many steps ant clockwise
    else if (stepsToMove < 0) {
        // Takes the magnitude of stepsToMove as it will be negaitve when moving anticlockwise.
        int stepsToMoveACW = (stepsToMove*-1);
        //uses the magnitude to move that many steps anticlockwise
        MoveXStepsACW(stepsToMoveACW);
    }
    else {
        // if the motor does not need to move turn the motor off
        stepperOff();
    }   
}

void StepperMotor::MoveXStepsCW(int steps){
    for(int i = 0; i <= (steps/4); i++){
        for(int j = 0; j <= 3; j++){

            coilA1.write(sequenceClockwise[j][0]);
            coilA2.write(sequenceClockwise[j][1]);
            coilB1.write(sequenceClockwise[j][2]);
            coilB2.write(sequenceClockwise[j][3]);

            wait_us(1000);
        }
    }
}

void StepperMotor::MoveXStepsACW(int steps){
    for(int i = 0; i <= (steps/4); i++){
        for(int j = 0; j <= 3; j++){

            coilA1.write(sequenceAntiClockwise[j][0]);
            coilA2.write(sequenceAntiClockwise[j][1]);
            coilB1.write(sequenceAntiClockwise[j][2]);
            coilB2.write(sequenceAntiClockwise[j][3]);

            wait_us(1000);
        }
    }
}

void StepperMotor::stepperOff(){

    coilA1.write(0);
    coilB2.write(0);
    coilB1.write(0);
    coilB2.write(0);

}