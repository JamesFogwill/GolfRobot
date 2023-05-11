#include "SetUp.h"
using namespace std;

SerialClass mySerial;

int main()
{   
    int option;
    bool serialWork = true; 
    //creates steppermotor object and initialises it with these pins
    StepperMotor myMotor(PF_13, PE_9, PE_11, PF_14);

    //myMotor.neverMiss();
    
    //serialWork = myMotor.TestSerial();

    option = mySerial.serialRead();

    switch (option) {

            case 1:
                //run test code, will make motor move one revolution cw and acw
                myMotor.TestRevCW();
                myMotor.TestRevACW();
                myMotor.stepperOff();

                break;

            case 2:
                //runs the first game mode
                //moves the hole endlessly fully both ways across the linear actuator
                myMotor.oldReliable();
                //this will never happen as the above is a while(true)
                myMotor.stepperOff();

                break;

            case 3:

                
                myMotor.neverMiss();
                myMotor.stepperOff();

                break;

            case 4:

                
                //myMotor.MoveXStepsCW(movement);
                myMotor.stepperOff();
                break;
            
            case 5:

                //turns the stepper off
                //exits the program

                myMotor.stepperOff();

                break;
            default:

                cout<<"Invalid choice please choose again"<<endl;

                break;
        }

    return 0;
    
}