#include <Stepper.h>

const int stepsPerRev = 200;

Stepper myStepper(stepsPerRev,8,9,10,11);

int targetSpeed = 800; //  100 is doable with a i increase of 50

void setup() {
  // put your setup code here, to run once:
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  // init serial port
  Serial.begin(9600);

}

void ramp(int target, int dir)
{
  for(int i = 60; i <= target; i += 40) //  maximum i found is stalling at 80
  {
    myStepper.setSpeed(i);
    myStepper.step(dir);
  }

}

void loop() { 

  for (int n = 0; n <= 5; n++)
  {
    // steps one rev clockwise
    Serial.println("Clockwise");
    ramp(targetSpeed, 10);
    myStepper.step(stepsPerRev*4);
    delay(500);

    //steps one rev anticlockwise
    Serial.println("anticlockwise");
    ramp(targetSpeed, -10);
    myStepper.step(-stepsPerRev*4);
    delay(500);
  }

  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);

  delay(100000);

}
