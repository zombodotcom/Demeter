# Demeter


<img src="https://i.imgur.com/onVL47M.png" alt="drawing" align="right" width="200"/>


**Demeter** 
is an ESP32, and Raspberry Pi based project designed to tackle IoT based home garden automation. 
This project was made to use an ESP32, Raspberry Pi, Sensors, and message protocol systems, to create an example on the functionality of hardware and software. 


**Demeter** is the goddess of the harvest and presides over grains and the fertility of the earth. She is the Goddess of agriculture, harvest, fertility and sacred law. Although she was most often referred to as the goddess of the harvest, she was also goddess of sacred law and the cycle of life and death.


"Though Demeter is often described simply as the goddess of the harvest, she presided also over the [sacred law](https://en.wikipedia.org/wiki/Religious_law "Religious law"), and the cycle of life and death. She and her daughter [Persephone](https://en.wikipedia.org/wiki/Persephone "Persephone") were the central figures of the [Eleusinian Mysteries](https://en.wikipedia.org/wiki/Eleusinian_Mysteries "Eleusinian Mysteries") that predated the [Olympian pantheon](https://en.wikipedia.org/wiki/Olympian_pantheon "Olympian pantheon")."

source: https://en.wikipedia.org/wiki/Demeter




Demeter is used to measure:
* Temperature
	* using a DHT22 sensor
		* [DHT22 Manua](http://osoyoo.com/2018/03/15/arduino-lesson-dht22-humidity-and-temperature-sensor/)
* Humidity
	* using a DHT22 Sensor
		* [DHT22 Manual](http://osoyoo.com/2018/03/15/arduino-lesson-dht22-humidity-and-temperature-sensor/)
* Soil Moisture
	* [Soil Sensor Manual](https://www.dfrobot.com/product-1385.html)
* Light Sensor and Gesture Sensor
	* [APDS-9960 Broadcom ](https://www.broadcom.com/products/optical-sensors/integrated-ambient-light-and-proximity-sensors/apds-9960)

The Raspberry Pi runs:
* MQTT Broker
	* mosquitto
* MQTT Subsriber and publisher
* A website 
* Stores Sensor Data
* 

The ESP-32 Node32S:
*  [DHT22 Manual](http://osoyoo.com/2018/03/15/arduino-lesson-dht22-humidity-and-temperature-sensor/)
* Soil Moisture Sensor
	* [Soil Sensor Manual](https://www.dfrobot.com/product-1385.html)
* Light Sensor and Gesture Sensor
	* [APDS-9960 Broadcom ](https://www.broadcom.com/products/optical-sensors/integrated-ambient-light-and-proximity-sensors/apds-9960)
* Solid State Relay
	* To power a submersible pump


The ESP32 is programmed with Arduino.
It uses multiple libraries:
* DHT22 Library
	* based on an esp8266 library which was converted to esp32
* Wifi
	* WIFI for esp32
* PUBSUBCLIENT
	* MQTT publishing and subcribing for microcontrollers
* APDS-9960 SPARKFUN Library
	* Which has been edited to allow redefinition of SDA SCL pins
