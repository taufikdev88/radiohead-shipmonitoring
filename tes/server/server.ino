#include <RHDatagram.h>
#include <RH_ASK.h>
#include <SPI.h>

//#define CLIENT_ADDRESS 1
#define SERVER_ADDRESS 1

// Singleton instance of the radio driver
RH_ASK driver;
// Class to manage message delivery and receipt, using the driver declared above
RHDatagram manager(driver, SERVER_ADDRESS);

struct dataStruct{
  float val1;  //Store temperature sensor value (degC)
  float val2;    //Store soil moisture level (%)
  float val3;      //Store hygrometer sensor reading
  float val4
  unsigned long date;
  unsigned long counter;
} SensorReadings;

void setup()
{
  Serial.begin(9600);
  if (!manager.init())
    Serial.println("init failed");

  SensorReadings.val1 = 0;
  SensorReadings.val2 = 0;
  SensorReadings.val3 = 0;
  SensorReadings.val4 = 0;
}

void loop()
{
	ReciveFromSensors();
}

void ReciveFromSensors()
{
  // Dont put this on the stack:
  uint8_t buf[sizeof(SensorReadings)];
  uint8_t from;
  uint8_t len = sizeof(buf);
 
  if (manager.available())
  {   
    // Wait for a message addressed to us from the client
    if (manager.recvfrom(buf, &len, &from))
    {
      int i;
      memcpy(&SensorReadings, buf, sizeof(SensorReadings));
      Serial.println("--------------------------------------------");
      Serial.print("Got message from unit: ");
      Serial.println(from, DEC);
      Serial.print("Transmission number: ");
      Serial.println(SensorReadings.counter);
      Serial.println("");
       
      Serial.print("val1: ");
      Serial.println(SensorReadings.val1);
       
      Serial.print("val2: ");
      Serial.println(SensorReadings.val2);
       
      Serial.print("val3");
      Serial.println(SensorReadings.val3);
      Serial.println("--------------------------------------------");
    } else {
		Serial.println("wrong packet data");
	}
  }
}
