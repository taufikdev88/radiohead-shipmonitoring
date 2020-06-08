// nrf24_server.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messageing server
// with the RH_NRF24 class. RH_NRF24 class does not provide for addressing or
// reliability, so you should only use RH_NRF24  if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example nrf24_client
// Tested on Uno with Sparkfun NRF25L01 module
// Tested on Anarduino Mini (http://www.anarduino.com/mini/) with RFM73 module
// Tested on Arduino Mega with Sparkfun WRL-00691 NRF25L01 module

#include <ArduinoJson.h>
#include <SPI.h>
#include <RH_NRF24.h>

// Singleton instance of the radio driver
RH_NRF24 nrf24;
// RH_NRF24 nrf24(8, 7); // use this to be electrically compatible with Mirf
// RH_NRF24 nrf24(8, 10);// For Leonardo, need explicit SS pin
// RH_NRF24 nrf24(8, 7); // For RFM73 on Anarduino Mini

struct data_holder {
  unsigned long date;
  unsigned long time;
  float val1;
  float val2;
  float val3;
  float val4;
  float val5;
} packet;

// define nama packet
#define gpsDate packet.date
#define gpsTime packet.time
#define gpsLat packet.val1
#define gpsLong packet.val2
#define sCur packet.val3
#define sVolt packet.val4
#define isPacket1 packet.val5

#define waveHeight packet.val1
#define wavePeriod packet.val2
#define wavePower packet.val3
#define airTemp packet.val4
#define waterTemp packet.val5

StaticJsonDocument<1024> doc;

bool isPacket1Received = false;

void setup() 
{
  Serial.begin(9600);
  if (!nrf24.init())
    Serial.println("init failed");
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");    
}

void loop()
{
  if (nrf24.available())
  {
    uint8_t buf[sizeof(packet)];
    uint8_t len = sizeof(buf);
    if (nrf24.recv(buf, &len))
    {
      memcpy(&packet, buf, sizeof(packet));
      
      if(isPacket1 == 0){
        isPacket1Received = true;
        doc["Date"] = gpsDate;
        doc["Time"] = gpsTime;
        doc["Latitude"] = gpsLat;
        doc["Longitude"] = gpsLong;
        doc["Current"] = sCur;
        doc["Voltage"] = sVolt;
      }
      if(isPacket1 != 0 && isPacket1Received == true){
        doc["WaveHeight"] = waveHeight;
        doc["WavePeriod"] = wavePeriod;
        doc["WavePower"] = wavePower;
        doc["AirTemp"] = airTemp;
        doc["WaterTemp"] = waterTemp;
        
        serializeJson(doc, Serial);
        Serial.println();
        
        isPacket1Received = false;
        doc.garbageCollect();
      }
      if(isPacket1 != 0 && isPacket1Received == false){
        doc.garbageCollect();
      }
    }
  }
}
