#  NodeMCU + DS18B20 medical data collection and analysis
## Getting Started
 An IOT based system for medical data collection and analysis. This application runs on an WiFi connected ESP8266 NodeMCU which gets readings from a Dallas DS18B20 temperature sensor (later on a MELEXIS sensor). Data are uploaded on a constant basis into ThingSpeak (https://thingspeak.com) cloud data analysis service where are processed and dipslayed accordingly.
 
### Prerequisites

A NodeMCU 8266 development board

A Dallas 18B20 temperature sensor

Adruino IDE



### Installing



You need to load these libraries to Arduino IDE

OneWire https://www.arduinolibraries.info/libraries/one-wire

Dallas https://www.arduinolibraries.info/libraries/dallas-temperature


Go to ThingSpeak and SignUp. Copy your API Key and WiFi credentials into biometrics.ino





## Built With

* [Arduino IDE](https://www.arduino.cc/en/main/software) 

## Authors

* **Chris Papathanasiou** - *Initial work* 

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* This code is initialy written for Antivirus Hackathlon https://crowdhackathon.com/antivirus/ entry

