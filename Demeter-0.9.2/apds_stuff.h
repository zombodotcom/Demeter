
#include <SparkFun_APDS9960.h>
#define APDS9960_SDA    23  //AKA GPIO0
#define APDS9960_SCL    22  //AKA GPIO5

// Global Variables for light sensor
SparkFun_APDS9960 apds = SparkFun_APDS9960();
uint16_t ambient_light = 0;
uint16_t red_light = 0;
uint16_t green_light = 0;
uint16_t blue_light = 0;

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
