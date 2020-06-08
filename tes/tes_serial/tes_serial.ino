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
  doc["Current"] = random(1,100) / 10.0;
  doc["Voltage"] = random(1,100) / 10.0;
  doc["WaveHeight"] = random(1,100) / 10.0;
  doc["WavePeriod"] = random(1,100) / 10.0;
  doc["WavePower"] = random(1,100) / 10.0;
  doc["AirTemp"] = random(1,100) / 10.0;
  doc["WaterTemp"] = random(1,100) / 10.0;
  
  serializeJson(doc, Serial);
  Serial.println();
  
  doc.garbageCollect();
  delay(200);
}
