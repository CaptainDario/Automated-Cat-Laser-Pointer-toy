#include <Arduino.h>

//custom
#include <stepper.h>
#include <webserver.h>
#include <credentials.h>



//motor bottom
AccelStepper stepper_1 = AccelStepper(8, D1, D3, D2, D4);
int stepper_1_max = 1000;
void setup_motor_1();

//motor top
AccelStepper stepper_2 = AccelStepper(8, D5, D7, D6, D0);
int stepper_2_max = 1000;
int end_point_2 = 1024;



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
  setup_motor_1();
  //init stepper 2
  stepper_2.setMaxSpeed(20000);
  stepper_2.setAcceleration(1000);
  stepper_2.setSpeed(20000);
  stepper_2.moveTo(end_point_2);

  Serial.print("Setup finished");
}

void loop() {
  if(rotating){
    if (stepper_1.distanceToGo() == 0)
    {
        // Random change to speed, position and acceleration
        // Make sure we dont get 0 speed or accelerations
        delay(50);
        stepper_1.moveTo(random(0, stepper_1_max));
    }
    stepper_1.run();
    if (stepper_2.distanceToGo() == 0)
    {
        // Random change to speed, position and acceleration
        // Make sure we dont get 0 speed or accelerations
        delay(50);
        stepper_2.moveTo(random(0, stepper_2_max));
    }
    stepper_2.run();
  }  

  //slow movment for configuration 
  //bottom
  if(move_bottom_left){
    stepper_1.moveTo(stepper_1.currentPosition() + 1);
    stepper_1.run();
  }
  if(move_bottom_right){
    stepper_1.moveTo(stepper_1.currentPosition() - 1);
    stepper_1.run();
  }
  //top
  if(move_top_right){
    stepper_2.moveTo(stepper_2.currentPosition() + 1);
    stepper_2.run();
  }
  if(move_top_left){
    stepper_2.moveTo(stepper_2.currentPosition() - 1);
    stepper_2.run();
  }

  //set limits
  if (set_bottom_minimum)
  {
    stepper_1.setCurrentPosition(0);
    set_bottom_minimum = false;
    Serial.print(stepper_1.currentPosition());
  }
  if (set_bottom_maximum)
  {
    stepper_1_max = stepper_1.currentPosition();
    set_bottom_maximum = false;
    Serial.print(stepper_1_max);
  }
  if (set_top_minimum)
  {
    stepper_2.setCurrentPosition(0);
    set_top_minimum = false;
    Serial.print(stepper_2.currentPosition());
  }
  if (set_top_maximum)
  {
    stepper_2_max = stepper_2.currentPosition();
    set_top_maximum = false;
    Serial.print(stepper_2_max);
  }
  
}

void setup_motor_1(){
  //init stepper 1
  stepper_1.setMaxSpeed(2000);
  stepper_1.setAcceleration(2000);
  stepper_1.setSpeed(2000);
}