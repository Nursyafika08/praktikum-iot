# MODUL 3 - PROTOKOL KOMUNIKASI IoT

*HTTP dan MQTT dengan Format JSON*

*Nama Praktikan:* Nursyafika
*NIM:* H1H024023
*Program Studi:* Teknik Komputer
*Universitas:* Universitas Jenderal Soedirman
*Mata Kuliah:* Praktikum Sistem IoT (TK2450050)

## A. Tujuan Praktikum

1. Memahami konsep dasar protokol komunikasi pada sistem IoT.
2. Mengetahui karakteristik serta perbedaan protokol HTTP dan MQTT.
3. Mengimplementasikan pengiriman data dari ESP8266 ke server menggunakan HTTP POST.
4. Mengimplementasikan pengiriman data dari ESP8266 ke broker menggunakan MQTT publish-subscribe.
5. Menggunakan format JSON untuk pertukaran data antara ESP8266, server, broker, dan subscriber.
6. Mengetahui kelebihan dan kekurangan HTTP dan MQTT berdasarkan hasil percobaan.

## B. Alat dan Bahan

- ESP8266 NodeMCU
- Kabel USB
- Laptop/PC
- Arduino IDE
- Library ArduinoJson
- Library PubSubClient
- Jaringan WiFi yang terhubung internet
- MQTT client, seperti MQTT Explorer atau HiveMQ WebSocket Client
- Broker MQTT broker.hivemq.com
- Endpoint HTTP httpbin.org/post

## C. Percobaan 3A: Komunikasi Data Menggunakan HTTP

### 1. Tujuan

Memahami proses pengiriman data dari ESP8266 ke server menggunakan protokol HTTP dengan metode POST. Data yang dikirim berupa suhu dan kelembaban dalam format JSON.

### 2. Rangkaian

ESP8266 dihubungkan ke laptop menggunakan kabel USB. ESP8266 digunakan untuk menjalankan program dan mengirimkan data melalui jaringan WiFi.

### 3. Konfigurasi

| Parameter | Nilai |
|---|---|
| Protokol | HTTP |
| Metode | POST |
| Endpoint | https://httpbin.org/post |
| Format data | JSON |
| Baud rate | 115200 |
| Interval pengiriman | 10 detik |

### 4. File Program

code/modul3a_http.ino

### 5. Penjelasan Program

- ESP8266WiFi.h digunakan untuk menghubungkan ESP8266 ke jaringan WiFi.
- ESP8266HTTPClient.h digunakan untuk melakukan komunikasi HTTP.
- WiFiClientSecure.h digunakan karena server yang dituju menggunakan HTTPS.
- ArduinoJson.h digunakan untuk mengolah data dalam format JSON.
- Variabel SSID dan password digunakan untuk mengatur koneksi WiFi.
- serverUrl menentukan alamat endpoint HTTP yang dituju.
- Serial.begin(115200) mengatur komunikasi Serial Monitor.
- WiFi.begin() memulai proses koneksi ke jaringan WiFi.
- Perulangan while membuat program menunggu sampai koneksi berhasil.
- WiFiClientSecure client membuat objek koneksi HTTPS.
- client.setInsecure() digunakan untuk pengujian koneksi HTTPS tanpa verifikasi sertifikat server.
- HTTPClient http membuat objek untuk komunikasi HTTP.
- http.begin(client, serverUrl) memulai koneksi menuju endpoint.
- http.addHeader() mengatur Content-Type menjadi application/json.
- JsonDocument doc membuat objek untuk menampung data JSON.
- doc["suhu"] menyimpan data suhu sebesar 28,5.
- doc["kelembaban"] menyimpan data kelembaban sebesar 65,0.
- serializeJson() mengubah objek JSON menjadi String.
- http.POST() mengirimkan data ke server menggunakan metode POST.
- http.getString() mengambil isi response dari server.
- http.end() mengakhiri koneksi HTTP.
- delay(10000) memberikan jeda pengiriman selama 10 detik.

### 6. Contoh Data yang Dikirim

json
{
  "suhu": 28.5,
  "kelembaban": 65.0
}


### 7. Hasil Pengamatan dan Analisis

Berdasarkan hasil pengamatan, ESP8266 berhasil terhubung ke jaringan WiFi dan mengirimkan data suhu serta kelembaban ke server menggunakan metode HTTP POST.

Data dikirim dalam bentuk JSON dengan nilai suhu 28,5 dan kelembaban 65. Pada seluruh pengujian, server memberikan response code 200. Hal tersebut menunjukkan bahwa request yang dikirim dapat diterima dan diproses oleh server.

