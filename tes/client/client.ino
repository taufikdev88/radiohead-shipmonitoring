#include <RHDatagram.h>
#include <RH_ASK.h>
#include <SPI.h>

//RH communication
#define CLIENT_ADDRESS 2
#define SERVER_ADDRESS 1
// Singleton instance of the radio driver
RH_ASK driver;
// Class to manage message delivery and receipt, using the driver declared above
RHDatagram manager(driver, CLIENT_ADDRESS);

struct dataStruct{
  float val1;
  float val2;
  float val3;
  float val4;
  unsigned long date;
  unsigned long counter;   
} SensorReadings;

 // RF communication, Dont put this on the stack:
  byte buf[sizeof(SensorReadings)] = {0};

void setup()
{
  Serial.begin(9600);
 
  //RF communication
  if (!manager.init())
    Serial.println("init failed");

  SensorReadings.val1 = -50.123123;
  SensorReadings.val2 = 123.321321;
  SensorReadings.val3 = 8.231;
  SensorReadings.val4 = 843.2;
  SensorReadings.date = 12332213;
}

void loop()
{
  Serial.println("------------------------------------");
  SendValues(); //Send sensor values
  delay(2000);
  Serial.println("------------------------------------");
}

//RF communication
void SendValues()
{ 
  //Load message into data-array
  //byte data[sizeof(sensorValues)];

  byte zize=sizeof(SensorReadings);
  memcpy (buf, &SensorReadings, zize);

 
  Serial.println("Sending to ask_datagram_server");
  int i = 0;
  int repeat = 10; //Times to repeat same message
   
  // Send a message to manager_server
  while (i<repeat)
  {
    if (manager.sendto(buf, zize, SERVER_ADDRESS))
    {
      Serial.println("Message sent");   
    }
    else
    {
      Serial.println("sendto failed");
    }
    delay(100);
    i = i+1;
  }
  SensorReadings.counter = SensorReadings.counter + 1;
}