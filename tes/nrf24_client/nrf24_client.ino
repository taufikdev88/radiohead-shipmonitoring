// nrf24_client.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messageing client
// with the RH_NRF24 class. RH_NRF24 class does not provide for addressing or
// reliability, so you should only use RH_NRF24 if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example nrf24_server.
// Tested on Uno with Sparkfun NRF25L01 module
// Tested on Anarduino Mini (http://www.anarduino.com/mini/) with RFM73 module
// Tested on Arduino Mega with Sparkfun WRL-00691 NRF25L01 module

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
} packet1, packet2;

// define nama packet
#define gpsDate1 packet1.date
#define gpsTime1 packet1.time
#define gpsLat packet1.val1
#define gpsLong packet1.val2
#define sCur packet1.val3
#define sVolt packet1.val4
#define thisIsPacket1 packet1.val5=0;

#define gpsDate2 packet2.date
#define gpsTime2 packet2.time
#define waveHeight packet2.val1
#define wavePeriod packet2.val2
#define wavePower packet2.val3
#define airTemp packet2.val4
#define waterTemp packet2.val5

void setup() 
{
  Serial.begin(9600);
  while (!Serial) 
    ; // wait for serial port to connect. Needed for Leonardo only
  if (!nrf24.init())
    Serial.println("init failed");
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");    

  gpsDate1 = 1231231;
  gpsDate2 = 1231233;
  gpsTime1 = 3213213;
  gpsTime2 = 3322323;
  gpsLat = -123.888999;
  gpsLong = 78.332333;
  sCur = 4.1;
  sVolt = 12.2;
  waveHeight = 12.3;
  wavePeriod = 12.0;
  wavePower = 88.2;
  airTemp = 66.4;
  waterTemp = 100.1;
}

byte sz = sizeof(packet1);
byte buf[sizeof(packet1)] = {0};

void loop()
{
  Serial.println("Sending to nrf24_server");
  memcpy(buf, &packet1, sz);
  nrf24.send(buf, sz);
  nrf24.waitPacketSent();
  delay(400);
  memcpy(buf, &packet2, sz);
  nrf24.send(buf, sz);
  nrf24.waitPacketSent();
  delay(400);
}
