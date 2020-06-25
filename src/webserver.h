#include <ESP8266WiFi.h>
#include <FS.h>
#include <ESPAsyncWebServer.h>

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

  // start rotation
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    disable_all_movement();
    rotating = true;
    enable_motor_for_movement();
    request->send(SPIFFS, "/toy_control.html", String(), false, set_state);
  });
  // stop rotation
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    disable_all_movement();
    enable_motor_for_movement();
    request->send(SPIFFS, "/toy_control.html", String(), false, set_state);
  });

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

  // Start server
  server.begin();
}