
# MODUL 2 - KONFIGURASI JARINGAN

*Konfigurasi WiFi Mode Station dan Access Point*

*Nama Praktikan:* Nursyafika
*NIM:* H1H024023
*Program Studi:* Teknik Komputer
*Universitas:* Universitas Jenderal Soedirman
*Mata Kuliah:* Praktikum Sistem IoT (TK2450050)

## A. Tujuan Praktikum

1. Memahami konsep dasar jaringan nirkabel (WiFi) pada perangkat IoT berbasis ESP8266.
2. Memahami perbedaan mode Station (STA), Access Point (AP), dan AP+STA pada ESP8266.
3. Mengimplementasikan konfigurasi jaringan untuk menghubungkan ESP8266 ke jaringan WiFi yang sudah tersedia.
4. Mengimplementasikan ESP8266 sebagai Access Point mandiri yang dapat diakses oleh perangkat lain.
5. Mampu membaca dan menganalisis parameter jaringan seperti IP Address, MAC Address, dan kekuatan sinyal (RSSI).

## B. Alat dan Bahan

- Board ESP8266 NodeMCU DevKit (1 buah)
- Kabel USB Micro-USB
- Laptop/PC dengan Arduino IDE dan board manager ESP8266
- Jaringan WiFi atau hotspot smartphone beserta SSID dan password
- Smartphone untuk menguji koneksi ke Access Point ESP8266
- LED (1 buah)
- Resistor 220 Ohm (1 buah)
- Kabel jumper dan breadboard

## C. Percobaan 2A: Konfigurasi Mode Station (STA)

### 1. Tujuan

Memahami dan mengimplementasikan konfigurasi ESP8266 pada mode Station (STA) agar dapat terhubung ke jaringan WiFi yang sudah tersedia.

Parameter jaringan yang diamati berupa status koneksi, IP Address, MAC Address, dan kekuatan sinyal (RSSI).

### 2. Rangkaian

Pada percobaan ini, ESP8266 dihubungkan ke laptop menggunakan kabel USB untuk proses upload program dan pembacaan Serial Monitor.

LED indikator dihubungkan ke pin D2 melalui resistor 220 Ohm, kemudian kaki LED lainnya dihubungkan ke GND. ESP8266 terhubung ke jaringan WiFi yang telah disiapkan.

### 3. File Program

code/modul2a_sta.ino

### 4. Penjelasan Program

- #include <ESP8266WiFi.h> memanggil library untuk mengatur dan memonitor koneksi WiFi pada ESP8266.
- #include "secrets.h" memanggil konfigurasi SSID dan password yang disimpan secara lokal.
- Variabel ssid menyimpan nama jaringan WiFi yang akan dituju.
- Variabel password menyimpan kata sandi jaringan WiFi.
- ledPin = D2 menentukan pin D2 sebagai LED indikator koneksi.
- Serial.begin(115200) mengatur komunikasi Serial Monitor dengan baud rate 115200.
- pinMode(ledPin, OUTPUT) mengatur pin LED sebagai output.
- digitalWrite(ledPin, LOW) memastikan LED mati pada kondisi awal.
- WiFi.mode(WIFI_STA) mengatur ESP8266 agar bekerja sebagai Station.
- WiFi.begin(ssid, password) memulai proses koneksi ke jaringan WiFi.
- Perulangan while (WiFi.status() != WL_CONNECTED) membuat program menunggu hingga koneksi berhasil.
- delay(500) memberikan jeda selama 500 milidetik.
- Serial.print(".") menampilkan tanda titik selama proses koneksi berlangsung.
- WiFi.localIP() mengambil alamat IP yang diberikan jaringan.
- WiFi.macAddress() menampilkan alamat MAC ESP8266.
- WiFi.RSSI() membaca kekuatan sinyal WiFi dalam satuan dBm.
- digitalWrite(ledPin, HIGH) menyalakan LED setelah koneksi berhasil.
- Pada fungsi loop(), program memeriksa status koneksi setiap 5 detik.
- Jika terhubung, Serial Monitor menampilkan status Terhubung.
- Jika terputus, Serial Monitor menampilkan status Terputus dan LED dimatikan.

