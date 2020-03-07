<h1>Kablosuz Haberleşme Uygulaması</h1>
<p>
Bu uygulamada, ESP32-WROOM-32 modülü , Arduino , nrf24l01 modülü <br>
ve Blynk IOS/Android arayüz geliştiricisi kullanarak gerçek zamanlı<br>
veri izleme ve kontrol sistemi gerçekleştirilmiştir.
</p>
<h1> Kullanılan Teknolojiler</h1>

<ul>
<li>
<h2><a href="https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf">ESP32-WROOM-32 Wifi ve Bluetooth Geliştirici Modülü</a></h2>
</li>
<li><h2><a href="https://maker.robotistan.com/arduino-projeleri-egitimi/">Arduino Uno</a></h2></li>
<li><h2><a href="https://gelecegiyazanlar.turkcell.com.tr/konu/arduino/egitim/arduino-401/arduino-ile-kablosuz-haberlesme">nrf24l01</a></h2></li>
<li><h2><a href="https://www.robotistan.com/dht11-isi-ve-nem-sensoru-kart">DHT11</a></h2></li>
<li><h2><a href="http://www.esp32learning.com/code/esp32-and-rgb-led-example.php">RGB led</a></h2></li>
<li><h2><a href="https://docs.blynk.cc/">Blynk IOS/Android arayüz geliştiricisi</a></h2></li>
</ul>
<h1>Amaç</h1>
<p>Bu uygulamanın amacı, Arduino ,nrf24l01(verici) modülü ve dht11 sıcaklık <br>
ve nem sensöründen oluşan verici devresinden eşzamanlı  olarak  ortamdaki <br>
sıcaklık ve nem değerlerini Esp32 , nrf24l01(alıcı) dan oluşan alıcı devreye<br>
göndermek ve esp32'nin wi-fi modülü vasıtasıyla internete bağlanarak Blynk servere<br>
verileri kaydederek Blynk platformuyla tasarlanan Android tabanlı uzaktan izleme <br>
ve kontrol  arayüzünde verileri görüntemek ve aynı arayüzden verici devresi üzerinde<br>
bulunan rgb led'in renkleri ayarlamaktır.</p>
<h1>Verici devresi örneği</h1>
<img src="/goruntu_video/verici.png" alt="Verici" title="Verici">
<h1>Verici kodu</h1>

```cpp

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

```

<h1>Alıcı devresi örneği</h1>
<img src="/goruntu_video/alici.png" alt="Alıcı" title="Alıcı">

<h1>Alıcı kodu</h1>

```cpp

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


typedef struct{                    // alınacak veri yapısı(paket)
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
  radio.openReadingPipe(0,pi);            //Dinlenecek kanal açılır
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);        //Veri alma hızı 
  radio.setChannel(100);                   
  radio.startListening();
  timer.setInterval(1000L, sendSensor);
  Blynk.begin(auth,ssid,pass);             //Blynk serveri başlatılır

  }

BLYNK_WRITE(V21){       // Uygulamadaki değer rgb pinlere yazdırılır
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
  Blynk.run();                     //Blynk ve timer çalıştırılır
  timer.run();
}

```
<h1>Mobil uygulama Arayüzü</h1>
<img src="/goruntu_video/blynk.jpeg" alt="Mobil uygulama Arayüzü" title="Mobil uygulama Arayüzü">
<h1>Gerekli Kütüphane</h1>
Bu kütüphaneler indirilip Arduino->libraries dosyasında yerleştirlir.
<ul><li><h2> <a href="https://github.com/nhatuan84/RF24">RF24 Kütüphanesi</a></h2></li>
<li><h2><a href="https://github.com/blynkkk/blynk-library">Blynk Kütüphanesi</a></h2></li>
<li><h2><a href="https://github.com/adidax/dht11">DHT11 Kütüphanesi</a></h2></li>
</ul>

