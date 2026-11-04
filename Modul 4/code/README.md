# MODUL 4 - KOMUNIKASI DAN PERTUKARAN DATA

*Pertukaran Data Dua Arah (Publish dan Subscribe)*

*Nama Praktikan:* Nursyafika
*NIM:* H1H024023
*Program Studi:* Teknik Komputer
*Universitas:* Universitas Jenderal Soedirman
*Mata Kuliah:* Praktikum Sistem IoT (TK2450050)

## A. Tujuan Praktikum

1. Memahami konsep pertukaran data dua arah (bidirectional) pada sistem IoT.
2. Memahami mekanisme subscribe dan proses deserialisasi data JSON pada ESP8266.
3. Mengimplementasikan penerimaan perintah kendali melalui MQTT untuk menggerakkan aktuator secara real-time.
4. Mengimplementasikan sistem IoT yang dapat mempublikasikan data sensor dan menerima perintah kendali secara bersamaan (full duplex).
5. Mampu menganalisis mekanisme pertukaran data IoT secara menyeluruh pada sistem yang saling terhubung.

## B. Alat dan Bahan

- ESP8266 DevKit (NodeMCU)
- Sensor DHT11
- LED sebagai simulasi aktuator
- Resistor 220 Ohm
- Buzzer
- Breadboard dan kabel jumper
- Kabel USB
- Laptop/PC
- Arduino IDE
- Library ArduinoJson
- Library PubSubClient
- Library DHT Sensor Library
- Jaringan WiFi yang terhubung internet
- MQTT Explorer
- Broker MQTT broker.hivemq.com port 1883

## C. Konfigurasi Sistem

| Parameter | Konfigurasi |
|---|---|
| Board | ESP8266 NodeMCU |
| SSID WiFi | MamaLime |
| Broker MQTT | broker.hivemq.com |
| Port MQTT | 1883 |
| Topic perintah LED | KelompokDediPyka/perintah |
| Topic data suhu | KelompokDediPyka/data |
| Topic buzzer | KelompokDediPyka/buzzer |
| Pin LED | GPIO4 (D2) |
| Pin DHT11 | GPIO5 (D1) |
| Pin buzzer | D5 |
| Baud rate | 115200 |

## D. Percobaan 4A: Subscribe dan Deserialisasi Data JSON untuk Kendali Aktuator

### 1. Tujuan

Memahami dan mengimplementasikan mekanisme subscribe pada MQTT beserta proses deserialisasi data JSON. ESP8266 menerima perintah dalam format JSON dari broker, kemudian perintah tersebut digunakan untuk menyalakan dan mematikan LED sebagai aktuator.

### 2. Rangkaian

ESP8266 dihubungkan ke laptop menggunakan kabel USB dan terhubung ke jaringan WiFi. LED dipasang pada pin GPIO4 (D2) ESP8266 dan GND sebagai indikator aktuator. Perintah dikirim dari MQTT Explorer melalui broker broker.hivemq.com.

### 3. File Program

code/modul4a_subscribe_json.ino

### 4. Penjelasan Program

- ESP8266WiFi.h digunakan untuk menghubungkan ESP8266 ke jaringan WiFi.
- PubSubClient.h digunakan untuk komunikasi MQTT.
- ArduinoJson.h digunakan untuk mengolah data JSON.
- topicPerintah menentukan topic MQTT yang digunakan untuk menerima perintah.
- ledPin = 4 menentukan pin LED pada GPIO4 atau D2.
- Fungsi callback() dipanggil otomatis setiap kali terdapat pesan baru pada topic yang di-subscribe.
- Payload berupa array byte disusun menjadi String menggunakan perulangan.
- deserializeJson() digunakan untuk mengubah pesan JSON menjadi objek yang dapat dibaca program.
- Jika parsing gagal, program menampilkan pesan error dan keluar dari fungsi tanpa mengubah kondisi LED.
- Jika nilai perintah adalah ON, LED dinyalakan menggunakan digitalWrite(ledPin, HIGH).
- Jika nilai perintah adalah OFF, LED dimatikan menggunakan digitalWrite(ledPin, LOW).
- Fungsi hubungkanWiFi() digunakan untuk menghubungkan ESP8266 ke jaringan WiFi.
- Fungsi hubungkanMQTT() menghubungkan ESP8266 ke broker dan melakukan subscribe setelah koneksi berhasil.
- client.setCallback(callback) mendaftarkan fungsi callback.
- client.loop() harus dipanggil secara terus-menerus agar pesan masuk dapat diterima.

