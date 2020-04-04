// COVIDUS - ESP8266+DS18B20+ArduinoIDE+Thingspeak IoT Medical
// -----------------------------------------------------------
// https://github.com/avcrowdhackathon/OMNIS
// 
// https://www.arduinolibraries.info/libraries/dallas-temperature
//
// LIVE Data for the Antivirus Hackathlon https://thingspeak.com/channels/1029493


#include <OneWire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS D1                 // ESP8266 Data port
#define TEMPERATURE_PRECISION 11        // Set sensor precision. 11 bit is 0.125 degrees C


//ThingSpeak API parameters
const char* host = "api.thingspeak.com"; // ThingSpeak api domain  
String ApiKey = "YOURAPIKEY";            // ThingSpeak API Key
String path = "/update?key=" + ApiKey + "&field1=";  


OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);

int numberOfDevices;                  // Number of OneWire devices found
DeviceAddress tempDeviceAddress;      // We'll use this variable to store a found device address
const char* ssid = "yourssid";        // WIFI SSID
const char* pass = "wifipassword";    // WIFI PASSWORD


char temperatureString[6];

void setup(void){
  Serial.begin(115200);
  Serial.println("");
  
  WiFi.begin(ssid, pass);
 
 // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Connected to wifi ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  DS18B20.begin();
  Serial.println("Sensor Init");  
 
 // Grab a count of devices on the OneWire bus
  numberOfDevices = DS18B20.getDeviceCount();
  
 // locate devices on the OneWire bus
  Serial.print("Locating devices...");
  
  Serial.print("Found ");
  Serial.print(numberOfDevices, DEC);
  Serial.println(" devices.");

 // report parasite power requirements
  Serial.print("Parasite power is: "); 
  if (DS18B20.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");
  
 // Loop through each device, print out address
  for(int i=0;i<numberOfDevices; i++)
  {
    // Search the wire for address
    if(DS18B20.getAddress(tempDeviceAddress, i))
  {
    Serial.print("Found device ");
    Serial.print(i, DEC);
    Serial.print(" with address: ");
    printAddress(tempDeviceAddress);
    Serial.println();
    
    Serial.print("Setting resolution to ");
    Serial.println(TEMPERATURE_PRECISION, DEC);
    
 // set resolution of TEMPERATURE_PRECISION bit to 11 ( 0.125 degrees C )
    DS18B20.setResolution(tempDeviceAddress, TEMPERATURE_PRECISION);
    
    Serial.print("Resolution actually set to: ");
    Serial.print(DS18B20.getResolution(tempDeviceAddress), DEC); 
    Serial.println();
  }else{
    Serial.print("Found ghost device at ");
    Serial.print(i, DEC);
    Serial.print(" but could not detect address. Check power and cabling");
  }
  }
}

float getTemperature() {
  float temp;
  do {
    DS18B20.requestTemperatures(); 
    temp = DS18B20.getTempCByIndex(0);           // Read temperature value from sensor
    delay(100);
  } while (temp == 100.0 || temp == (-127.0));   // Filter temp values of sensor
  Serial.println("Temp received ...");
  return temp;
}

// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}


void loop() {

  float temperature = getTemperature();

  dtostrf(temperature, 2, 2, temperatureString);
  // send temperature to the serial console
  Serial.println(temperatureString);

  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
// Send data to ThingSpeak
  client.print(String("GET ") + path + temperatureString + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: keep-alive\r\n\r\n");
  delay(30000);

}
