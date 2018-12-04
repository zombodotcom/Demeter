
#include <Adafruit_NeoPixel.h>
#define stripPin       27
#define NUMPIXELS      24
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, stripPin, NEO_GRB + NEO_KHZ800);

uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}



void changeColor(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
}


 void rainbow(){
    uint16_t i, j;

  for(j=0; j<256*3; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
 }
 }
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.

void pixeltest(){
  for(int i=0;i<NUMPIXELS;i++){

    // strip.Color takes RGB values, from 0,0,0 up to 255,255,255
    strip.setPixelColor(i, strip.Color(0,255,0)); // Moderately bright green color.

    strip.show(); // This sends the updated pixel color to the hardware.

    delay(100); // Delay for a period of time (in milliseconds).

  }
}

void shutoffleds(){
   for(int i=0;i<NUMPIXELS;i++){
    strip.setPixelColor(i, 0, 0, 0);
   }
   strip.show();
   delay(100);
}

void striplighter(float t, float h,int moistureval,uint16_t ambient_light){
  
  if (isnan(h)||isnan(t)||(moistureval==0)||ambient_light==0){

      for(int i=0;i<NUMPIXELS;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    strip.setPixelColor(i, strip.Color(155,0,0)); // Moderately bright red color.
    delay(10);
    strip.show(); // This sends the updated pixel color to the hardware.
    delay(100); // Delay for a period of time (in milliseconds).
      }
      changeColor(strip.Color(0, 0, 0));
       delay(100);
      strip.show();
      delay(100);
   } 
  else{
  rainbow();
  }
  

}

void waterlight(int moistureval){
  if(moistureval>2000){

    
   for(int i=0;i<NUMPIXELS;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    strip.setPixelColor(i, strip.Color(0,0,200)); // Moderately bright red color.
    delay(10);
    strip.show(); // This sends the updated pixel color to the hardware.
    delay(100); // Delay for a period of time (in milliseconds).
      }
      changeColor(strip.Color(0, 0, 0));
       delay(100);
      strip.show();
      delay(100);
   }
  

}