### 5. Hasil Pengamatan Percobaan 2A

| No. | Waktu (s) | Status Koneksi | IP Address | RSSI (dBm) | LED |
|---|---:|---|---|---:|---|
| 1 | 0 | Terhubung | 192.168.211.166 | -39 | Nyala |
| 2 | 5 | Terhubung | 192.168.211.166 | -39 | Nyala |
| 3 | 10 | Terhubung | 192.168.211.166 | -39 | Nyala |
| 4 | 15 | Terhubung | 192.168.211.166 | -39 | Nyala |
| 5 | 20 | Terputus | - | - | Mati |
| 6 | 25 | Terhubung | 192.168.45.166 | -18 | Nyala |
| 7 | 30 | Terhubung | 192.168.45.166 | -18 | Nyala |
| 8 | 35 | Terhubung | 192.168.45.166 | -18 | Nyala |
| 9 | 40 | Terhubung | 192.168.45.166 | -18 | Nyala |
| 10 | 45 | Terhubung | 192.168.45.166 | -18 | Nyala |

MAC Address yang teramati: 68:C6:3A:D5:35:34.

### 6. Pengujian Mode Station

| No. | Kondisi Pengujian | Status Koneksi |
|---|---|---|
| 1 | Kredensial benar | Terhubung |
| 2 | Password salah | Terputus |
| 3 | SSID salah | Terputus |

### 7. Analisis

Pada detik ke-0 sampai ke-15, ESP8266 berstatus terhubung dengan IP Address 192.168.211.166, MAC Address 68:C6:3A:D5:35:34, dan RSSI -39 dBm. LED indikator juga menyala.

Pada detik ke-20, koneksi berubah menjadi terputus sehingga IP Address dan RSSI tidak terbaca dan LED padam. Pada detik ke-25, ESP8266 kembali terhubung dengan IP Address 192.168.45.166 dan RSSI -18 dBm. Kondisi tersebut bertahan sampai detik ke-45 dengan LED kembali menyala.

Perubahan alamat IP menunjukkan bahwa alamat diberikan kembali oleh jaringan ketika koneksi terjalin kembali.

Pada pengujian kredensial, SSID dan password yang benar menghasilkan status terhubung. Ketika password atau SSID salah, ESP8266 tidak dapat terhubung sehingga Serial Monitor hanya menampilkan tanda titik karena program masih menunggu koneksi pada perulangan while.

## D. Modifikasi Percobaan 2A: Reconnect Otomatis

### 1. Tujuan

Memodifikasi program agar ESP8266 mencoba menghubungkan ulang secara otomatis apabila koneksi WiFi terputus.

### 2. File Program

code/modul2a_sta_modifikasi.ino

### 3. Penjelasan Program

- Fungsi hubungkanWiFi() dibuat untuk mengelompokkan proses koneksi WiFi agar dapat dipanggil kembali.
- WiFi.begin(ssid, password) memulai koneksi ke jaringan WiFi.
- Perulangan while menunggu sampai ESP8266 berhasil terhubung.
- WiFi.localIP() menampilkan alamat IP setelah koneksi berhasil.
- WiFi.macAddress() menampilkan alamat MAC perangkat.
- WiFi.RSSI() menampilkan kekuatan sinyal.
- digitalWrite(ledPin, HIGH) menyalakan LED ketika koneksi berhasil.
- Pada fungsi setup(), mode WiFi diatur menjadi WIFI_STA, kemudian fungsi hubungkanWiFi() dipanggil.
- Pada fungsi loop(), program memeriksa status koneksi.
- Jika koneksi terputus, LED dimatikan dan Serial Monitor menampilkan pesan bahwa perangkat mencoba menghubungkan ulang.
- WiFi.disconnect() memutuskan sisa koneksi lama.
- hubungkanWiFi() dipanggil kembali agar ESP8266 mencoba terhubung ulang.

Dengan modifikasi ini, proses koneksi tidak hanya dilakukan satu kali pada fungsi setup(), tetapi dapat dijalankan kembali ketika koneksi terputus.

## E. Percobaan 2B: Konfigurasi Mode Access Point (AP)

### 1. Tujuan

