#include <AccelStepper.h>
#include <pin.h>

//motor bottom
AccelStepper stepper_bottom = AccelStepper(8, stepper_bottom_pin_1, stepper_bottom_pin_2,
                                              stepper_bottom_pin_3, stepper_bottom_pin_4);
int stepper_bottom_max = 1000;
void setup_motor_bottom();
int min_delay_before_new_pos_bottom = 50;

//motor top
AccelStepper stepper_top = AccelStepper(8, stepper_top_pin_1, stepper_top_pin_2, 
                                            stepper_top_pin_3, stepper_top_pin_4);
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


String current_state = String();


/*
Set the string on the webserver which indicates indicates the current state.
*/
String set_state(const String& var){

  current_state = String();

  if(var == "STATE"){
    if(rotating){
      current_state = "Running";
    }
    else if(move_bottom_left || move_bottom_right ||
          set_bottom_minimum || set_bottom_maximum){
      current_state = "callibrating bottom";
    }
    else if(move_top_left || move_top_right ||
          set_top_minimum || set_top_maximum){
      current_state = "callibrating top";
    }
    else{
      current_state = "Idle";
    }
  }
  return current_state;
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