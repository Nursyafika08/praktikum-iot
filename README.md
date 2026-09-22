# Praktikum IoT

Nama: Nursyafika  
NIM: H1H024023  
Program Studi: Teknik Komputer

Repository ini berisi hasil praktikum mata kuliah Internet of Things (IoT).

## Modul 3 - Protokol Komunikasi IoT

Modul 3 membahas penggunaan protokol komunikasi HTTP dan MQTT pada sistem IoT dengan format pertukaran data JSON.

### Materi yang dipraktikkan

Pada modul ini dilakukan dua percobaan:

1. Komunikasi data menggunakan HTTP
2. Komunikasi data menggunakan MQTT

Data yang digunakan berupa data sensor suhu dan kelembaban dalam format JSON.

Contoh format data:

```json
{
  "suhu": 28.5,
  "kelembaban": 65.0
}

HTTP

Pada percobaan HTTP, ESP32 digunakan sebagai client untuk mengirimkan data ke server menggunakan metode POST.

Endpoint pengujian yang digunakan:

https://httpbin.org/post

Komunikasi HTTP menggunakan pola request-response, yaitu ESP32 mengirimkan request kemudian menerima response dari server.

MQTT

Pada percobaan MQTT, ESP32 digunakan sebagai publisher untuk mengirimkan data ke broker MQTT.

Broker yang digunakan:

broker.hivemq.com

Port:

1883

Data dikirim melalui topic tertentu dan hasil publish diverifikasi menggunakan MQTT Explorer.

MQTT menggunakan pola publish-subscribe dengan broker sebagai perantara antara publisher dan subscriber.

JSON

JSON digunakan sebagai format pertukaran data karena data dapat disusun dalam bentuk pasangan key-value sehingga lebih mudah dibaca dan diproses.

Pada praktikum ini digunakan library ArduinoJson untuk membuat dan mengubah data menjadi format JSON.

Tools dan Library

ESP32 DevKit

Arduino IDE

Kabel USB

Jaringan WiFi

MQTT Explorer

ArduinoJson

PubSubClient


Hasil Praktikum

Hasil program dan dokumentasi praktikum Modul 3 disimpan pada folder Modul-3.

Pada percobaan HTTP, data dikirim dari ESP32 ke server menggunakan HTTP POST.

Pada percobaan MQTT, data dikirim dari ESP32 ke broker menggunakan mekanisme publish-subscribe dan dapat dipantau melalui MQTT Explorer.

Perbandingan HTTP dan MQTT

HTTP menggunakan pola request-response dan setiap pengiriman dilakukan melalui request kepada server.

MQTT menggunakan pola publish-subscribe dengan broker sebagai perantara. MQTT memiliki overhead komunikasi yang lebih ringan dan cocok untuk pengiriman data IoT secara berkala.

Kesimpulan

Melalui Modul 3, dapat dipahami penggunaan HTTP dan MQTT sebagai protokol komunikasi pada sistem IoT. Kedua protokol dapat digunakan untuk mengirimkan data dalam format JSON. HTTP menggunakan pola request-response, sedangkan MQTT menggunakan pola publish-subscribe dengan broker sebagai perantara.

