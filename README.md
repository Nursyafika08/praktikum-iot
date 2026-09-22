# Praktikum IoT

**Nama:** Nursyafika  
**NIM:** H1H024023  
**Program Studi:** Teknik Komputer  

# Modul 3 - HTTP dan MQTT

## Tujuan

Pada modul ini dilakukan percobaan komunikasi data menggunakan HTTP dan MQTT pada ESP32.

## Tools dan Library

- ESP32 DevKit
- Arduino IDE
- Kabel USB
- MQTT Explorer
- ArduinoJson
- PubSubClient

## Data Sensor

Data yang digunakan berupa data sensor suhu dan kelembaban dalam format JSON.

Contoh format data:

```json
{
  "suhu": 28.5,
  "kelembaban": 65.0
}
```

HTTP

Pada percobaan HTTP, ESP32 digunakan sebagai client untuk mengirimkan data ke server menggunakan metode HTTP POST.

Endpoint pengujian yang digunakan:

https://httpbin.org/post

Komunikasi HTTP menggunakan pola request-response, yaitu ESP32 mengirimkan request kemudian menerima response dari server.

MQTT

Pada percobaan MQTT, ESP32 digunakan sebagai publisher untuk mengirimkan data ke broker MQTT.

Broker yang digunakan:

Broker: broker.hivemq.com

Port: 1883


Data dikirim melalui topic tertentu dan hasil publish diverifikasi menggunakan MQTT Explorer.

MQTT menggunakan pola publish-subscribe dengan broker sebagai perantara antara publisher dan subscriber.

JSON

JSON digunakan sebagai format pertukaran data karena data dapat disusun dalam bentuk pasangan key-value.

Pada praktikum ini digunakan library ArduinoJson untuk membuat dan mengubah data menjadi format JSON.

Hasil Praktikum

Hasil program dan dokumentasi praktikum Modul 3 disimpan pada folder Modul-3.

Pada percobaan HTTP, data dikirim dari ESP32 ke server menggunakan HTTP POST.

Pada percobaan MQTT, data dikirim dari ESP32 ke broker menggunakan mekanisme publish-subscribe dan diverifikasi menggunakan MQTT Explorer.

Perbandingan HTTP dan MQTT

HTTP menggunakan pola request-response dan setiap pengiriman dilakukan melalui request kepada server.

MQTT menggunakan pola publish-subscribe dengan broker sebagai perantara antara publisher dan subscriber.

Kesimpulan

Pada praktikum ini dipelajari komunikasi data menggunakan HTTP dan MQTT pada ESP32. HTTP menggunakan pola request-response, sedangkan MQTT menggunakan pola publish-subscribe. Data sensor dikemas dalam format JSON untuk dikirim melalui kedua metode komunikasi tersebut.


**Jangan hapus tiga tanda ``` setelah JSON**, karena itu yang menutup kotak kode dan mencegah bagian HTTP ikut dianggap sebagai kode.
