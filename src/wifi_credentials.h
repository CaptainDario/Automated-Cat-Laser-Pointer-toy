#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <vector>
#include <EEPROM.h>


//the name of the Access Point if no connection to a wifi network is possible
String ap_ssid = "DaPetToy";
//if the user has entered a new SSID and password
bool new_wifi = true;
String new_SSID = "";
String new_pwd = "";
//all nearby WiFi networks and their signal strength
std::vector<std::vector<String>> networks = {};


/**
  * Find all nearby wifi signals and save the SSID's and their signal strength in the 'networks' vector
  */
void get_nearby_networks();
/**
  * writes the found networks from the last scan into the "WiFI"-webpage
  */
String set_nearby_networks(const String& var);
/**
  * Set the values the user entered for connecting to a new network.
  */
void set_new_wifi(String __SSID, String __pwd);
/**
  * Tries to connect to connect to the newly given network.
  */
bool try_connect_to_wifi();


void get_nearby_networks(){

  int n = WiFi.scanComplete();
  if(n == -2){
    WiFi.scanNetworks(true);
  }
  else if(n){

    networks.clear();

    //add all nearby networks to the vector of networks
    for (int i = 0; i < n; ++i){
        networks.push_back(std::vector<String>{String(WiFi.SSID(i)),
                                                String(WiFi.RSSI(i))});
        //Serial.println("RSSI: " + networks[i][1] + "\tSSID: " + networks[i][0]);
    }

    //delete the scan
    WiFi.scanDelete();
    if(WiFi.scanComplete() == -2){
        WiFi.scanNetworks(true);
    }
  }
}

String set_nearby_networks(const String& var){

  String ret = String();

  if(var == "SSID"){
      for (size_t i = 0; i < networks.size(); i++)
      {
          ret += "<tr>";
          ret += "<td>" + String(networks[i][0]) + "</td>";
          ret += "<td>" + String(networks[i][1]) + "</td>";
          ret += "</tr>";
      }
  }
  //Serial.println(ret);
  return ret; 
}

void set_new_wifi(String __SSID, String __pwd){
  new_wifi = true;
  new_pwd = __pwd;
  new_SSID = __SSID; 
}

bool try_connect_to_wifi(){
  
  bool connected = false;
  
  if(new_wifi){

    WiFi.mode(WIFI_STA);

    //if a new SSID and password was set, try to connect to it
    if(new_SSID != "" && new_pwd != ""){
      WiFi.begin(new_SSID, new_pwd);
    }
    else{
      Serial.println("Trying to connect to last used network...");
      WiFi.begin();
    }
    
    //try to connect to wifi for 10 sec
    int i = 0;
    while (WiFi.status() != WL_CONNECTED && i < 10) {
      WiFi.hostname("DaAppLab-cat-toy");
      delay(1000);
      Serial.print(++i); Serial.print("... ");
    }

    //a connection was established
    if(WiFi.status() == WL_CONNECTED){
      connected = true;

      Serial.print("IP address:\t");
      Serial.println(WiFi.localIP());

      Serial.println('\n');
    }

    //reset the data entered by the user
    new_pwd = "";
    new_SSID = "";
    new_wifi = false;

    if(connected){
      Serial.println("Connection established!");  
    }
    else{
      Serial.println("Connection failed setting up hotspot.");
      WiFi.mode(WIFI_AP);
      WiFi.softAP(ap_ssid);
    }
  }

  return connected;
}
