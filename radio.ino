RH_NRF24 nrf24(8, 7); 

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
  delay(300);
  
  memcpy(buf, &packet2, sz); // gantian packet2 yang di kirim ke buffer
  nrf24.send(buf, sz); 
  nrf24.waitPacketSent();
  delay(300);
}