Pengiriman dilakukan secara berkala dengan interval 10 detik dan seluruh data pada pengujian berhasil dikirim.

## D. Modifikasi Percobaan 3A: Penambahan Data Waktu Menggunakan millis()

### 1. Tujuan

Menambahkan informasi waktu ke dalam data JSON menggunakan fungsi millis().

### 2. File Program

code/modul3a_http_modifikasi.ino

### 3. Penjelasan Modifikasi

Pada program modifikasi ditambahkan perintah:

doc["waktu"] = millis();

Perintah tersebut digunakan untuk memasukkan waktu yang dihitung sejak ESP8266 mulai berjalan ke dalam objek JSON.

Dengan penambahan tersebut, data yang dikirim tidak hanya berisi suhu dan kelembaban, tetapi juga informasi waktu pengiriman.

### 4. Contoh Data JSON

json
{
  "suhu": 28.5,
  "kelembaban": 65.0,
  "waktu": 10000
}


Nilai waktu pada contoh tersebut hanya ilustrasi. Nilai sebenarnya mengikuti waktu kerja ESP8266 saat program dijalankan.

## E. Percobaan 3B: Komunikasi MQTT

### 1. Tujuan

Memahami proses komunikasi menggunakan protokol MQTT dengan metode publish-subscribe. ESP8266 digunakan untuk mengirim data JSON ke broker melalui topic tertentu, kemudian data tersebut diterima oleh subscriber.

### 2. Rangkaian

ESP8266 dihubungkan ke laptop menggunakan kabel USB dan terhubung ke jaringan WiFi. Data dikirim menuju broker MQTT dan diamati menggunakan MQTT Explorer.

### 3. Konfigurasi

| Parameter | Nilai |
|---|---|
| Protokol | MQTT |
| Broker | broker.hivemq.com |
| Port | 1883 |
| Topic | pyka/esp8266/latihan |
| Format data | JSON |
| Baud rate | 115200 |
| Interval pengiriman | 5 detik |

### 4. File Program

code/modul3b_mqtt.ino

### 5. Penjelasan Program

- ESP8266WiFi.h digunakan untuk mengatur koneksi WiFi.
- PubSubClient.h digunakan untuk komunikasi MQTT.
- ArduinoJson.h digunakan untuk membuat data dalam format JSON.
- Variabel mqttServer menyimpan alamat broker MQTT.
- mqttPort menentukan port komunikasi MQTT, yaitu 1883.
- mqttTopic menentukan topic tempat data dikirim.
- WiFiClient espClient membuat objek koneksi jaringan.
- PubSubClient client(espClient) membuat objek client MQTT.
- Fungsi hubungkanWiFi() digunakan untuk menghubungkan ESP8266 ke jaringan WiFi.
- Fungsi hubungkanMQTT() digunakan untuk menghubungkan ESP8266 dengan broker MQTT.
- client.connected() memeriksa status koneksi MQTT.
- ESP.getChipId() digunakan untuk mendapatkan identitas chip ESP8266.
- client.connect() melakukan koneksi ke broker menggunakan Client ID.
- client.setServer() menentukan broker dan port MQTT.
- client.loop() menjaga proses komunikasi MQTT tetap berjalan.
- JsonDocument doc membuat objek JSON.
- Data suhu dan kelembaban dimasukkan ke dalam objek JSON.
- serializeJson() mengubah data JSON menjadi bentuk karakter.
- client.publish() mengirim data ke topic MQTT yang ditentukan.
- delay(5000) memberikan jeda pengiriman selama 5 detik.

### 6. Contoh Data JSON

json
{
  "suhu": 28.5,
  "kelembaban": 65.0
}


### 7. Hasil Pengamatan dan Analisis

Pada percobaan MQTT, ESP8266 berhasil terhubung ke broker dan melakukan publish data JSON melalui topic pyka/esp8266/latihan. Data yang dikirim kemudian dapat diterima oleh subscriber.

Berdasarkan sepuluh kali pengujian, broker tetap dalam kondisi terhubung dan seluruh data yang dikirim berhasil diterima oleh subscriber. Hal tersebut menunjukkan bahwa komunikasi publish-subscribe dapat berjalan dengan baik selama koneksi ke broker tersedia.

## F. Modifikasi Tambahan MQTT dengan Data Waktu

### 1. File Program

code/modul3b_mqtt_modifikasi.ino

