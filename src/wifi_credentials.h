#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <vector>


std::vector<std::vector<String>> networks = {};
std::vector<String> rssi_s = {};
std::vector<String> ssid_s = {};

void get_nearby_networks(){

    int n = WiFi.scanComplete();
    if(n == -2){
      WiFi.scanNetworks(true);
    }
    else if(n){

        //rssi_s.clear();
        //ssid_s.clear();
        networks.clear();

        for (int i = 0; i < n; ++i){
            //rssi_s.push_back(String(WiFi.RSSI(i)));
            //ssid_s.push_back(String(WiFi.SSID(i)));
            networks.push_back(std::vector<String>{String(WiFi.SSID(i)),
                                                    String(WiFi.RSSI(i))});
            //Serial.println("RSSI: " + networks[i][1] + "\tSSID: " + networks[i][0]);
        }

        WiFi.scanDelete();
        if(WiFi.scanComplete() == -2){
            WiFi.scanNetworks(true);
        }
    }
}

/*
// writes the found networks from the last scan into the "WiFI"-wepage
*/
String set_nearby_networks(const String& var){

    //Serial.println(":" + var + ":");

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

/*
// Tries to connect to the last saved network when no arguments are given
//
// If *both* parameters are set ESP will try to connect to this network.
*/
bool try_connect_to_wifi(String ssid="", String pwd=""){
  
  bool ret = false;
  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if(ssid != "" && pwd != ""){
    WiFi.begin(ssid, pwd);
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

  if(WiFi.status() == WL_CONNECTED){
    ret = true;
  
    Serial.println('\n');
  }

  return ret;
}