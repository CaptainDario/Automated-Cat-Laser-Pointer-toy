#include <ESP8266WiFi.h>
#include <FS.h>
#include <ESPAsyncWebServer.h>
#include <wifi_credentials.h>

AsyncWebServer server(80);


 
void setup_webserver(){


  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/control.html", String(), false, set_state);
  });
  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });

  //Navbar
  server.on("/about.html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/about.html", String(), false, set_state);
  });  
  server.on("/control.html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/control.html", String(), false, set_state);
  });  
  server.on("/setup.html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/setup.html");
  });
  server.on("/update.html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/update.html");
  });
  server.on("/wifi_setup.html", HTTP_GET, [](AsyncWebServerRequest *request){
    get_nearby_networks();
    request->send(SPIFFS, "/wifi_setup.html", String(), false, set_nearby_networks);
  });
  server.on("/help.html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/help.html");
  });  


  //Controls
  // start rotation
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(LASER_PIN, HIGH);
    disable_all_movement();
    rotating = true;
    enable_motor_for_movement();
    request->send(SPIFFS, "/control.html", String(), false, set_state);
  });
  // stop rotation
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(LASER_PIN, LOW);
    disable_all_movement();
    enable_motor_for_movement();
    request->send(SPIFFS, "/control.html", String(), false, set_state);
  });


  //Setup
  // move bottom
  server.on("/move_bottom_left", HTTP_GET, [](AsyncWebServerRequest *request){
    disable_all_movement();
    move_bottom_left = true;
    enable_motor_for_movement();
    request->send(SPIFFS, "/control.html", String(), false, set_state);
  });
  server.on("/move_bottom_right", HTTP_GET, [](AsyncWebServerRequest *request){
    disable_all_movement();
    move_bottom_right = true;
    enable_motor_for_movement();
    request->send(SPIFFS, "/control.html", String(), false, set_state);
  });
  // move top
  server.on("/move_top_left", HTTP_GET, [](AsyncWebServerRequest *request){
    disable_all_movement();
    move_top_left = true;
    enable_motor_for_movement();
    request->send(SPIFFS, "/control.html", String(), false, set_state);
  });
  server.on("/move_top_right", HTTP_GET, [](AsyncWebServerRequest *request){
    disable_all_movement();
    move_top_right = true;
    enable_motor_for_movement();
    request->send(SPIFFS, "/control.html", String(), false, set_state);
  });
  
  // set bottom min/max
  server.on("/set_bottom_minimum", HTTP_GET, [](AsyncWebServerRequest *request){
    disable_all_movement();
    set_bottom_minimum = true;
    enable_motor_for_movement();
    request->send(SPIFFS, "/control.html", String(), false, set_state);
  });
  server.on("/set_bottom_maximum", HTTP_GET, [](AsyncWebServerRequest *request){
    disable_all_movement();
    set_bottom_maximum = true;
    enable_motor_for_movement();
    request->send(SPIFFS, "/control.html", String(), false, set_state);
  });
  // set top min/max
  server.on("/set_top_minimum", HTTP_GET, [](AsyncWebServerRequest *request){
    disable_all_movement();
    set_top_minimum = true;
    enable_motor_for_movement();
    request->send(SPIFFS, "/control.html", String(), false, set_state);
  });
  server.on("/set_top_maximum", HTTP_GET, [](AsyncWebServerRequest *request){
    disable_all_movement();
    set_top_maximum = true;
    enable_motor_for_movement();
    request->send(SPIFFS, "/control.html", String(), false, set_state);
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
      set_new_wifi(__SSID, __pwd);
    }
    
    //route to the Control page
    request->send(SPIFFS, "/control.html", String(), false, set_state);
  });


  //footer/header
  server.on("/header.html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/header.html");
  });
  server.on("/footer.html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/footer.html");
  });


  //JS
  server.on("/include_html.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/include_html.js");
  });
  server.on("/live.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/live.js");
  });
  server.on("/BackGroundEffects.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/BackGroundEffects.js");
  });
  server.on("/quad.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/quad.js");
  });


  //IMGS
  //PNG
  server.on("/logo.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/logo.png");
  });
  server.on("/DaAppLab_Text.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/DaAppLab_Text.png");
  });
  server.on("/github.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/github.png");
  });
  server.on("/thingiverse.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/thingiverse.png");
  });
  //JPG
  server.on("/instructables.jpg", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/instructables.jpg");
  });
  server.on("/logo.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/logo.png");
  });
  //SVG
  server.on("/google-play.svg", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/google-play.svg");
  });
  server.on("/youtube.svg", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/youtube.svg");
  });


  // Start server
  server.begin();
}