### 2. Penjelasan

Program ini merupakan pengembangan tambahan dari program MQTT utama dengan menambahkan data waktu menggunakan millis() ke dalam objek JSON.

Baris yang ditambahkan:

doc["waktu"] = millis();

Dengan penambahan tersebut, subscriber dapat menerima informasi suhu, kelembaban, dan waktu pengiriman dalam satu pesan JSON.

Modifikasi ini merupakan tambahan program, bukan hasil pengamatan terpisah yang tercantum dalam BCP.

## G. Jawaban Pertanyaan Praktikum HTTP

### 1. Gambarkan diagram alur proses pengiriman data melalui HTTP POST pada program!

Mulai → Inisialisasi Serial dan WiFi → Menghubungkan WiFi → WiFi terhubung? → Membuat WiFiClientSecure → Inisialisasi HTTP → Menentukan Content-Type JSON → Membuat data JSON → Serialisasi JSON → Mengirim HTTP POST → Memeriksa response → Menampilkan response → Mengakhiri koneksi HTTP → Delay 10 detik → Mengulangi proses.

### 2. Apa fungsi http.addHeader("Content-Type", "application/json")?

Perintah tersebut digunakan untuk memberikan informasi kepada server bahwa data yang terdapat pada request menggunakan format JSON. Dengan demikian, server dapat mengenali jenis data yang diterima dan memprosesnya sesuai format tersebut.

### 3. Jelaskan arti kode response HTTP 200, 404, 400, dan 500!

- *200 (OK):* menunjukkan bahwa request berhasil diproses oleh server.
- *404 (Not Found):* menunjukkan bahwa alamat atau resource yang dituju tidak ditemukan.
- *400 (Bad Request):* menunjukkan bahwa request yang dikirim tidak dapat diproses karena terdapat kesalahan pada request.
- *500 (Internal Server Error):* menunjukkan adanya kesalahan pada sisi server ketika memproses request.

### 4. Bagaimana cara menambahkan data waktu menggunakan millis() ke JSON?

Data waktu dapat ditambahkan ke dalam objek JSON menggunakan perintah:

doc["waktu"] = millis();

Dengan perintah tersebut, waktu yang dihitung sejak ESP8266 mulai berjalan akan ikut dimasukkan ke dalam data JSON.

## H. Jawaban Pertanyaan Praktikum MQTT

### 1. Apa fungsi Topic pada MQTT dan mengapa topic harus dibuat unik?

Topic digunakan sebagai jalur untuk menentukan ke mana pesan MQTT dikirim dan dari mana subscriber menerima pesan.

Publisher mengirim data ke topic tertentu, sedangkan subscriber menerima data dengan melakukan subscribe pada topic tersebut. Penggunaan topic yang spesifik membantu membedakan pesan dari perangkat atau percobaan yang berbeda sehingga data tidak tercampur.

### 2. Apa fungsi client.loop()?

client.loop() digunakan untuk menjaga proses komunikasi antara ESP8266 dengan broker MQTT tetap berjalan. Fungsi ini perlu dijalankan secara rutin agar client dapat menangani komunikasi MQTT dengan baik.

### 3. Apa yang akan terjadi apabila koneksi ke broker MQTT terputus di tengah program berjalan?

Jika koneksi ke broker terputus, ESP8266 tidak dapat melakukan publish data sampai koneksi kembali tersedia.

Program memeriksa kondisi tersebut melalui client.connected(). Apabila client tidak lagi terhubung, fungsi hubungkanMQTT() dijalankan untuk mencoba melakukan koneksi kembali. Setelah koneksi berhasil, proses publish data dapat dilanjutkan.

## I. Pertanyaan Analisis

### 1. Uraikan hasil tugas pada praktikum yang telah dilakukan pada setiap percobaan!

Pada percobaan HTTP, ESP8266 berhasil terhubung ke WiFi dan mengirimkan data suhu serta kelembaban ke server menggunakan metode POST. Data dikirim dalam format JSON dan seluruh pengujian mendapatkan response code 200.

Pada percobaan MQTT, ESP8266 berhasil terhubung dengan broker dan melakukan publish data JSON melalui topic pyka/esp8266/latihan. Data yang dikirim berhasil diterima oleh subscriber pada seluruh pengujian.

### 2. Bandingkan besar overhead data dan pola komunikasi antara protokol HTTP dan MQTT berdasarkan hasil percobaan!

HTTP menggunakan pola request-response. ESP8266 mengirimkan request kepada server dan kemudian menerima response dari server.

