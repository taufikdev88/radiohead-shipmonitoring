// nrf24_client

#include <SPI.h>
#include <RH_NRF24.h>
#include <inttypes.h>

// Singleton instance of the radio driver
RH_NRF24 nrf24;
// RH_NRF24 nrf24(8, 7); // use this to be electrically compatible with Mirf
// RH_NRF24 nrf24(8, 10);// For Leonardo, need explicit SS pin
// RH_NRF24 nrf24(8, 7); // For RFM73 on Anarduino Mini

void setup_radio(){
  Serial.begin(9600); // untuk debugging ke laptop
  if (!nrf24.init())
    Serial.println("init failed");
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");
}

void send_data(){
  // coba 1
//  uint8_t ad[] = "sdsfasdfa";
  String ad("ciba");
  nrf24.send(ad, sizeof(ad));
//  uint8_t timeData[] = "0," + String(gpsDate) + "," + String(gpsTime) + ",n";
////  uint8_t timeData[] = "0," + String(gpsDate) + "," + String(gpsTime) + ",n";
//  uint8_t gpsData[] = "1," + String(gpsLat) + "," + String(gpsLong) + ",n";
//  uint8_t waveData[] = "2," + String(waveHeight) + "," + String(wavePeriod) + "," + String(wavePower) + ",n";
//  uint8_t powerAndTempData[] = "3," + String(airTemp) + "," + String(waterTemp) + "," + String(sCur) + "," + String(sVolt) + ",n";
//  
//  nrf24.send(timeData, sizeof(timeData));
//  nrf24.waitPacketSent();
//  nrf24.send(gpsData, sizeof(gpsData));
//  nrf24.waitPacketSent();
//  nrf24.send(waveData, sizeof(waveData));
//  nrf24.waitPacketSent();
//  nrf24.send(powerAndTempData, sizeof(powerAndTempData));
//  nrf24.waitPacketSent();
}

/*  
 *  
 * Koding lama 
 *  
 */
 /*
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(8, 7); // CE, CSN

void setup_radio(){
  radio.begin();
  radio.openWritingPipe(0xF0F0F0F0E1LL);
  radio.openReadingPipe(1, 0xE8E8F0F0E1LL);
  radio.setChannel(0x76);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.setRetries(4,15);
  radio.stopListening();
  radio.enableDynamicPayloads();
  radio.powerUp();
  Serial.println("setup radio");
}


void send_data(){
  //  we can only send 32 bytes at a time so we have to split up 
  // the measurements
  radio.write(&measurement_1, sizeof(measurement_1));
  radio.write(&measurement_2, sizeof(measurement_2)) ;
}
*/