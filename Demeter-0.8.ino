// this verson includes SSR pump, APDS9860 light sensor, DHT22,
// MQTT and Wifi and also neopixels

#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

#include <SparkFun_APDS9960.h>
#include <Adafruit_NeoPixel.h>

//led strip stuff cant use fastled because of mismatches in wait with the APDS9960 =(

//Analog Input
#define ANALOG_PIN_0 36
#define SSRPUMP 19
int moistureval = 0;

#define stripPin            27
#define NUMPIXELS      16
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, stripPin, NEO_GRB + NEO_KHZ800);



#include "DHT.h"          // Library for DHT sensors
#define DHTTYPE DHT22         // DHT 22  (AM2302)

const char* ssid = "Zombo";
const char* password =  "password";
const char* mqttServer = "192.168.0.100";
const int mqttPort = 1883;
const char* mqttUser = "zombo";
const char* mqttPassword = "pi";
#define DHTPIN 21               // DHT Pin 
#define APDS9960_SDA    23  //AKA GPIO0
#define APDS9960_SCL    22  //AKA GPIO5

// Global Variables for light sensor
SparkFun_APDS9960 apds = SparkFun_APDS9960();
uint16_t ambient_light = 0;
uint16_t red_light = 0;
uint16_t green_light = 0;
uint16_t blue_light = 0;

//objects!
WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHTTYPE);    
const int ledPin = 2;
#define temperature_topic "temp"       //Topic temperature
#define ambient_topic "ambient"       //Topic temperature
#define humidity_topic "humid"         //Topic humidity
#define debug_topic "debug"                   //Topic for debugging
#define moisture_topic "moist"       //Topic temperature
 
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
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  
  Serial.println("Connected to the WiFi network");
      Serial.print("=> ESP32 new IP address is: ");
      Serial.print(WiFi.localIP());
      Serial.println("");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  while (!client.connected()) {
    reconnect();
  }
  dht.begin();
  delay(100);
  Wire.begin(APDS9960_SDA,APDS9960_SCL);
  delay(100);
  startapds();
  delay(100);
  pixels.begin();
 
  // client.publish("esp/test", "test publish");
 
}
void pixeltest(){
  for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,150,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(500); // Delay for a period of time (in milliseconds).

  }
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
void reconnect() {
 
   while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("Demeter", mqttUser, mqttPassword )) {
 
      Serial.println("connected");
      client.subscribe("esp32/led");
      client.subscribe("esp32/pump");
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
}


void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT
//    if (String(topic) == "esp32/led") {
//    Serial.print("Changing output to ");
//   
//      }
//    
  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
   if (String(topic) == "esp32/pump") {
       if(messageTemp == "on"){
        digitalWrite(SSRPUMP, HIGH);
       }
       else if(messageTemp == "off"){
      Serial.println("off");
        digitalWrite(SSRPUMP, LOW); 
    }
    
   }
  
  if (String(topic) == "esp32/led") {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(ledPin, HIGH);
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(ledPin, LOW);
    }
  }
}




 
 
void loop() {
   if (!client.connected()) {
    reconnect();
  }
  lightsensorcheck();
  moistureval = analogRead(ANALOG_PIN_0);

    
   delay(5000);
  // Read temperature in Celcius
    float t = dht.readTemperature();
  // Read humidity
    float h = dht.readHumidity();
    
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
      char buffer[10];
      dtostrf(t,0, 0, buffer);
      client.publish(temperature_topic,buffer,true);
//      client.publish(moisture_topic,buffer,true);
//      client.publish(ambient_topic,buffer,true);
      dtostrf(h,0, 0, buffer);
      client.publish(humidity_topic,buffer,true);
  // client.publish("esp/test",h);
    client.loop();
  
}
