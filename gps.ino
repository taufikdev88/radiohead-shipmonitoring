// komunikasi memakai serial di pin 3 dan 4
TinyGPSPlus gps;
// Arduino -> GPS
// d4->tx, d3->rx
SoftwareSerial ss(4, 3);
void setup_gps(){
  ss.begin(9600);
}

void get_gps_data(){
  unsigned long start_time = millis();
  // try for 30 seconds and break if all is valid early
  while ( millis()-start_time < 300 ) {
    while (ss.available() > 0) {
      if (gps.encode(ss.read())) {
        if (gps.location.isValid()){
            gpsLat = gps.location.lat();
            gpsLong = gps.location.lng();
        }
        if (gps.date.isValid() && gps.time.isValid()) {
            gpsDate = gps.date.value();
            gpsTime = gps.date.value();
        }
      }
    }
    delay(10);
    if( gps.location.isValid() && gps.date.isValid() && gps.time.isValid() ){
      break;
    }
  }
}