Memahami dan mengimplementasikan konfigurasi ESP8266 sebagai Access Point (AP) yang dapat diakses langsung oleh perangkat lain seperti smartphone.

Jumlah perangkat yang terhubung ke Access Point dipantau melalui Serial Monitor.

### 2. Rangkaian

ESP8266 dihubungkan ke laptop menggunakan kabel USB. Pada percobaan ini ESP8266 tidak terhubung ke router atau hotspot karena ESP8266 sendiri yang menyediakan jaringan WiFi.

### 3. File Program

code/modul2b_ap.ino

### 4. Penjelasan Program

- #include <ESP8266WiFi.h> memanggil library pengaturan WiFi ESP8266.
- ap_ssid menyimpan nama jaringan Access Point yang dibuat ESP8266.
- ap_password menyimpan password Access Point.
- Serial.begin(115200) mengatur komunikasi serial.
- WiFi.mode(WIFI_AP) mengatur ESP8266 menjadi Access Point.
- WiFi.softAP(ap_ssid, ap_password) mengaktifkan jaringan Access Point menggunakan SSID dan password yang ditentukan.
- WiFi.softAPIP() mengambil alamat IP Access Point.
- Serial Monitor menampilkan pesan bahwa Access Point telah aktif, nama SSID, dan alamat IP.
- WiFi.softAPgetStationNum() menghitung jumlah perangkat yang terhubung.
- Jumlah perangkat ditampilkan setiap 5 detik menggunakan delay(5000).

### 5. Hasil Pengamatan Percobaan 2B

| No. | Parameter | Nilai Pengamatan |
|---|---|---|
| 1 | SSID | ESP32-RASTA |
| 2 | Password | Berhasil digunakan |
| 3 | IP Address AP | 192.168.4.1 |
| 4 | Status Access Point | Aktif |
| 5 | SSID terdeteksi pada client | Ya |
| 6 | Perangkat berhasil terhubung | 3 smartphone |

### 6. Pengamatan Jumlah Perangkat Terhubung

| No. | Waktu (s) | Jumlah Client | Keterangan |
|---|---:|---:|---|
| 1 | 0 | 0 | Belum ada perangkat terhubung |
| 2 | 5 | 0 | Belum ada perangkat terhubung |
| 3 | 10 | 0 | Belum ada perangkat terhubung |
| 4 | 15 | 1 | Smartphone pertama terhubung |
| 5 | 20 | 1 | Jumlah client tetap |
| 6 | 25 | 2 | Smartphone kedua terhubung |
| 7 | 30 | 2 | Jumlah client tetap |
| 8 | 35 | 2 | Jumlah client tetap |
| 9 | 40 | 3 | Smartphone ketiga terhubung |
| 10 | 45 | 3 | Jumlah client tetap |

### 7. Analisis

ESP8266 berhasil membuat jaringan WiFi Access Point dengan IP Address 192.168.4.1. SSID dapat terdeteksi pada perangkat client dan tiga smartphone berhasil terhubung menggunakan password yang telah ditentukan.

Berdasarkan pengamatan, jumlah perangkat yang terhubung pada Serial Monitor bertambah mengikuti perangkat yang tersambung. Pada detik ke-0 sampai ke-10 terdapat 0 client, detik ke-15 sampai ke-20 terdapat 1 client, detik ke-25 sampai ke-35 terdapat 2 client, dan detik ke-40 sampai ke-45 terdapat 3 client.

Hasil ini menunjukkan bahwa ESP8266 dapat menyediakan jaringan WiFi sendiri dan memantau jumlah perangkat yang terhubung.

*Catatan konfigurasi BCP:* kode program percobaan mencantumkan SSID APLAFF, sedangkan tabel hasil pengamatan mencantumkan ESP32-RASTA. Keduanya merupakan informasi yang berbeda di dalam BCP, sehingga nama yang digunakan saat pengujian perlu disesuaikan dengan konfigurasi aktual perangkat.

## F. Modifikasi Percobaan 2B: Mode AP+STA

### 1. Tujuan

Memodifikasi program agar ESP8266 berjalan pada mode AP+STA, yaitu terhubung ke jaringan WiFi sekaligus menyediakan Access Point.

### 2. File Program

