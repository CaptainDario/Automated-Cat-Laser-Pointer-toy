#include <Arduino.h>

//custom
#include <stepper.h>
#include <webserver.h>
#include <credentials.h>


//function pre defines
void set_limits();
void configuration();


void setup() {
  Serial.begin(460800);

  //randomize values
  pinMode(A0, INPUT);
  randomSeed(analogRead(A0));

  //set up wifi
  WiFi.begin(SSID, PWD);
  Serial.print("Connecting to "); Serial.print(SSID);
  Serial.println(" ...");

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
  //check if motors need to be enabled
  enable_motor_for_movement();

  if(rotating){
    if (stepper_bottom.distanceToGo() == 0)
    {
        delay(min_delay_before_new_pos_bottom);
        // set a random position
        int rnd;
        if(stepper_bottom_max > 0)
          rnd = random(0, stepper_bottom_max);
        else
          rnd = random(stepper_bottom_max, 0);

        Serial.print("bottom: "); Serial.println(rnd);
        stepper_bottom.moveTo(rnd);
    }
    stepper_bottom.run();

    if (stepper_top.distanceToGo() == 0)
    {
        delay(min_delay_before_new_pos_top);
        // set a random position
        int rnd;
        if(stepper_top_max > 0)
          rnd = random(0, stepper_top_max);
        else
          rnd = random(stepper_top_max, 0);

        Serial.print("top: "); Serial.println(rnd);
        stepper_top.moveTo(rnd);
    }
    stepper_top.run();
  }  

  set_limits();
  configuration();
  
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



void configuration(){
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
}

void set_limits(){
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