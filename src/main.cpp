#include <Arduino.h>
#include <WiFiManager.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>

//custom
#include <stepper.h>
#include <webserver.h>



//motor 1
AccelStepper stepper_1 = AccelStepper(8, D1, D3, D2, D4);
int end_point_1 = 1024 * 4;

//motor 2
AccelStepper stepper_2 = AccelStepper(8, D5, D7, D6, D8);
int end_point_2 = 1024;



void setup() {
  //Serial.begin(9600);
  
  //set up wifi
  WiFiManager wifiManager;
  wifiManager.autoConnect("DaAppLab's Laser pointer toy");

  setup_webserver();

  //set up stepper motors 
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

  Serial.print("Setup finished");
}

void loop() {
  random_rotation(stepper_1, end_point_1, stepper_2, end_point_2);
}