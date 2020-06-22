#include <Arduino.h>
#include <AccelStepper.h>

//motor 1
AccelStepper stepper_1 = AccelStepper(8, D1, D3, D2, D4);
int end_point_1 = 1024 * 4;

//motor 2
AccelStepper stepper_2 = AccelStepper(8, D5, D7, D6, D8);
int end_point_2 = 1024;



void setup() {
  //init stepper 1
  stepper_1.setMaxSpeed(2000);
  stepper_1.setAcceleration(2000);
  stepper_1.setSpeed(2000);
  stepper_1.moveTo(end_point_1);

  //init stepper 2
  stepper_2.setMaxSpeed(20000);
  stepper_2.setAcceleration(1000);
  stepper_2.setSpeed(20000);
  stepper_2.moveTo(end_point_2);

  Serial.begin(9600);
}

void loop() {
  if (stepper_1.distanceToGo() == 0)
  {
      // Random change to speed, position and acceleration
      // Make sure we dont get 0 speed or accelerations
      delay(100);
      stepper_1.moveTo(rand() % end_point_1);
  }
  stepper_1.run();
  if (stepper_2.distanceToGo() == 0)
  {
      // Random change to speed, position and acceleration
      // Make sure we dont get 0 speed or accelerations
      delay(100);
      stepper_2.moveTo(rand() % end_point_2);
  }
  stepper_2.run();
}