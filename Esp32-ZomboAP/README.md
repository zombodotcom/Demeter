##This is the Soft AP

Make sure to change the Demeter offline to the new SSID and pass
the pi should grab 192.168.0.100 first, if it boots up. or you set a static ip for wlan0
```
const char *ssid = "SSID";
const char *password = "PASS";

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
```
