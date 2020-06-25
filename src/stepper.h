#include <AccelStepper.h>

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

// Replaces placeholder with toy-state val
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

void disable_all_movement(){
  rotating = false;
  move_bottom_right = false;
  move_bottom_left  = false;
  move_top_right    = false;
  move_top_left     = false;
}