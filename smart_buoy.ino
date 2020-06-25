/*
 * T3chFlicks - Smart Buoy Project
 * Find full tutorial including video, schematic, and links 
 * to components at https://t3chflicks.com/shop/kit/smart-buoy/
*/

#include <Wire.h>

// struktur data yang disiapkan untuk menampung nilai nilai sensor 
struct data_holder {
  unsigned long date;
  unsigned long time;
  float val1;
  float val2;
  float val3;
  float val4;
  float val5;
} packet1, packet2;

// packet1 = {
// i=0
// date
// time
// latitude
// longitude
// current
// voltage
// null
// }

// packet2 = {
// i=1
// date
// time
// wave height
// wave period
// wave power
// air temp
// water temp
// }

// #define adalah perintah agar compiler mengganti setiap kata awal dengan kata akhir
// contohnya #define katapertama katakedua
// saat sudah di compile maka katapertama akan berubah menjadi katakedua
// ini digunakan untuk mempermudah pengisian sensor
// contohnya biar tidak ribet saat pengen ngisi latitude, harus menghapal packet1.val1
// tinggal didefine bahwa gpsLat itu packet1.val1 maka otomatis di codingan manapun
// saat saya panggil gpsLat = 123123l; itu sama saja dengan packet1.val1 = 1231231;
// define nama packet
#define gpsDate1 packet1.date
#define gpsTime1 packet1.time
#define gpsLat packet1.val1
#define gpsLong packet1.val2
#define sCur packet1.val3
#define sVolt packet1.val4

#define gpsDate2 packet2.date
#define gpsTime2 packet2.time
#define waveHeight packet2.val1
#define wavePeriod packet2.val2
#define wavePower packet2.val3
#define airTemp packet2.val4
#define waterTemp packet2.val5

#define TCAADDR 0x70

void tcaselect(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}

void setup() {
  packet1.val5=0; 
  // karena saat packetnya banyak untuk menandai packet1 dan packet2, 
  // seperti saat kusuruh mencoba yang ada indexnya ternyata nrf24 gak mau ngirim
  // makanya di packet1.val5 digunakan untuk deteksi apakah dia packet1 atau tidak
  // kalau packet1.val5 isinya nol/0 berarti paket itu adalah paket1
  setup_gps();
  setup_radio();
  setup_gy86();
  setup_power_control();
  setup_water_temperature();
  setup_logger();
}

void loop() {
  get_gps_data();
  get_wave_stats();
  get_water_temperature();
  set_new_alarm();
  send_data();
  logger_save();
  delay(300); // seemed to help radio communication reliability
  turn_off();
}
