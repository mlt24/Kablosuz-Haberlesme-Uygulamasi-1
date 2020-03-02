#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "RF24_config.h"


char auth[] = "YourAuthToken";     //mailden alınır
char ssid[] = "YourNetworkName";   
char pass[] = "YourPassword";


BlynkTimer timer;                  //timer nesnesi
RF24 radio(12, 14, 26, 25, 27);    //kanal
byte pi[6] = "00001";              //kanal adresi


typedef struct{                    // Gönderilecek veri yapısı(paket) dizi de göndderilebilir
   float temp = 0;
   float hum  = 0;  
   float dd   = 0;
  }Veri;
    
Veri veri;

int p21=0;
int p22=0;
int p23=0; 

void sendSensor()                  //kanal dinlenir ve alınan verileri Blynk serverine gönderilir
{   
  if (radio.available()){   
     radio.read(&veri, sizeof(Veri));
     Blynk.virtualWrite(V5, veri.temp);
     Blynk.virtualWrite(V6, veri.hum);
  }
}

void setup(){

  
  ledcAttachPin(21, 10);           //esp32 ~pwm pinleri kullanabilmek için GPIO pinleri
  ledcAttachPin(22, 11);            // kanallara bağlanır 0-15 pinler
  ledcAttachPin(23, 12);
  
  ledcSetup(10, 4000, 8);            
  ledcSetup(11, 4000, 8);
  ledcSetup(12, 4000, 8);


  
  Serial.begin(115200);
  radio.begin();                            
  radio.openReadingPipe(0,pi);               //Dinlenecek kanal açılır
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);          //Veri alma hızı 
  radio.setChannel(100);                   
  radio.startListening();
  timer.setInterval(1000L, sendSensor);
  Blynk.begin(auth,ssid,pass);             //Blynk serveri başlatılır

  }

BLYNK_WRITE(V21){                          // Uygulamadaki değer rgb pinlere yazdırılır
  p21 = param.asInt();
  ledcWrite(10,p21); 
  Serial.println(p21);
  }

BLYNK_WRITE(V22){
  p22 = param.asInt();
  ledcWrite(11,p22);
  Serial.println(p22);
  }

BLYNK_WRITE(V23){
  p23 = param.asInt();
  ledcWrite(12,p23);
  Serial.println(p23);
  }


void loop(void){
  Blynk.run();                             //Blynk ve timer çalıştırılır
  timer.run();
}