code/modul2b_apsta.ino

### 3. Penjelasan Program

- ssid menyimpan nama WiFi yang dituju oleh ESP8266 dalam mode Station.
- password menyimpan password WiFi Station.
- ap_ssid menyimpan nama jaringan yang dibuat ESP8266.
- ap_password menyimpan password Access Point.
- Serial.begin(115200) mengaktifkan komunikasi serial.
- WiFi.mode(WIFI_AP_STA) mengaktifkan mode Access Point dan Station secara bersamaan.
- WiFi.softAP(ap_ssid, ap_password) menjalankan Access Point.
- WiFi.begin(ssid, password) menghubungkan ESP8266 ke jaringan WiFi yang sudah tersedia.
- Perulangan while menunggu sampai koneksi Station berhasil.
- WiFi.localIP() menampilkan IP Address pada mode Station.
- WiFi.softAPIP() menampilkan IP Address pada mode Access Point.
- Pada fungsi loop(), program menampilkan status koneksi Station.
- WiFi.softAPgetStationNum() menampilkan jumlah perangkat yang terhubung ke Access Point.
- delay(5000) memberikan jeda tampilan selama 5 detik.

Dengan mode AP+STA, ESP8266 dapat tetap menyediakan jaringan lokal sekaligus terhubung ke jaringan WiFi lain.

## G. Jawaban Pertanyaan Praktikum Percobaan 2A

### 1. Gambarkan diagram alur proses koneksi ESP8266 ke jaringan WiFi pada program di atas!

Mulai → Inisialisasi Serial, pin LED sebagai OUTPUT, dan LED dimatikan → Atur mode WIFI_STA dan jalankan WiFi.begin() → Apakah WiFi terhubung?

Jika belum, tunggu 500 ms dan cetak tanda titik, kemudian periksa kembali status koneksi.

Jika sudah, tampilkan IP Address, MAC Address, dan RSSI → Nyalakan LED → Pada fungsi loop(), periksa status koneksi setiap 5 detik.

Jika terhubung, tampilkan "Status: Terhubung". Jika terputus, tampilkan "Status: Terputus" dan matikan LED → Ulangi pemeriksaan.

### 2. Apa fungsi perintah WiFi.mode(WIFI_STA)?

Perintah tersebut mengatur ESP8266 bekerja pada mode Station, yaitu berperan sebagai klien yang terhubung ke jaringan WiFi yang sudah ada, misalnya hotspot smartphone atau router.

Pada mode ini ESP8266 memperoleh alamat IP dari jaringan tersebut dan tidak membuat jaringan sendiri.

### 3. Jelaskan apa yang terjadi apabila SSID atau password yang dimasukkan salah!

Apabila SSID atau password salah, ESP8266 tidak dapat terhubung ke jaringan. Jika SSID salah, jaringan yang dituju tidak ditemukan, sedangkan jika password salah, proses autentikasi ke jaringan ditolak.

Akibatnya, WiFi.status() tidak pernah bernilai WL_CONNECTED, sehingga perulangan while pada setup() terus berjalan dan Serial Monitor hanya menampilkan tanda titik. ESP8266 tidak memperoleh IP Address dan LED tetap mati.

### 4. Modifikasi program agar ESP8266 mencoba menghubungkan ulang secara otomatis apabila koneksi WiFi terputus!

Modifikasi dilakukan dengan membuat fungsi hubungkanWiFi() yang berisi proses koneksi, menunggu sampai terhubung, menampilkan informasi jaringan, dan menyalakan LED.

Pada fungsi loop(), apabila status koneksi bukan WL_CONNECTED, program menampilkan status terputus, mematikan LED, memutus sisa koneksi dengan WiFi.disconnect(), kemudian memanggil hubungkanWiFi() kembali sehingga ESP8266 mencoba terhubung ulang secara otomatis.

## H. Jawaban Pertanyaan Praktikum Percobaan 2B

### 1. Mengapa alamat IP default Access Point pada ESP8266 umumnya bernilai 192.168.4.1?

Alamat 192.168.4.1 merupakan alamat default yang sudah ditetapkan pada firmware atau SDK ESP8266 untuk antarmuka Soft Access Point. ESP8266 menggunakan alamat tersebut sebagai gateway sekaligus server DHCP pada jaringan 192.168.4.0/24.