### 5. Contoh Pesan JSON

Perintah ON:

{"perintah":"ON"}

Perintah OFF:

{"perintah":"OFF"}

### 6. Hasil Pengamatan Percobaan 4A

| No. | Perintah JSON | Hasil Parsing | Status LED | Keterangan |
|---|---|---|---|---|
| 1 | ON | ON | Menyala | Aktuator ON |
| 2 | OFF | OFF | Mati | Aktuator OFF |
| 3 | ON | ON | Menyala | Aktuator ON |
| 4 | OFF | OFF | Mati | Aktuator OFF |
| 5 | ON | ON | Menyala | Aktuator ON |

### 7. Analisis

Berdasarkan hasil pengamatan, ESP8266 berhasil terhubung ke jaringan WiFi dan broker MQTT, kemudian melakukan subscribe ke topic KelompokDediPyka/perintah.

Setiap pesan JSON yang dipublikasikan dari MQTT Explorer muncul pada Serial Monitor sebagai pesan mentah, kemudian dideserialisasi dan nilai perintahnya diproses. Perintah ON membuat LED menyala dan perintah OFF membuat LED mati.

Pada awal pengujian, pesan sempat dikirim dengan nilai tanpa tanda kutip, yaitu {"perintah": ON}. Pesan tersebut diterima oleh ESP8266, tetapi proses deserialisasi gagal dengan error InvalidInput sehingga LED tidak berubah. Setelah pesan diperbaiki menjadi {"perintah":"ON"}, perintah dapat diproses dengan benar.

Hal ini menunjukkan bahwa penulisan format JSON harus valid agar dapat dibaca dan diproses oleh ESP8266.

## E. Modifikasi Percobaan 4A: Pengaturan Intensitas LED Menggunakan PWM

### 1. Tujuan

Memodifikasi program agar data JSON yang diterima juga memuat nilai intensitas untuk mengatur kecerahan LED menggunakan PWM.

### 2. File Program

code/modul4a_pwm.ino

### 3. Penjelasan Modifikasi

Pada modifikasi ini, program membaca nilai intensitas dari pesan JSON menggunakan:

int intensitas = doc["intensitas"] | 255;

Nilai intensitas dibatasi menggunakan constrain(intensitas, 0, 255) agar tetap berada dalam rentang yang sesuai.

Pada ESP8266, pengaturan kecerahan LED menggunakan analogWrite(), bukan ledcWrite() seperti pada ESP32. Oleh karena itu, rentang PWM disesuaikan menggunakan analogWriteRange(255).

Jika perintah ON diterima, LED menyala sesuai intensitas yang dikirim. Jika perintah OFF diterima, nilai PWM diatur menjadi 0 sehingga LED mati.

### 4. Contoh Pesan JSON

{"perintah":"ON","intensitas":200}

{"perintah":"ON","intensitas":100}

{"perintah":"OFF","intensitas":0}

## F. Percobaan 4B: Pertukaran Data Dua Arah (Publish dan Subscribe Secara Bersamaan)

### 1. Tujuan

Mengimplementasikan sistem IoT yang dapat mempublikasikan data sensor dan menerima perintah kendali secara bersamaan (full duplex). Percobaan ini merupakan penggabungan antara proses publish pada Modul 3 dan subscribe pada percobaan 4A.

### 2. Rangkaian

ESP8266 dihubungkan ke laptop menggunakan kabel USB dan terhubung ke jaringan WiFi. Sensor DHT11 dihubungkan ke pin GPIO5 (D1), sedangkan LED dipasang pada pin GPIO4 (D2).

### 3. File Program

code/modul4b_publish_subscribe.ino

### 4. Penjelasan Program

