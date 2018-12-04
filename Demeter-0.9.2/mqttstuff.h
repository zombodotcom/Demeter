#include <PubSubClient.h>
#include <WiFi.h>

const char* ssid = "Zombo";
const char* password =  "thepromisedlan";
const char* mqttServer = "192.168.0.100";
const int mqttPort = 1883;
const char* mqttUser = "zombo";
const char* mqttPassword = "pi";

#define temperature_topic "temp"       //Topic temperature
#define ambient_topic "ambient"       //Topic temperature
#define humidity_topic "humid"         //Topic humidity
#define debug_topic "debug"                   //Topic for debugging
#define moisture_topic "moist"       //Topic temperature

WiFiClient espClient;
PubSubClient client(espClient);

void reconnect() {
 
   while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("Demeter2", mqttUser, mqttPassword )) {
 
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


void setupwifi(){
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
}
