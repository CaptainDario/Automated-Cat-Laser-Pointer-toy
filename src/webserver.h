#include <ESP8266WiFi.h>
#include <FS.h>
#include <ESPAsyncWebServer.h>
#include <wifi_credentials.h>

AsyncWebServer server(80);


 
void setup_webserver(){


  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/toy_control.html", String(), false, set_state);
  });
  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });

  //Navbar
  server.on("/toy_control.html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/toy_control.html", String(), false, set_state);
  });  
  server.on("/toy_setup.html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/toy_setup.html");
  });
  server.on("/toy_update.html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/toy_update.html");
  });
  server.on("/toy_wifi_setup.html", HTTP_GET, [](AsyncWebServerRequest *request){
    get_nearby_networks();
    request->send(SPIFFS, "/toy_wifi_setup.html", String(), false, set_nearby_networks);
  });
  server.on("/toy_help.html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/toy_help.html");
  });  


  //Controls
  // start rotation
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(LASER_PIN, HIGH);
    disable_all_movement();
    rotating = true;
    enable_motor_for_movement();
    request->send(SPIFFS, "/toy_control.html", String(), false, set_state);
  });
  // stop rotation
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(LASER_PIN, LOW);
    disable_all_movement();
    enable_motor_for_movement();
    request->send(SPIFFS, "/toy_control.html", String(), false, set_state);
  });


  //Setup
  // move bottom
  server.on("/move_bottom_left", HTTP_GET, [](AsyncWebServerRequest *request){
    disable_all_movement();
    move_bottom_left = true;
    enable_motor_for_movement();
    request->send(SPIFFS, "/toy_control.html", String(), false, set_state);
  });
  server.on("/move_bottom_right", HTTP_GET, [](AsyncWebServerRequest *request){
    disable_all_movement();
    move_bottom_right = true;
    enable_motor_for_movement();
    request->send(SPIFFS, "/toy_control.html", String(), false, set_state);
  });
  // move top
  server.on("/move_top_left", HTTP_GET, [](AsyncWebServerRequest *request){
    disable_all_movement();
    move_top_left = true;
    enable_motor_for_movement();
    request->send(SPIFFS, "/toy_control.html", String(), false, set_state);
  });
  server.on("/move_top_right", HTTP_GET, [](AsyncWebServerRequest *request){
    disable_all_movement();
    move_top_right = true;
    enable_motor_for_movement();
    request->send(SPIFFS, "/toy_control.html", String(), false, set_state);
  });
  
  // set bottom min/max
  server.on("/set_bottom_minimum", HTTP_GET, [](AsyncWebServerRequest *request){
    disable_all_movement();
    set_bottom_minimum = true;
    enable_motor_for_movement();
    request->send(SPIFFS, "/toy_control.html", String(), false, set_state);
  });
  server.on("/set_bottom_maximum", HTTP_GET, [](AsyncWebServerRequest *request){
    disable_all_movement();
    set_bottom_maximum = true;
    enable_motor_for_movement();
    request->send(SPIFFS, "/toy_control.html", String(), false, set_state);
  });
  // set top min/max
  server.on("/set_top_minimum", HTTP_GET, [](AsyncWebServerRequest *request){
    disable_all_movement();
    set_top_minimum = true;
    enable_motor_for_movement();
    request->send(SPIFFS, "/toy_control.html", String(), false, set_state);
  });
  server.on("/set_top_maximum", HTTP_GET, [](AsyncWebServerRequest *request){
    disable_all_movement();
    set_top_maximum = true;
    enable_motor_for_movement();
    request->send(SPIFFS, "/toy_control.html", String(), false, set_state);
  });


  //WIFI CREDENTIALS
  server.on("/connect", HTTP_POST, [](AsyncWebServerRequest *request){
    String __SSID;
    String __pwd;

    Serial.println("/connect to new wifi");

    if(request->hasParam("SSID", true)){
      __SSID = request->getParam("SSID", true)->value();

      Serial.println("SSID: " + __SSID);
    }
    if(request->hasParam("pwd", true)){
      __pwd = request->getParam("pwd", true)->value();

      Serial.println("pwd: " + __pwd);
    }

    //check that ssid and password are not empty
    if(__SSID == "" || __pwd == ""){
      Serial.println("Values not set");
    }
    else{
      try_connect_to_wifi(__SSID, __pwd);
    }
    
    //route to the Control page
    request->send(SPIFFS, "/toy_control.html", String(), false, set_state);
  });


  // Start server
  server.begin();
}



