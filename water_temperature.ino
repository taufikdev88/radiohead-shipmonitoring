// komunikasi i2c
#include <OneWire.h>
#include <DallasTemperature.h>

// DS18B20 - Water Temperature
OneWire oneWire(6);
DallasTemperature sensors(&oneWire);


void setup_water_temperature(){
  sensors.begin();
}

void get_water_temperature(){
  sensors.requestTemperatures();
  waterTemp = sensors.getTempCByIndex(0);
}
