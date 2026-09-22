# Praktikum IoT

**Nama:** Nursyafika  
**NIM:** H1H024023  
**Program Studi:** Teknik Komputer  

Repository ini digunakan untuk menyimpan hasil praktikum mata kuliah Internet of Things (IoT).

## Modul 3 – Protokol Komunikasi IoT

Pada Modul 3 dilakukan praktikum mengenai protokol komunikasi yang digunakan dalam sistem IoT, yaitu **HTTP dan MQTT** dengan format pertukaran data **JSON**.

### Tujuan Praktikum

Praktikum ini bertujuan untuk:

1. Memahami konsep dasar protokol komunikasi pada sistem IoT.
2. Memahami karakteristik dan perbedaan HTTP dan MQTT.
3. Mengimplementasikan pengiriman data dari ESP32 ke server menggunakan HTTP dengan metode POST.
4. Mengimplementasikan pertukaran data dari ESP32 ke broker MQTT menggunakan pola publish-subscribe.
5. Menggunakan format JSON untuk pertukaran data.
6. Membandingkan penggunaan HTTP dan MQTT pada sistem IoT.

## HTTP

HTTP menggunakan pola komunikasi **request-response**. ESP32 berperan sebagai client yang mengirimkan request kepada server, kemudian server memberikan response.

Pada praktikum, HTTP digunakan untuk mengirim data sensor dalam format JSON menggunakan metode POST ke endpoint pengujian:

`httpbin.org/post`

Data yang dikirim berupa data suhu dan kelembaban.

## MQTT

MQTT merupakan protokol komunikasi yang menggunakan pola **publish-subscribe**. Pada komunikasi MQTT terdapat broker sebagai perantara antara publisher dan subscriber.

Pada praktikum digunakan broker:

`broker.hivemq.com`

Port yang digunakan:

`1883`

ESP32 bertindak sebagai publisher dengan mengirimkan data ke sebuah topic. Data tersebut kemudian dapat dipantau menggunakan MQTT Explorer.

## Format JSON

Data yang digunakan dalam praktikum dikemas menggunakan format JSON. Contoh data:

```json
{
  "suhu": 28.5,
  "kelembaban": 65.0
}

Format JSON digunakan agar data dapat disusun secara terstruktur dan mudah dibaca maupun diproses oleh perangkat atau aplikasi lain.

Tools dan Library

Praktikum menggunakan beberapa perangkat dan aplikasi berikut:

ESP32 DevKit

Laptop/PC

Arduino IDE

Jaringan WiFi

MQTT Explorer

Library ArduinoJson

Library PubSubClient


Hasil Praktikum

Pada percobaan HTTP, ESP32 digunakan untuk mengirimkan data suhu dan kelembaban dalam format JSON menggunakan metode POST.

Pada percobaan MQTT, ESP32 terhubung ke broker MQTT dan melakukan publish data melalui topic yang telah ditentukan. Data yang dikirim kemudian dapat dilihat melalui MQTT Explorer.

Struktur Repository

praktikum-iot/
│
├── Modul-3/
│   ├── Modul-3-HTTP.ino
│   └── Modul-3-MQTT.ino
│
└── README.md

Kesimpulan

Dari praktikum Modul 3 dapat dipahami bahwa HTTP dan MQTT dapat digunakan untuk komunikasi data pada sistem IoT. HTTP menggunakan pola request-response, sedangkan MQTT menggunakan pola publish-subscribe dengan broker sebagai perantara.

Data pada kedua percobaan menggunakan format JSON sehingga data suhu dan kelembaban dapat dikirim dalam bentuk yang terstruktur. MQTT juga memiliki overhead komunikasi yang lebih ringan sehingga sesuai untuk pengiriman data sensor secara berkala dan berkelanjutan.
