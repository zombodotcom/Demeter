
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


**Pi MQT Setup**

First Update

    sudo apt-get update
    sudo apt-get upgrade

Then install MQTT


    sudo apt-get install mosquitto -y
    sudo apt-get install mosquitto-clients -y

then edit your mqtt broker config

    sudo nano /etc/mosquitto/mosquitto.conf

COMMENT OUT 

    include_dir /etc/mosquitto/conf.d


Add these new lines 

    allow_anonymous false
    password_file /etc/mosquitto/pwfile
    listener 1883
then set a username, you will then be asked to type in a password

    sudo mosquitto_passwd -c /etc/mosquitto/pwfile usernamehere

then reboot the pi

    sudo reboot

to see if its running 
restart it, stop it, or start it, 

    sudo service mosquitto stop
    sudo service mosquitto start
    sudo service mosquitto restart


I prefer to run it as a daemon 

    mosquitto -d


After that 

you can test subscriptions like this

    mosquitto_sub -d -h 192.168.0.100 -u username -P password -t temp -t humid -t moist -t esp32/pump -t esp32/led

 and publish like this 
 

    mosquitto_pub -d -u username -P password -t esp32/led -m "on"
    mosquitto_pub -d -u username -P password -t temp -m "25"

The MQTT Logger Built in python was made by
http://www.steves-internet-guide.com/simple-python-mqtt-data-logger/


Download the Topic Logger
http://www.steves-internet-guide.com/simple-python-mqtt-topic-logger/



be sure to install patho-mqtt
https://www.eclipse.org/paho/clients/python/docs/

    pip3 install paho-mqtt

To start logging all files run:

    python3 mqtt-topic-logger.py -b 192.168.0.100 -t "temp" -t "humid" -u username -P password -s

there are other options like where to log files, but the documentation is pretty straightforward. 