- ESP8266WiFi.h digunakan untuk mengatur koneksi WiFi.
- PubSubClient.h digunakan untuk komunikasi MQTT.
- ArduinoJson.h digunakan untuk mengolah data JSON.
- DHT.h digunakan untuk membaca sensor DHT11.
- topicData digunakan untuk mengirim data suhu.
- topicPerintah digunakan untuk menerima perintah kendali LED.
- DHTPIN 5 menentukan pin sensor pada GPIO5 atau D1.
- ledPin = 4 menentukan pin LED pada GPIO4 atau D2.
- waktuTerakhirPublish menyimpan waktu pengiriman terakhir.
- intervalPublish = 5000 menentukan interval pengiriman selama 5 detik.
- Fungsi callback() menerima pesan perintah dari topic perintah dan melakukan deserialisasi JSON.
- hubungkanWiFi() menghubungkan ESP8266 ke jaringan WiFi.
- hubungkanMQTT() menghubungkan ESP8266 ke broker dan melakukan subscribe ke topic perintah.
- client.loop() memproses pesan masuk secara terus-menerus.
- millis() digunakan untuk mengatur waktu pengiriman tanpa menggunakan delay panjang.
- dht.readTemperature() membaca suhu dari DHT11.
- serializeJson() mengubah data suhu menjadi JSON.
- client.publish() mengirimkan data suhu ke broker melalui topic data.

### 5. Contoh Data JSON

Data suhu yang dipublikasikan:

{"suhu":30.2}

Perintah LED ON:

{"perintah":"ON"}

Perintah LED OFF:

{"perintah":"OFF"}

### 6. Hasil Pengamatan Percobaan 4B

| No. | Waktu (s) | Data Suhu | Perintah | Status LED | Data Diterima Subscriber |
|---|---:|---|---|---|---|
| 1 | 0 | 30,2°C | - | Mati | Berhasil |
| 2 | 5 | 30,2°C | ON | Menyala | Berhasil |
| 3 | 10 | 30,2°C | - | Menyala | Berhasil |
| 4 | 15 | 30,8°C | OFF | Mati | Berhasil |
| 5 | 20 | 30,8°C | - | Mati | Berhasil |
| 6 | 25 | 30,8°C | ON | Menyala | Berhasil |
| 7 | 30 | 31,3°C | - | Menyala | Berhasil |
| 8 | 35 | 31,3°C | OFF | Mati | Berhasil |
| 9 | 40 | 31,2°C | - | Mati | Berhasil |
| 10 | 45 | 31,2°C | ON | Menyala | Berhasil |

### 7. Analisis

Pada percobaan 4B, ESP8266 berhasil mempublikasikan data suhu dari sensor DHT11 ke topic KelompokDediPyka/data dengan interval 5 detik. Hal ini terlihat dari riwayat pesan pada MQTT Explorer yang memiliki selisih waktu sekitar 5 detik.

Nilai suhu yang terbaca berada pada rentang sekitar 30 sampai 31°C. Pada saat yang sama, ESP8266 tetap dapat menerima perintah dari topic KelompokDediPyka/perintah.

Ketika perintah ON dan OFF dipublikasikan dari MQTT Explorer, LED langsung menyala dan mati tanpa menunggu siklus publish berikutnya. Hal tersebut menunjukkan bahwa proses publish dan subscribe dapat berjalan bersamaan.

## G. Jawaban Pertanyaan Praktikum 4A

### 1. Gambarkan diagram alur proses penerimaan dan pemrosesan pesan pada fungsi callback!

Mulai → Callback dipanggil → Terima topic dan payload → Ubah payload menjadi String → Tampilkan pesan pada Serial Monitor → Jalankan deserializeJson() → Periksa keberhasilan parsing.

Jika parsing gagal, tampilkan pesan gagal parsing JSON lalu keluar dari fungsi.

Jika berhasil, ambil nilai perintah dari JSON. Jika perintah ON, LED diberi HIGH dan status ON ditampilkan. Jika perintah OFF, LED diberi LOW dan status OFF ditampilkan. Proses selesai.

### 2. Apa yang akan terjadi apabila pesan yang dipublikasikan bukan merupakan format JSON yang valid?

Pesan tetap diterima oleh ESP8266 dan fungsi callback tetap dijalankan, tetapi deserializeJson() akan mengembalikan error, misalnya InvalidInput.

Program kemudian menampilkan pesan Gagal parsing JSON beserta jenis error pada Serial Monitor dan keluar dari fungsi dengan return, sehingga perintah tidak diproses dan kondisi LED tidak berubah.

### 3. Mengapa fungsi client.subscribe() dipanggil di dalam fungsi hubungkanMQTT(), bukan di dalam setup()?

Subscribe hanya dapat dilakukan setelah ESP8266 berhasil terhubung ke broker. Pada setup(), koneksi MQTT belum dibuat karena baru ditentukan server-nya dengan client.setServer().

Selain itu, langganan topic akan hilang ketika koneksi ke broker terputus. Dengan memanggil subscribe di dalam hubungkanMQTT(), ESP8266 otomatis berlangganan kembali setiap kali berhasil tersambung ulang sehingga perintah tetap dapat diterima.