Dengan demikian, perangkat yang terhubung akan mendapatkan alamat IP dengan awalan 192.168.4.x. Alamat ini dapat diubah menggunakan WiFi.softAPConfig(), tetapi jika tidak diatur maka nilai default tersebut yang dipakai.

### 2. Apa perbedaan mendasar antara mode Station dan mode Access Point pada ESP8266?

Pada mode Station, ESP8266 berperan sebagai klien yang terhubung ke jaringan WiFi yang sudah ada dan memperoleh alamat IP dari router atau hotspot.

Pada mode Access Point, ESP8266 berperan sebagai penyedia jaringan yang dapat diakses langsung oleh perangkat lain tanpa router eksternal. ESP8266 sendiri membagikan alamat IP kepada perangkat yang terhubung.

Mode Station digunakan ketika ESP8266 perlu mengakses internet atau server, sedangkan mode Access Point digunakan misalnya untuk konfigurasi awal perangkat.

### 3. Jelaskan risiko keamanan apabila password Access Point tidak diberikan atau terlalu sederhana!

Apabila Access Point tidak memakai password atau password terlalu sederhana, siapa pun yang berada dalam jangkauan dapat terhubung tanpa izin.

Risikonya antara lain pihak lain dapat mengakses layanan atau data pada perangkat, menyadap data yang dikirim, mengubah konfigurasi, atau memanfaatkan perangkat untuk serangan lain. Password yang sederhana juga mudah ditebak melalui percobaan berulang.

Karena itu, Access Point sebaiknya menggunakan password minimal 8 karakter yang sulit ditebak.

### 4. Modifikasi program agar ESP8266 berjalan pada mode AP+STA!

Pada modifikasi ini, mode WiFi diatur menjadi WIFI_AP_STA sehingga ESP8266 dapat bekerja sebagai Access Point dan Station secara bersamaan.

WiFi.softAP() mengaktifkan Access Point dengan SSID dan password yang ditentukan, sedangkan WiFi.begin() menghubungkan ESP8266 ke jaringan WiFi yang dituju.

Setelah Station terhubung, Serial Monitor menampilkan IP Address mode STA melalui WiFi.localIP() dan IP Address mode AP melalui WiFi.softAPIP().

Pada fungsi loop(), program menampilkan status koneksi STA dan jumlah perangkat yang terhubung ke Access Point setiap 5 detik.

## I. Pertanyaan Analisis

### 1. Uraikan hasil tugas pada praktikum yang telah dilakukan pada setiap percobaan!

Pada percobaan 2A, ESP8266 berhasil terhubung ke jaringan WiFi pada mode Station. Serial Monitor menampilkan status koneksi, IP Address, MAC Address, dan RSSI, serta LED indikator menyala ketika terhubung.

Pada pengamatan selama 45 detik, koneksi sempat terputus pada detik ke-20 dan LED mati, kemudian ESP8266 terhubung kembali pada detik ke-25 dengan IP Address baru dan LED kembali menyala. Pada pengujian kredensial, koneksi hanya berhasil ketika SSID dan password benar.

Pada percobaan 2B, ESP8266 berhasil menjadi Access Point dengan IP Address 192.168.4.1. SSID terdeteksi pada perangkat client dan tiga smartphone berhasil terhubung. Jumlah perangkat yang terhubung pada Serial Monitor bertambah dari 0 menjadi 3 seiring perangkat yang tersambung.

### 2. Bagaimana pengaruh kekuatan sinyal (RSSI) terhadap kestabilan koneksi WiFi pada perangkat IoT?

RSSI menunjukkan kekuatan sinyal yang diterima dalam satuan dBm. Semakin mendekati 0 dBm, sinyal semakin kuat, sedangkan nilai yang semakin negatif menunjukkan sinyal yang semakin lemah.

Sinyal yang lemah membuat data lebih sering hilang dan dikirim ulang, sehingga koneksi menjadi lambat, tidak stabil, dan lebih mudah terputus. Pada perangkat IoT yang bekerja terus-menerus, hal ini dapat menyebabkan data terlambat atau tidak terkirim.

