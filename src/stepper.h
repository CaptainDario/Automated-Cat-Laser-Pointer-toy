#include <AccelStepper.h>


void random_rotation(AccelStepper stepper_1, int max_1, AccelStepper stepper_2, int max_2){
  if (stepper_1.distanceToGo() == 0)
  {
      // Random change to speed, position and acceleration
      // Make sure we dont get 0 speed or accelerations
      delay(100);
      stepper_1.moveTo(rand() % max_1);
  }
  stepper_1.run();
  if (stepper_2.distanceToGo() == 0)
  {
      // Random change to speed, position and acceleration
      // Make sure we dont get 0 speed or accelerations
      delay(100);
      stepper_2.moveTo(rand() % max_2);
  }
  stepper_2.run();
}