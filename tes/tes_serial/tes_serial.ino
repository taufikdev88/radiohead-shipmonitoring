#include <ArduinoJson.h>

StaticJsonDocument<1024> doc;

void setup() 
{
  Serial.begin(9600); 
}

void loop()
{
  doc["Date"] = 1231232123;
  doc["Time"] = 123132123;
  doc["Latitude"] = -1213.231232;
  doc["Longitude"] = 7.454545;
  doc["Current"] = 5.1;
  doc["Voltage"] = 12.0;
  doc["WaveHeight"] = 12.12;
  doc["WavePeriod"] = 34.23;
  doc["WavePower"] = 43.23;
  doc["AirTemp"] = 23.43;
  doc["WaterTemp"] = 231.23;
  
  serializeJson(doc, Serial);
  Serial.println();
  
  doc.garbageCollect();
  delay(200);
}
