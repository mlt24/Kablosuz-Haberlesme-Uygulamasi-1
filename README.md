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
<li>
<li><h2><a href="https://maker.robotistan.com/arduino-projeleri-egitimi/">Arduino Uno</a></h2><li>
<li><h2><a href="https://gelecegiyazanlar.turkcell.com.tr/konu/arduino/egitim/arduino-401/arduino-ile-kablosuz-haberlesme">nrf24l01</a></h2></li>
<li><h2><a href="https://www.robotistan.com/dht11-isi-ve-nem-sensoru-kart">DHT11</a></h2><li>
<li><h2><a href="http://www.esp32learning.com/code/esp32-and-rgb-led-example.php">RGB led</a></h2><li>
<li><h2><a href="https://docs.blynk.cc/">Blynk Mobil Uygulaması</a></h2><li>
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

<h1>Alıcı devresi örneği</h1>
<img src="/goruntu_video/alici.png" alt="Simply Easy Learning" title="Analog Saati>

<h1>Kodu kodu</h1>
<h1>Gerekli Kütüphane</h1>
Bu kütüphaneler indirilip Arduino->libraries dosyasında yerleştirlir.
<ul><li><h2><a href="https://github.com/nhatuan84/RF24">RF24 Kütüphanesi</a></h2><li>
<li><h2><a href="https://github.com/blynkkk/blynk-library">Blynk Kütüphanesi</a></h2><li>
</ul>
<h1> Gösteri </h1>
<video width="320" height="240" autoplay>
  <source src="/goruntu_video/gosteri.MOV" type="video/mp4">
  <source src="/goruntu_video/gosteri.MOV" type="video/MOV">
Your browser does not support the video tag.
</video>

