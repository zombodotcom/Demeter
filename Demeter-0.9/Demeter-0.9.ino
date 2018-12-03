// this verson includes SSR pump, APDS9860 light sensor, DHT22,
// MQTT and Wifi and also neostrip


#include <Wire.h>
#include "Leds.h"


#include <SparkFun_APDS9960.h>


//led strip stuff cant use fastled because of mismatches in wait with the APDS9960 =(

//Analog Input
#define ANALOG_PIN_0 36
#define SSRPUMP 19

//se
#include "DHT.h"          // Library for DHT sensors
#define DHTTYPE DHT22         // DHT 22  (AM2302)
#define DHTPIN 21               // DHT Pin 

#define APDS9960_SDA    23  //AKA GPIO0
#define APDS9960_SCL    22  //AKA GPIO5

// Global Variables for light sensor
SparkFun_APDS9960 apds = SparkFun_APDS9960();
uint16_t ambient_light = 0;
uint16_t red_light = 0;
uint16_t green_light = 0;
uint16_t blue_light = 0;


int moistureval = 0;
const int ledPin = 2;
#include "mqttstuff.h"


DHT dht(DHTPIN, DHTTYPE);   

 


 
/* definitions for deepsleep */
#define uS_TO_S_FACTOR 1000000        /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 900              /* Time ESP32 will go to sleep for 15 minutes (in seconds) */
#define TIME_TO_SLEEP_ERROR 3600       /* Time to sleep in case of error (1 hour) */
 
bool debug = true;             //Display log message if True

 
void setup() {
 
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(SSRPUMP, OUTPUT);
  WiFi.begin(ssid, password);
  setupwifi();
  dht.begin();
  delay(100);
  Wire.begin(APDS9960_SDA,APDS9960_SCL);
  delay(100);
  startapds();
  delay(100);
  strip.begin();
//  shutoffleds();
  changeColor(strip.Color(0, 0, 0));
  strip.show();

  strip.setBrightness(10);
 
 
  // client.publish("esp/test", "test publish");
 
}



void startapds(){
   if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }
  
   if ( apds.enableLightSensor(false) ) {
    Serial.println(F("Light sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during light sensor init!"));
  }
}

void lightsensorcheck(){

  if (  !apds.readAmbientLight(ambient_light) ||
        !apds.readRedLight(red_light) ||
        !apds.readGreenLight(green_light) ||
        !apds.readBlueLight(blue_light) ) {
    Serial.println("Error reading light values");
  } else {
//    Serial.print("Ambient: ");
//    Serial.print(ambient_light);
//    Serial.print(" Red: ");
//    Serial.print(red_light);
//    Serial.print(" Green: ");
//    Serial.print(green_light);
//    Serial.print(" Blue: ");
//    Serial.println(blue_light);
  }
}






 
void loop() {
   if (!client.connected()) {
    reconnect();
    
  }
//  striplighter();
//  rainbow();  

  lightsensorcheck();
  moistureval = analogRead(ANALOG_PIN_0);

    
   delay(5000);
  // Read temperature in Celcius
    float t = dht.readTemperature();
  // Read humidity
    float h = dht.readHumidity();
//    if(h==0||t==nan||
      if ( debug ) {
      Serial.print("\nTemperature : ");
      Serial.print(t);
      Serial.print(" | Humidity : ");
      Serial.print(h);
      Serial.print("| Moisture Data: ");
      Serial.print(moistureval);
      Serial.print("\nAmbient: ");
      Serial.print(ambient_light);
      Serial.print(" Red: ");
      Serial.print(red_light);
      Serial.print(" Green: ");
      Serial.print(green_light);
      Serial.print(" Blue: ");
      Serial.print(blue_light);
      

      
      }
      striplighter(t,h,moistureval,ambient_light);
      
      char buffer[15];
      dtostrf(t,0, 0, buffer);
      client.publish(temperature_topic,buffer,true);
      dtostrf(h,0, 0, buffer);
      client.publish(humidity_topic,buffer,true);

      dtostrf(moistureval,0, 0, buffer);
      client.publish(moisture_topic,buffer,true);
      
      sprintf(buffer, "%u", ambient_light);
      client.publish(ambient_topic,buffer,true);

      

      
   
  // client.publish("esp/test",h);
    client.loop();
  
}
