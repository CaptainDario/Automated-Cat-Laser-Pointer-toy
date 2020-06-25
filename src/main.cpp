#include <Arduino.h>

//custom
#include <stepper.h>
#include <webserver.h>
#include <credentials.h>



//motor bottom
AccelStepper stepper_bottom = AccelStepper(8, D1, D3, D2, D4);
int stepper_bottom_max = 1000;
void setup_motor_bottom();

//motor top
AccelStepper stepper_top = AccelStepper(8, D5, D7, D6, D0);
int stepper_top_max = 1000;
void setup_motor_top();



void setup() {
  Serial.begin(460800);
  
  //set up wifi
  WiFi.begin(SSID, PWD);
  Serial.print("Connecting to ");
  Serial.print(SSID); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    WiFi.hostname("DaAppLab cat toy");
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }
  
  // Initialize SPIFFS
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP()); 

  //start the webserver
  setup_webserver();

  //set up stepper motors 
  setup_motor_bottom();
  setup_motor_top();

  Serial.print("Setup finished");
}

void loop() {
  if(rotating){
    if (stepper_bottom.distanceToGo() == 0)
    {
        // Random change to speed, position and acceleration
        // Make sure we dont get 0 speed or accelerations
        delay(50);
        stepper_bottom.moveTo(random(0, stepper_bottom_max));
    }
    stepper_bottom.run();
    if (stepper_top.distanceToGo() == 0)
    {
        // Random change to speed, position and acceleration
        // Make sure we dont get 0 speed or accelerations
        delay(50);
        stepper_top.moveTo(random(0, stepper_top_max));
    }
    stepper_top.run();
  }  

  //slow movment for configuration 
  //bottom
  if(move_bottom_left){
    stepper_bottom.moveTo(stepper_bottom.currentPosition() + 5);
    stepper_bottom.run();
  }
  if(move_bottom_right){
    stepper_bottom.moveTo(stepper_bottom.currentPosition() - 5);
    stepper_bottom.run();
  }
  //top
  if(move_top_right){
    stepper_top.moveTo(stepper_top.currentPosition() + 5);
    stepper_top.run();
  }
  if(move_top_left){
    stepper_top.moveTo(stepper_top.currentPosition() - 5);
    stepper_top.run();
  }

  //set limits
  if (set_bottom_minimum)
  {
    stepper_bottom.setCurrentPosition(0);
    set_bottom_minimum = false;
    Serial.print(stepper_top.currentPosition());
  }
  if (set_bottom_maximum)
  {
    stepper_bottom_max = stepper_bottom.currentPosition();
    set_bottom_maximum = false;
    Serial.print(stepper_bottom_max);
  }
  if (set_top_minimum)
  {
    stepper_top.setCurrentPosition(0);
    set_top_minimum = false;
    Serial.print(stepper_top.currentPosition());
  }
  if (set_top_maximum)
  {
    stepper_top_max = stepper_top.currentPosition();
    set_top_maximum = false;
    Serial.print(stepper_top_max);
  }
  
}

void setup_motor_bottom(){
  //init stepper 1 (bottom)
  stepper_bottom.setMaxSpeed(2000);
  stepper_bottom.setAcceleration(2000);
  stepper_bottom.setSpeed(2000);
}

void setup_motor_top(){
  //init stepper 2 (top/laser pointer)
  stepper_top.setMaxSpeed(2000);
  stepper_top.setAcceleration(2000);
  stepper_top.setSpeed(2000);

}