Pada pengamatan, RSSI bernilai -39 dBm dan -18 dBm yang tergolong kuat. Koneksi yang terputus pada detik ke-20 terjadi ketika RSSI masih -39 dBm, sehingga pemutusan koneksi tidak hanya dipengaruhi kekuatan sinyal, tetapi juga faktor lain seperti kondisi hotspot atau jaringan.

### 3. Bagaimana cara kerja ESP8266 dalam membedakan peran sebagai klien (Station) dan sebagai penyedia jaringan (Access Point)?

Peran ESP8266 ditentukan melalui pengaturan mode WiFi pada program menggunakan WiFi.mode().

Pada mode WIFI_STA, program memanggil WiFi.begin(ssid, password) sehingga ESP8266 mencari dan bergabung ke jaringan yang sudah ada. Perangkat memperoleh alamat IP dari router atau hotspot yang dapat dibaca dengan WiFi.localIP().

Pada mode WIFI_AP, program memanggil WiFi.softAP(ssid, password) sehingga ESP8266 membuat jaringan sendiri, membagikan alamat IP kepada perangkat yang terhubung, dan jumlah perangkat tersebut dapat dipantau dengan WiFi.softAPgetStationNum().

Mode WIFI_AP_STA menjalankan kedua peran tersebut secara bersamaan.

### 4. Bagaimana kombinasi mode Station dan Access Point (AP+STA) dapat dimanfaatkan dalam skenario nyata sistem IoT?

Pada proses provisioning, perangkat IoT yang baru belum mengetahui SSID dan password WiFi pengguna. Perangkat dapat menyalakan Access Point sehingga pengguna menghubungkan smartphone langsung ke perangkat, lalu memasukkan SSID dan password WiFi rumah melalui halaman konfigurasi.

Setelah data diterima, perangkat menggunakan mode Station untuk terhubung ke WiFi rumah. Dengan mode AP+STA, perangkat tetap dapat menyediakan Access Point untuk konfigurasi atau pemantauan lokal sekaligus terhubung ke internet.

## J. Kendala yang Dihadapi

Selama pelaksanaan praktikum Modul 2 terdapat beberapa kendala, yaitu:

1. Modul menggunakan ESP32 dengan library WiFi.h dan LED pada GPIO 2, sedangkan praktikum menggunakan ESP8266 NodeMCU. Program disesuaikan menggunakan library ESP8266WiFi.h dan pin LED D2.
2. Pada percobaan 2A, koneksi WiFi sempat terputus pada detik ke-20 dan LED mati. ESP8266 kemudian terhubung kembali dengan alamat IP yang berbeda sehingga data pengamatan perlu dicatat ulang sesuai kondisi tersebut.
3. Ketika SSID atau password diubah menjadi salah, ESP8266 tidak dapat terhubung dan Serial Monitor hanya menampilkan tanda titik karena program menunggu koneksi tanpa batas waktu.
4. Pada percobaan 2B, password Access Point harus terdiri dari minimal 8 karakter agar Access Point dapat aktif, dan jumlah perangkat yang terhubung baru terbaca pada Serial Monitor setelah smartphone berhasil tersambung.

## K. Kesimpulan

Berdasarkan praktikum Modul 2 mengenai Konfigurasi Jaringan, dapat dipahami bahwa ESP8266 dapat bekerja pada mode Station untuk terhubung ke jaringan WiFi yang sudah ada dan pada mode Access Point untuk menyediakan jaringan sendiri.

Pada percobaan 2A, ESP8266 berhasil terhubung ke jaringan WiFi dan menampilkan status koneksi, IP Address, MAC Address, dan RSSI pada Serial Monitor, sedangkan SSID atau password yang salah membuat koneksi gagal.

Pada percobaan 2B, ESP8266 berhasil menjadi Access Point dengan IP Address 192.168.4.1 yang dapat diakses oleh tiga smartphone, dan jumlah perangkat yang terhubung dapat dipantau melalui Serial Monitor.

Kekuatan sinyal RSSI memengaruhi kestabilan koneksi, sedangkan kombinasi mode AP+STA dapat dimanfaatkan untuk konfigurasi awal perangkat IoT.