### 4. Modifikasi program agar data JSON yang diterima memuat nilai intensitas untuk mengatur kecerahan LED menggunakan PWM!

Modifikasi dilakukan dengan menambahkan nilai intensitas pada objek JSON. Nilai tersebut dibaca menggunakan doc["intensitas"], kemudian dibatasi dalam rentang 0–255 menggunakan constrain().

Pada ESP8266 digunakan analogWriteRange(255) untuk mengatur rentang PWM. Ketika perintah ON diterima, LED menyala sesuai nilai intensitas. Ketika perintah OFF diterima, LED dimatikan dengan nilai PWM 0.

## H. Jawaban Pertanyaan Praktikum 4B

### 1. Mengapa penggunaan delay() yang lama sebaiknya dihindari pada program yang menggabungkan proses publish dan subscribe secara bersamaan?

delay() bersifat blocking, yaitu menghentikan seluruh proses program selama waktu tunda. Selama itu client.loop() tidak dapat dipanggil sehingga pesan perintah yang masuk tidak segera diproses dan LED terlambat merespons.

Jika tundanya terlalu lama, koneksi ke broker juga dapat terputus karena ESP8266 tidak mengirim sinyal keep-alive tepat waktu.

### 2. Jelaskan cara kerja mekanisme non-blocking menggunakan fungsi millis()!

millis() mengembalikan waktu dalam milidetik sejak ESP8266 mulai berjalan. Program menyimpan waktu publish terakhir pada waktuTerakhirPublish.

Pada setiap putaran loop(), selisih millis() dan waktuTerakhirPublish diperiksa. Jika selisihnya belum melebihi intervalPublish sebesar 5000 ms, program tidak melakukan publish dan langsung kembali ke awal loop sehingga client.loop() tetap dipanggil.

Jika sudah melebihi interval, waktu publish terakhir diperbarui dan data suhu dikirim. Dengan cara ini pengiriman data berkala tidak menghentikan proses penerimaan pesan.

### 3. Apa yang akan terjadi apabila fungsi client.loop() jarang dipanggil?

Pesan perintah yang masuk baru diproses ketika client.loop() dipanggil kembali sehingga LED merespons dengan lambat.

Selain itu, client.loop() juga bertugas menjaga koneksi dengan mengirim keep-alive ke broker. Jika jarak pemanggilannya terlalu lama melebihi batas keep-alive, broker dapat menganggap client terputus dan ESP8266 harus menyambung ulang.

### 4. Modifikasi program agar menambahkan topic perintah baru untuk mengendalikan aktuator kedua berupa buzzer!

Modifikasi dilakukan dengan menambahkan topic KelompokDediPyka/buzzer dan pin buzzer D5.

Program melakukan subscribe terhadap topic LED dan buzzer setelah berhasil terhubung ke broker. Pada callback digunakan strcmp() untuk membandingkan topic pesan yang masuk.

Jika pesan berasal dari topic LED, perintah ON atau OFF diterapkan pada LED. Jika pesan berasal dari topic buzzer, perintah yang sama diterapkan pada buzzer.

## I. Pertanyaan Analisis

### 1. Uraikan hasil tugas pada praktikum yang telah dilakukan pada setiap percobaan!

Pada percobaan 4A, ESP8266 berhasil terhubung ke broker, melakukan subscribe ke topic KelompokDediPyka/perintah, menerima pesan JSON, dan melakukan deserialisasi. Perintah ON menyalakan LED dan perintah OFF mematikan LED, sedangkan pesan dengan format JSON yang tidak valid menghasilkan error InvalidInput dan tidak mengubah LED.

Pada percobaan 4B, ESP8266 berhasil mempublikasikan data suhu dari DHT11 ke topic KelompokDediPyka/data setiap 5 detik dan pada saat yang sama tetap dapat menerima perintah ON dan OFF dari topic KelompokDediPyka/perintah. LED merespons langsung dan sistem tetap terhubung ke broker selama pengujian.

### 2. Bandingkan mekanisme komunikasi satu arah dengan komunikasi dua arah!

Pada komunikasi satu arah seperti Modul 3, ESP8266 hanya mengirim data ke broker melalui client.publish() dan tidak menerima perintah dari broker.

Pada komunikasi dua arah seperti Modul 4, ESP8266 selain mempublikasikan data juga melakukan subscribe ke topic perintah. Oleh karena itu, diperlukan fungsi callback, deserialisasi JSON, dan pengaturan waktu non-blocking menggunakan millis().

