#include<Stepper.h>

const int stepsPerRev = 200;
Stepper myStepper(stepsPerRev,8,9,10,11);

void setup() {

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  Serial.begin(9600);

}

// function to ramp up the speed which stops the motor from stalling
void ramp(int targetSpeed, int direction){

  for(int currentSpeed = 60; currentSpeed <= targetSpeed; currentSpeed += 10){
    
    myStepper.setSpeed(currentSpeed);
    myStepper.step(direction); // steps in the 
  }
  
}

void Slidey(){

    // revolutions per minute so the speed of the motor
    int rpm = 180;

    for(int n = 0; n <= 1; n ++){

    // clockwise motion
    ramp(rpm, 10);
    myStepper.step(stepsPerRev*5.1);
    
    //anticlockwise motion
    ramp(rpm, -10);
    myStepper.step(-stepsPerRev*5.1);
    }
}

// uses joystick control
void Joyful(){

}

int startUp(){

  Serial.println("What operation should the motor run?");
  Serial.println("1: Test");
  Serial.println("2: Gamemode Slidey");
  Serial.println("3: Gamemode Joyful ");
  Serial.println("4: Exit");

  while (Serial.available() == 0){};

  int option = Serial.parseInt();

  return option;
}

void loop() {

  int choice = startUp();
  
  if (choice == 1){
    
    
  }
  else if (choice == 2){

    Slidey();
  }
  else if (choice == 3){

  }
  else if (choice == 4){
    
    pinMode(8, LOW);
    pinMode(9, LOW);
    pinMode(10, LOW);
    pinMode(11, LOW);

    exit(0);
  }


}
