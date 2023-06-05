#include "SetUp.h"


using namespace std;

extern SerialClass mySerial;

bool StepperMotor::TestSerial(){
    // function i used to test the serial, if the correct data is received, move the motor
    data = mySerial.serialRead();
    if(data==200){
        TestRevCW();
        stepperOff();
        return true;
    }
    // echo back the data to qt, checks the data is correct on the mbed side
    mySerial.serialWrite(data, 3);
    return false;
    
}
// does 4 steps of the motor clockwise, takes in the delay which controls the speed of the motor
void StepperMotor::sequenceCW(int delay){
    for(int j = 0; j <= 3; j++){
        coilA1.write(sequenceClockwise[j][0]);
        coilA2.write(sequenceClockwise[j][1]);
        coilB1.write(sequenceClockwise[j][2]);
        coilB2.write(sequenceClockwise[j][3]);
        wait_us(delay);
    }
};
// does 4 steps of the motor anticlockwise, takes in the delay which controls the speed of the motor
void StepperMotor::sequenceACW(int delay){
    for(int j = 0; j <= 3; j++){
        coilA1.write(sequenceAntiClockwise[j][0]);
        coilA2.write(sequenceAntiClockwise[j][1]);
        coilB1.write(sequenceAntiClockwise[j][2]);
        coilB2.write(sequenceAntiClockwise[j][3]);
        wait_us(delay);
    }
};
// new function that takes the target position, moves the motor to the target in steps of 12
// this makes smoother motor movements and stops the motor loosing steps when its told to move one step and it possibly doesnt.
void StepperMotor::simpleMove(int target) {

    for(int i = 0; i < 20; i++){
        // hysterisis of 10 each side to make sure its not moving less than 10 steps
        if(target > simplePos + 10) {
            // updates the position by 12 steps and moves 12 steps
            simplePos += 12;
            sequenceCW(1000);// 4 steps each
            sequenceCW(1000);
            sequenceCW(1000); }
        if(target < simplePos - 10) {
            simplePos -= 12;
            sequenceACW(1000);
            sequenceACW(1000);
            sequenceACW(1000); }

    }
}

void StepperMotor::TestRevCW(){

// loop 50 times as there are 200 steps in 1 rotation and 4 steps in each sequence
    for(int i = 0; i <= revolutionSteps; i++){
       sequenceCW(1200);
    }
}

void StepperMotor::TestRevACW(){

// loop 50 times as there are 200 steps in 1 rotation.
    for(int i = 0; i <= revolutionSteps; i++){
        sequenceACW(1200);
    }
}

int StepperMotor::accelDecelCW(int accOrDecc, int steps){
    // function to accelerate and decelerate the motor
    // takes in the steps needed to move for predictive breaking and whether we need to accel or decel
    // if accelerate then increment the delay in the stepper until min delay and max speed is reached
    if(accOrDecc == 1){
        for(int p = motorMinSpeed; p >= motorMaxSpeed; p -= 25 ){
            sequenceCW(p);
            // minus 4 steps from each sequence to keep track of how many steps left
            steps-=4;
            // if steps  is 0 then stop accelerating
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
                // if have travelled half the steps then start to decel
                accOrDecc = 0;
                break;
            }
        }
        
    }
    //decelerating
    // this assumes that it takes the same number of steps to accelerate as it does to decelerate
    if (accOrDecc == 0) {
        // increase the delay in 25 increments
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
    // game mode which moves the motor from one side to the other
    // can change the speed by playing with the delay in TestRevA/CW()
    while (true) {
        //there are 5 revolutions on the gantry so loop one revolution 5 times
        for(int revsCW = 0; revsCW <= 5; revsCW++){
             TestRevCW();
        }
        for(int revsACW = 0; revsACW <= 5; revsACW++){
            TestRevACW();
        }
    }
}

void StepperMotor::neverMiss(){
  
    while(true){
        
        ballMidPoint[0] = mySerial.serialRead();

        simpleMove(ballMidPoint[0]);

// theory, stepper motor doesnt actually move unless the steps required to move is significant so we loose accuracy when moving very small amounf of steps. Added the plus and minus 50 to make sure only a significant amount of steps are ever moved, this does mean the accuracy of the hole is to 50 steps.

// this is not implemented in the simple move function

        //if (ballMidPoint[0] > (currentPos+25) || ballMidPoint[0] < (currentPos-25)) {
            // works out the m
            //int movement = ballMidPoint[0] - currentPos;
            //currentPos = ballMidPoint[0];
            //nMFullStep(movement);
            
            //wait_us(1500);
       // }
        

   
    }   
}

// function to decide whether the motor needs to move acw or cw, now redundant because simple move is so much better
void StepperMotor::nMFullStep(int stepsToMove){

    //if the motor needs to move cw
    if (stepsToMove > 1) {
        // move that many steps cw
        MoveXStepsCW(stepsToMove);
    }
    //if the motor needs to move acw
    else if (stepsToMove < -1) {
        // Takes the magnitude of stepsToMove as it will be negaitve when moving acw.
        int stepsToMoveACW = (stepsToMove*-1);
        //uses the magnitude to move that many steps acw
        MoveXStepsACW(stepsToMoveACW);
    }
    else {
        // if the motor does not need to move turn the motor off
        //stepperOff();
    }   
}

// function to move the motor the required steps
// also accel and decel however redundant because hardware issue fixed (not enough current)
// simple move now does this
void StepperMotor::MoveXStepsCW(int steps){
    
    //-----------------------NORMAL OPERATION-----------------------

    for(int i = 0; i <= steps/4; i++){
    sequenceCW(1000);
        
    }
    
    

    //--------------ACCELLERATE AND DECELERATE--------------
    /*
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
    */
    //THE ABOVE STILL NEEDS TESTING AND THE ACW IMPLEMENTED
    // IT SHOULD ACCEL AND DECEL CORRECETLY
}

void StepperMotor::MoveXStepsACW(int steps){
    //---------------NORMAL----------------

    
    // if the round is not there it will truncate the value, eg 2.5 becomes 2
    for(int i = 0; i <= steps/4; i++){
    sequenceACW(1000);
    }
    
    

    //----------------------ACCEL DECEL -------------------------
    /*
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
    */
}

// function to turn the stepper off 
void StepperMotor::stepperOff(){

    coilA1.write(0);
    coilB2.write(0);
    coilB1.write(0);
    coilB2.write(0);

}