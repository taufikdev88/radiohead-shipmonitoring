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

// struktur data disiapkan harus sama persis dengan struct yg ada di client
// agar data dapat diterima
struct data_holder {
  unsigned long date;
  unsigned long time;
  float val1;
  float val2;
  float val3;
  float val4;
  float val5;
} packet;

// sama seperti di smart_buoy yg client
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

/* 
 * untuk mempermudah pengiriman data ke laptop, dan mempercepat dalam pengolahan data 
 * maka menggunakan JSON adalah yg paling tepat, karena banyak library yg menyediakan
 * untuk mengolah data JSON baik dalam serialize(membungkus) maupun deserealize(membuka)
 */
StaticJsonDocument<1024> doc;

/*
 * flag untuk menandai packet1 sudah diterima sebelum packet2, jika packet1 tidak diterima
 * dan packet2 diterima terlebih dahulu, batalkan untuk meneruskan data ke laptop
 */
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
  /*
   * cek apakah nrf24 sudah menerima data
   */
  if (nrf24.available())
  {
    /*
     * siapkan buffer untuk menerima datanya, persis seperti struct yg kita buat
     */
    uint8_t buf[sizeof(packet)];
    uint8_t len = sizeof(buf);
    /*
     * cek apakah data yg diterima adalah data yang kita inginkan 
     * jika tidak sama, maka jangan diterima
     */
    if (nrf24.recv(buf, &len))
    {
      /*
       * ini kebalikan dari packet1 diubah ke buffer, ini adalah buffer dalam bentuk
       * byte data dibongkar ke dalam struct data, sehingga mudah diolah
       */
      memcpy(&packet, buf, sizeof(packet));

      /*
       * cek apakah packet yang diterima ini adalah packet1 dengan mengecek di val5 harus 0
       */
      if(isPacket1 == 0){
        /*
         * tandai flagnya bahwa packet1 sudah diterima dahulu
         * dan simpan nilainya ke dalam json tadi
         */
        isPacket1Received = true;
        doc["Date"] = gpsDate;
        doc["Time"] = gpsTime;
        doc["Latitude"] = gpsLat;
        doc["Longitude"] = gpsLong;
        doc["Current"] = sCur;
        doc["Voltage"] = sVolt;
      }
      /*
       * cek apakah ini packet ke 2 tandanya nilai val5 tidak 0, dan cek juga apakah packet1
       * sudah diterima duluan 
       */
      if(isPacket1 != 0 && isPacket1Received == true){
        /*
         * simpan nilainya ke json
         */
        doc["WaveHeight"] = waveHeight;
        doc["WavePeriod"] = wavePeriod;
        doc["WavePower"] = wavePower;
        doc["AirTemp"] = airTemp;
        doc["WaterTemp"] = waterTemp;

        /*
         * lalu kirimkan jsonnya dalam bentuk string yang sudah cantik
         * contohnya: {"key": "value", "key2": 12}
         * tinggal nanti di sisi aplikasi desktop jalankan perintah deserealize
         * 
         * serial.println() dibutuhkan agar payload/json yg dikirim diberi tambahan \r\n
         * \r\n dibutuhkan di sisi aplikasi desktop bahwa datanya sudah cukup itu
         * \r\n artinya enter/new line/baris baru
         */
        serializeJson(doc, Serial);
        Serial.println();

        /*
         * kembalikan flag packet1 diterima ke false lagi untuk memastikan datanya urut lagi
         * lalu lakukan pembersihan ke memory, karena json memakan memory arduinonya
         */
        isPacket1Received = false;
        doc.garbageCollect();
      }
      /*
       * nah disini, jika yg diterima packet2 dahulu, sedangkan packet1 belum diterima
       * buang saja langsung
       */
      if(isPacket1 != 0 && isPacket1Received == false){
        doc.garbageCollect();
      }
    }
  }
}
