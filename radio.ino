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

// siapkan buffer untuk menyimpan packet kita agar bisa dikirim melalui nrf24
// karena nrf24 radiohead tidak menerima parameter berupa struct , maka perlu 
// diubah ke byte dulu byte itu sama saja dengan uint8_t , lebar datanya sama 8bit
byte sz = sizeof(packet1);
byte buf[sizeof(packet1)] = {0};

void send_data(){
  memcpy(buf, &packet1, sz); // simpan nilai struct tadi ke buffer
  nrf24.send(buf, sz); // kirimkan data nya ke nrf24
  nrf24.waitPacketSent(); // beri perintah untuk menunggu datanya terkirim

  memcpy(buf, &packet2, sz); // gantian packet2 yang di kirim ke buffer
  nrf24.send(buf, sz); 
  nrf24.waitPacketSent();
}

/*  
 *  
 * Koding lama library nrf adafruiut
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
