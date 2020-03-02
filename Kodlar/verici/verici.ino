#include  <SPI.h>                //SPI bir senkron seri haberleşme protokolüdür 
#include "nRF24L01.h"
#include "RF24.h"
#include "RF24_config.h"
#include <dht11.h>                   
#define pin A0                  //Sensor değer Analog çıkıştan alınmaktadır
dht11 DHT;
RF24 radio(7,8);                //Kullanılacak kanal 
byte pipe[6] = "00001";         //Kanal adresi  (Karşı taraftakiyle aynı olmalıdır(!))

typedef struct{                 //Gönderilecek veri paketi , dizi olarak da gönderilebilir
    float temp = 0; 
    float hum  = 0;
    float dd   = 0;
  }Veri;
Veri veri;

void setup(void) {
  Serial.begin(115200);                  
  radio.begin();                   //kanal başlatılır
  radio.openWritingPipe(pipe);     //Kanale veri yazmaya ayarlanır   
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS); //Veri iletim hızı
  radio.setChannel(100);          
  radio.stopListening();
}
void loop() {
  DHT.read(pin);                    // Sıcaklık  ve nem değerleri okunur
  veri.temp = DHT.temperature;
  veri.hum  = DHT.humidity; 
  radio.write(&veri,sizeof(Veri));  //değerleri kanala yazılır 
  delay(1000);
}