MQTT menggunakan pola publish-subscribe dengan broker sebagai perantara. ESP8266 mengirimkan data melalui topic dan subscriber yang berlangganan topic tersebut dapat menerima data.

Dalam komunikasi data IoT yang dilakukan secara berulang, MQTT memiliki mekanisme komunikasi yang lebih ringan dibandingkan HTTP karena menggunakan koneksi yang dapat dipertahankan.

### 3. Untuk skenario pengiriman data sensor secara terus-menerus setiap beberapa detik dalam jangka waktu lama, protokol manakah yang lebih sesuai digunakan? Jelaskan alasannya!

MQTT sesuai digunakan untuk pengiriman data sensor secara berkala dalam jangka waktu lama. Hal ini karena MQTT menggunakan mekanisme publish-subscribe dan koneksi dengan broker dapat dipertahankan.

ESP8266 dapat melakukan publish data melalui topic yang telah ditentukan, sedangkan subscriber dapat menerima data tersebut tanpa ESP8266 harus mengirimkan request baru kepada setiap penerima.

### 4. Bagaimana peran format JSON dalam mendukung interoperabilitas data antara perangkat IoT dan berbagai platform/aplikasi yang berbeda?

JSON berfungsi sebagai format pertukaran data yang memiliki struktur sederhana dan mudah diproses.

Pada praktikum ini, data suhu dan kelembaban disimpan dalam bentuk pasangan key-value. Penggunaan JSON membuat data yang dikirim oleh ESP8266 dapat lebih mudah dibaca dan diproses oleh server, broker, maupun aplikasi yang mendukung format JSON.

Dengan begitu, perangkat dan platform yang berbeda dapat menggunakan struktur data yang sama.

## J. Perbandingan HTTP dan MQTT

| Aspek | HTTP | MQTT |
|---|---|---|
| Pola komunikasi | Request-response | Publish-subscribe |
| Tujuan komunikasi | Server | Broker |
| Metode pengiriman | POST | Publish |
| Penerima data | Server | Subscriber |
| Format data | JSON | JSON |
| Interval pengiriman | 10 detik | 5 detik |
| Endpoint/Broker | httpbin.org/post | broker.hivemq.com |
| Kegunaan | Mengirim request ke server | Pengiriman data berkala ke subscriber |

## K. Kendala yang Dihadapi

Selama pelaksanaan praktikum terdapat beberapa kendala, yaitu:

1. ESP8266 pada awalnya tidak dapat terhubung ke hotspot HP karena jumlah perangkat yang dapat terhubung telah mencapai batas. Setelah pengaturan jumlah perangkat pada hotspot diubah, ESP8266 dapat terhubung ke jaringan.
2. Pada percobaan HTTP terdapat error pada penggunaan fungsi HTTPClient::begin karena penggunaan API yang sudah tidak sesuai dengan versi library yang digunakan. Program kemudian menggunakan http.begin(client, serverUrl) dengan objek WiFiClientSecure.
3. Komunikasi HTTPS membutuhkan WiFiClientSecure agar ESP8266 dapat terhubung ke endpoint https://httpbin.org/post.
4. Pada awal percobaan MQTT, library PubSubClient belum terpasang sehingga program belum dapat dikompilasi. Setelah library tersebut dipasang, program MQTT dapat dijalankan.

## L. Kesimpulan

Berdasarkan praktikum Modul 3 mengenai Protokol Komunikasi IoT, dapat dipahami bahwa HTTP dan MQTT memiliki mekanisme komunikasi yang berbeda untuk melakukan pertukaran data pada perangkat IoT.

Pada percobaan HTTP, ESP8266 berhasil terhubung ke jaringan WiFi dan mengirimkan data suhu serta kelembaban dalam format JSON menggunakan metode HTTP POST. Seluruh pengujian memperoleh response code 200.

Pada percobaan MQTT, ESP8266 berhasil terhubung ke broker broker.hivemq.com dan melakukan publish data melalui topic pyka/esp8266/latihan. Data yang dikirim juga berhasil diterima oleh subscriber pada seluruh pengujian.

HTTP menggunakan pola request-response, sedangkan MQTT menggunakan pola publish-subscribe dengan broker sebagai perantara. Format JSON yang digunakan pada kedua percobaan membuat data suhu dan kelembaban tersusun secara terstruktur sehingga dapat lebih mudah dipertukarkan dan diproses oleh perangkat maupun aplikasi.