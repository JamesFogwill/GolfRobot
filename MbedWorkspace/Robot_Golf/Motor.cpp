#include "SetUp.h"


using namespace std;

extern SerialClass mySerial;

bool StepperMotor::TestSerial(){

    data = mySerial.serialRead();
    if(data==200){
        TestRevCW();
        stepperOff();
        return true;
    }
    return false;
    //mySerial.serialWrite(data);
}

void StepperMotor::sequenceCW(int delay){
    for(int j = 0; j <= 3; j++){
        coilA1.write(sequenceClockwise[j][0]);
        coilA2.write(sequenceClockwise[j][1]);
        coilB1.write(sequenceClockwise[j][2]);
        coilB2.write(sequenceClockwise[j][3]);
        wait_us(delay);
    }
};
void StepperMotor::sequenceACW(int delay){
    for(int j = 0; j <= 3; j++){
        coilA1.write(sequenceAntiClockwise[j][0]);
        coilA2.write(sequenceAntiClockwise[j][1]);
        coilB1.write(sequenceAntiClockwise[j][2]);
        coilB2.write(sequenceAntiClockwise[j][3]);
        wait_us(delay);
    }
};

void StepperMotor::TestRevCW(){

// loop 200 times as there are 200 steps in 1 rotation.
    for(int i = 0; i <= phasePerFourSteps; i++){
       sequenceCW(1000);
    }
}

void StepperMotor::TestRevACW(){

// loop 200 times as there are 200 steps in 1 rotation.
    for(int i = 0; i <= phasePerFourSteps; i++){
        sequenceACW(1000);
    }
}

int StepperMotor::accelDecelCW(int accOrDecc, int steps){

    if(accOrDecc == 1){
        for(int p = motorMinSpeed; p >= motorMaxSpeed; p -= 25 ){
            sequenceCW(p);
            steps-=4;
            if(steps <= 0){
                break;
            }
        }
        return steps;
    }
    else if (accOrDecc == 0) {
        for(int p = motorMaxSpeed; p >= motorMinSpeed; p += 25 ){
            sequenceCW(p);
            steps -=4;
            if (steps <= 0) {
            break;
            }
        }
        return steps;
    }
    else {
        return steps;
    }     
};

int StepperMotor::accelDecelACW(int accOrDecc, int steps){
    // keeps track of the total
    int totalSteps = steps;
    //keeps track of current speed, sets lowest speed to start.
    // accelerating
    if(accOrDecc == 1){
        // loop until max speed or minimum delay has been reached
        for(int p = motorMinSpeed; p >= motorMaxSpeed; p -= 25 ){
            sequenceACW(p);// this is 4 steps so must - 4 from steps
            steps -= 4;
            //check to make sure we have the room to decelerate
            //if the stepsleft is half the total start to decelerate
            currentDelay = p;

            if (steps <= (totalSteps/2)) {
                accOrDecc = 0;
                break;
            }
        }
        
    }
    //decelerating
    // this assumes that it takes the same number of steps to accelerate as it does to decelerate
    if (accOrDecc == 0) {
        for(int p = currentDelay; p <= motorMinSpeed; p += 25 ){
            sequenceACW(p);
            steps -=4;
        }
        return steps;
    }
    else {
        return steps;
    }     
};



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
    boundaries[0] = mySerial.serialRead();
    boundaries[1] = mySerial.serialRead();
    
    cout<<"The boundary positions are:"<<endl;
    cout<<"Top: "<<boundaries[0]<<endl;
    cout<<"Bottom: "<<boundaries[1]<<endl;
    int i = 0;   

    
    //-----------TEST CODE-------------
    //boundaries[0] = 310;
    //boundaries[1] = 90;
    //ballMidPoint[0] = 100;
    
    i = 1;
    while(true){
        
        // reads the position of the ball from Qt if there are coordinates being transmitted and print them
        //cout<<"Begin playing"<<endl;

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

    //if the motor needs to move cw
    if (stepsToMove > 0) {
        // move that many steps cw
        MoveXStepsCW(stepsToMove);
    }
    //if the motor needs to move acw
    else if (stepsToMove < 0) {
        // Takes the magnitude of stepsToMove as it will be negaitve when moving acw.
        int stepsToMoveACW = (stepsToMove*-1);
        //uses the magnitude to move that many steps acw
        MoveXStepsACW(stepsToMoveACW);
    }
    else {
        // if the motor does not need to move turn the motor off
        stepperOff();
    }   
}

void StepperMotor::MoveXStepsCW(int steps){
    
    // accelerate = 1 decelerate = 0
    int AOD = 1;
    // accelerates te motor and stores the remaining movement
    int stepsLeft = accelDecelCW(AOD, steps);
    //works out how many steps have been moved (needed for decelerate)
    int stepsMoved = steps - stepsLeft;
    //work out how many steps left before deceleration
    int stepsLeftToDec = stepsLeft - stepsMoved;
    if(stepsLeft >= 5){
        // divide by 4 because each cycle of the inside for loop is 4 steps
        // the outside loop is step*4
        for(int i = 0; i <= (stepsLeftToDec/4); i++){
        sequenceCW(motorMaxSpeed);
            stepsLeft -=4;
        }
        //sets to deccelerate
        AOD = 0;
        //decelerate
        accelDecelCW(AOD,stepsLeft);
    }
    else {
        
        stepperOff();
    }
    //THE ABOVE STILL NEEDS TESTING AND THE ACW IMPLEMENTED
    // IT SHOULD ACCEL AND DECEL CORRECETLY
}

void StepperMotor::MoveXStepsACW(int steps){

    int AOD = 1;
    int stepsLeft = accelDecelACW(AOD, steps);
    int stepsMoved = steps - stepsLeft;
    int stepsLeftToDec = stepsLeft - stepsMoved;

    if(stepsLeft >= 5){
        // divide by 4 because each cycle of the inside for loop is 4 steps
        // the outside loop is step*4
        for(int i = 0; i <= (stepsLeftToDec/4); i++){
        sequenceACW(motorMaxSpeed);
            stepsLeft -=4;
        }
        //sets to deccelerate
        AOD = 0;
        //decelerate
        accelDecelACW(AOD,stepsLeft);
    }
    else {
        
        stepperOff();
    }
}

void StepperMotor::stepperOff(){

    coilA1.write(0);
    coilB2.write(0);
    coilB1.write(0);
    coilB2.write(0);

}