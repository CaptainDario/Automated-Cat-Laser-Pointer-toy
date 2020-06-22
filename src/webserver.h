#include <ESP8266WiFi.h>
#include <FS.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);


 
void setup_webserver(){


  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/toy_control.html", String(), false, set_rotation);
  });
  
  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });

  // start rotation
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    disable_all_movement();
    rotating = true;
    request->send(SPIFFS, "/toy_control.html", String(), false, set_rotation);
  });
  // stop rotation
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    disable_all_movement();
    request->send(SPIFFS, "/toy_control.html", String(), false, set_rotation);
  });

  // move bottom
  server.on("/move_bottom_left", HTTP_GET, [](AsyncWebServerRequest *request){
    disable_all_movement();
    move_bottom_left = true;
    request->send(SPIFFS, "/toy_control.html", String(), false, set_rotation);
  });
  server.on("/move_bottom_right", HTTP_GET, [](AsyncWebServerRequest *request){
    disable_all_movement();
    move_bottom_right = true;
    request->send(SPIFFS, "/toy_control.html", String(), false, set_rotation);
  });
  // move top
  server.on("/move_top_left", HTTP_GET, [](AsyncWebServerRequest *request){
    disable_all_movement();
    move_top_left = true;
    request->send(SPIFFS, "/toy_control.html", String(), false, set_rotation);
  });
  server.on("/move_top_right", HTTP_GET, [](AsyncWebServerRequest *request){
    disable_all_movement();
    move_top_right = true;
    request->send(SPIFFS, "/toy_control.html", String(), false, set_rotation);
  });
  
  // set bottom min/max
  server.on("/set_bottom_minimum", HTTP_GET, [](AsyncWebServerRequest *request){
    disable_all_movement();
    set_bottom_minimum = true;
    request->send(SPIFFS, "/toy_control.html", String(), false, set_rotation);
  });
  server.on("/set_bottom_maximum", HTTP_GET, [](AsyncWebServerRequest *request){
    disable_all_movement();
    set_bottom_maximum = true;
    request->send(SPIFFS, "/toy_control.html", String(), false, set_rotation);
  });
  // set top min/max
  server.on("/set_top_minimum", HTTP_GET, [](AsyncWebServerRequest *request){
    disable_all_movement();
    set_top_minimum = true;
    request->send(SPIFFS, "/toy_control.html", String(), false, set_rotation);
  });
  server.on("/set_top_maximum", HTTP_GET, [](AsyncWebServerRequest *request){
    disable_all_movement();
    set_top_maximum = true;
    request->send(SPIFFS, "/toy_control.html", String(), false, set_rotation);
  });

  // Start server
  server.begin();
}