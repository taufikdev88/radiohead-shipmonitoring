/*
 * T3chFlicks - Smart Buoy Project
 * Find full tutorial including video, schematic, and links 
 * to components at https://t3chflicks.com/shop/kit/smart-buoy/
*/

#include <Wire.h>

struct data_holder {
  int index;
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

// define nama packet
#define gpsDate1 packet1.date
#define gpsTime1 packet1.time
#define gpsLat packet1.val1
#define gpsLong packet1.val2
#define sCur packet1.val3
#define sVolt packet1.val4
#define waitTime packet1.val5

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
  setup_gps();
  setup_radio();
  setup_gy86();
  setup_power_control();
  setup_water_temperature();
  packet1.index = 0;
  packet2.index = 1;
}

void loop() {
  get_gps_data();
  get_wave_stats();
  get_water_temperature();
  set_new_alarm();
  send_data();
  delay(3000); // seemed to help radio communication reliability
  turn_off();
}
