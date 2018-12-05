#include <WiFi.h>

const char *ssid = "Esp32-ZomboAP";
const char *password = "derp1234";

void setup() {
  Serial.begin(115200);
  Serial.println("Configuring access point...");

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  Serial.println("Wait 100 ms for AP_START...");
  delay(100);
  
  Serial.println("Set softAPConfig");
  IPAddress Ip(192, 168, 0, 99); // we are preprogrammed to 192.168.0.100 right now on the Pi 
  //so, might was well force it to grab 100 as the next ip :D
  IPAddress NMask(255, 255, 255, 0);
  WiFi.softAPConfig(Ip, Ip, NMask);
  
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
}

void loop() {
}
