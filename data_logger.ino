#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;

void setup_logger(){
  Serial.begin(9600);
  
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    while (1);
  }
  Serial.println("card initialized.");
}

void logger_save(){
  String payload;
  payload += ((String) "date: " + packet1.date + "\t");
  payload += ((String) "time: " + packet1.time + "\t");
  payload += ((String) "lat: " + packet1.val1 + "\t");
  payload += ((String) "lng: " + packet1.val2 + "\t");
  payload += ((String) "cur: " + packet1.val3 + "\t");
  payload += ((String) "vol: " + packet1.val4 + "\t");
  payload += ((String) "w_hgt: " + packet2.val1 + "\t");
  payload += ((String) "w_prd: " + packet2.val2 + "\t");
  payload += ((String) "w_pwr: " + packet2.val3 + "\t");
  payload += ((String) "air_t: " + packet2.val4 + "\t");
  payload += ((String) "wtr_t: " + packet2.val5 + "\t");

  File dataFile = SD.open("log.txt", FILE_WRITE);
  if(dataFile){
    dataFile.println(payload);
    dataFile.close();
  } else {
    Serial.println("Error opening file");
  }
}