Dengan komunikasi dua arah, perangkat tidak hanya melaporkan data tetapi juga dapat dikendalikan dari jarak jauh.

### 3. Mengapa pendekatan non-blocking menggunakan millis() lebih sesuai dibandingkan delay() pada sistem IoT real-time?

Pada komunikasi dua arah, ESP8266 harus siap menerima perintah kapan saja. Pendekatan blocking menghentikan seluruh program selama delay(), sehingga perintah yang masuk tertunda dan koneksi ke broker berisiko terputus.

Pendekatan non-blocking menggunakan millis() hanya memeriksa selisih waktu pada setiap putaran loop(). Dengan demikian, client.loop() tetap berjalan dan perintah dapat langsung diproses sementara data sensor tetap dikirim secara berkala.

### 4. Berikan contoh penerapan komunikasi dua arah pada sistem IoT nyata!

Contohnya adalah sistem smart home. Sensor suhu dan kelembapan mengirim data ke broker melalui publish, sedangkan pengguna dapat menyalakan atau mematikan kipas, lampu, atau pendingin ruangan melalui aplikasi yang mengirim perintah ke topic tertentu.

Manfaatnya dibandingkan sistem satu arah adalah pengguna tidak hanya memantau kondisi ruangan, tetapi juga dapat langsung bertindak dari jarak jauh dan perangkat dapat merespons perintah secara real-time tanpa perlu berada di lokasi.

## J. Perbandingan Komunikasi Satu Arah dan Dua Arah

| Aspek | Satu Arah (Modul 3) | Dua Arah (Modul 4) |
|---|---|---|
| Arah komunikasi | ESP8266 ke broker | ESP8266 ke broker dan broker ke ESP8266 |
| Fungsi MQTT | client.publish() | client.publish() dan client.subscribe() |
| Fungsi callback | Tidak digunakan | Digunakan |
| Proses JSON | Serialisasi | Serialisasi dan deserialisasi |
| Pengaturan jeda | delay(5000) | millis() (non-blocking) |
| Topic | pyka/esp8266/latihan | KelompokDediPyka/data dan KelompokDediPyka/perintah |
| Aktuator | Tidak ada | LED dikendalikan dari MQTT Explorer |
| Hasil pengujian | Berhasil | Berhasil |

## K. Kendala yang Dihadapi

1. Kode pada modul menggunakan library WiFi.h dan pin GPIO 26 yang sesuai untuk ESP32, sedangkan board yang digunakan adalah ESP8266. Kode kemudian disesuaikan dengan menggunakan library ESP8266WiFi.h dan pin D-series pada ESP8266.
2. Pada awal percobaan 4A, pesan perintah dikirim dengan format {"perintah": ON} tanpa tanda kutip pada nilai sehingga deserialisasi gagal dengan error InvalidInput dan LED tidak berubah. Setelah format diperbaiki menjadi {"perintah":"ON"}, perintah dapat diproses.
3. Pada ESP8266, pengaturan kecerahan LED menggunakan analogWrite() dengan rentang bawaan 0–1023, bukan ledcWrite() seperti pada ESP32, sehingga rentangnya perlu disesuaikan dengan analogWriteRange(255) pada modifikasi program.

## L. Kesimpulan

Berdasarkan praktikum Modul 4 mengenai Komunikasi dan Pertukaran Data, dapat dipahami bahwa sistem IoT dapat melakukan pertukaran data dua arah menggunakan protokol MQTT melalui mekanisme publish dan subscribe.

Pada percobaan 4A, ESP8266 berhasil melakukan subscribe ke topic perintah, menerima pesan JSON, melakukan deserialisasi, dan mengendalikan LED sesuai perintah ON dan OFF. Pesan dengan format JSON yang tidak valid menghasilkan error parsing sehingga tidak diproses.

Pada percobaan 4B, ESP8266 berhasil mempublikasikan data suhu dari sensor DHT11 setiap 5 detik dan pada saat yang sama tetap dapat menerima perintah kendali LED. Penggunaan millis() sebagai pengganti delay() membuat proses publish tidak menghalangi client.loop() sehingga komunikasi full duplex dapat berjalan stabil.

Dengan demikian, komunikasi dua arah memungkinkan perangkat IoT tidak hanya mengirim data, tetapi juga dapat dikendalikan dari jarak jauh secara real-time.