#include <AccelStepper.h>


//motor bottom
AccelStepper stepper_bottom = AccelStepper(8, D1, D3, D2, D4);
int stepper_bottom_max = 1000;
void setup_motor_bottom();
int min_delay_before_new_pos_bottom = 50;

//motor top
AccelStepper stepper_top = AccelStepper(8, D5, D7, D6, D0);
int stepper_top_max = 1000;
void setup_motor_top();
int min_delay_before_new_pos_top = 50;


//current state (true -> rotating | false -> not rotating)
bool rotating = false;
bool move_bottom_right = false;
bool move_bottom_left = false;
bool move_top_right = false;
bool move_top_left = false;

//set the limits
bool set_bottom_minimum = false;
bool set_bottom_maximum = false;
bool set_top_minimum = false;
bool set_top_maximum = false;


String motor_state;


/*
Set the string on the webserver which indicates indicates the current state.
*/
String set_rotation(const String& var){

  if(var == "STATE"){
    if(rotating){
      motor_state = "Running";
    }
    else{
      motor_state = "Idle";
    }

    return motor_state;
  }
  return String();
}

/*
Disbles all movement instructions to the motors.
This should help prevent them from overheating.
*/
void disable_all_movement(){

  rotating = false;
  move_bottom_right = false;
  move_bottom_left  = false;
  move_top_right    = false;
  move_top_left     = false;

  stepper_top.disableOutputs();
  stepper_bottom.disableOutputs();
}

/*
Enables the motors only when a movement is requried.
This should help prevent them from overheating.
*/
void enable_motor_for_movement(){

  if(move_bottom_right || move_bottom_left)
    stepper_bottom.enableOutputs();

  if(move_top_right || move_top_left)
    stepper_top.enableOutputs();

  if(rotating){
    stepper_top.enableOutputs();
    stepper_bottom.enableOutputs();
  }
}