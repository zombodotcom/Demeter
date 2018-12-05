// this verson includes SSR pump, APDS9860 light sensor, DHT22,
// MQTT and Wifi and also neostrip

#include <Wire.h>
#include "Leds.h"

//led strip stuff cant use fastled because of mismatches in wait with the APDS9960 =(

//Analog Input
#define ANALOG_PIN_0 36
#define SSRPUMP 19

//DHT
#include "DHT.h"      // Library for DHT sensors
#define DHTTYPE DHT22 // DHT 22  (AM2302)
#define DHTPIN 21     // DHT Pin

int moistureval = 0;
const int ledPin = 2;
#include "mqttstuff.h"
#include "apds_stuff.h"

DHT dht(DHTPIN, DHTTYPE);

///* definitions for deepsleep */
//#define uS_TO_S_FACTOR 1000000   /* Conversion factor for micro seconds to seconds */
//#define TIME_TO_SLEEP 900        /* Time ESP32 will go to sleep for 15 minutes (in seconds) */
//#define TIME_TO_SLEEP_ERROR 3600 /* Time to sleep in case of error (1 hour) */

bool debug = true; //Display log message if True

void setup()
{

  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(SSRPUMP, OUTPUT);
  WiFi.begin(ssid, password);
  setupwifi(); //in mqttstuff.h
  dht.begin();
  delay(100);
  Wire.begin(APDS9960_SDA, APDS9960_SCL);
  delay(100);
  startapds(); // in apds_stuff
  delay(100);
  strip.begin();
  //  shutoffleds();
  changeColor(strip.Color(0, 0, 0));
  strip.show();

  strip.setBrightness(10);

  // client.publish("esp/test", "test publish");
}

void loop()
{
   delay(10000);// longer time for delay so slower messages
  if (!client.connected())
  {
    reconnect();
  }
  //  striplighter();
  //  rainbow();

  lightsensorcheck();
  moistureval = analogRead(ANALOG_PIN_0);
  waterlight(moistureval);
 
  // Read temperature in Celcius
  float t = dht.readTemperature();
  // Read humidity
  float h = dht.readHumidity();

  if (debug)
  {
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
  striplighter(t, h, moistureval, ambient_light);

  char buffer[15];
  dtostrf(t, 0, 0, buffer);
  client.publish(temperature_topic, buffer, true);
  dtostrf(h, 0, 0, buffer);
  client.publish(humidity_topic, buffer, true);

  dtostrf(moistureval, 0, 0, buffer);
  client.publish(moisture_topic, buffer, true);

  sprintf(buffer, "%u", ambient_light);
  client.publish(ambient_topic, buffer, true);

  // client.publish("esp/test",h);
  client.loop();
}
