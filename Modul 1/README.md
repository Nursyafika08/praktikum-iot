# MODUL 1 - SENSOR DAN AKTUATOR

*Akuisisi Data Sensor dan Kendali Aktuator*

*Nama Praktikan:* Nursyafika
*NIM:* H1H024023
*Program Studi:* Teknik Komputer
*Universitas:* Universitas Jenderal Soedirman
*Mata Kuliah:* Praktikum Sistem IoT (TK2450050)

## A. Tujuan Praktikum

1. Memahami konsep akuisisi data sensor pada perangkat IoT berbasis ESP8266.
2. Memahami konsep dasar kendali aktuator (relay, motor servo, buzzer) menggunakan ESP8266.
3. Mengimplementasikan pembacaan data sensor suhu dan kelembaban menggunakan sensor DHT11.
4. Mengimplementasikan kendali aktuator (relay) secara otomatis berdasarkan data sensor yang diperoleh.
5. Mampu menganalisis hubungan antara data sensor yang diakuisisi dengan respons aktuator pada sistem IoT.

## B. Alat dan Bahan

- ESP8266 DevKit (1 buah)
- Sensor DHT11 (1 buah)
- Modul Relay 1 channel (1 buah)
- LED (1 buah) sebagai simulasi beban aktuator
- Breadboard
- Kabel jumper
- Kabel USB
- Laptop/PC
- Arduino IDE dengan board manager ESP8266 dan library DHT Sensor

## C. Percobaan 1A: Akuisisi Data Sensor DHT11

### 1. Tujuan

Memahami dan mengimplementasikan proses akuisisi data sensor suhu dan kelembaban menggunakan sensor DHT11 pada ESP8266. Data hasil pembacaan ditampilkan pada Serial Monitor setiap 2 detik.

### 2. Konfigurasi Rangkaian

| Komponen | Koneksi |
|---|---|
| VCC DHT11 | 3V3 ESP8266 |
| DATA DHT11 | GPIO 4 (D2) |
| GND DHT11 | GND |

ESP8266 dihubungkan ke laptop menggunakan kabel USB untuk proses upload program dan pembacaan data pada Serial Monitor.

### 3. File Program

code/modul1a_dht11.ino

### 4. Penjelasan Program

- #include <DHT.h> memanggil library DHT yang digunakan untuk membaca data sensor.
- #define DHTPIN 4 menentukan pin data sensor pada GPIO 4 atau D2.
- #define DHTTYPE DHT11 menentukan jenis sensor yang digunakan.
- DHT dht(DHTPIN, DHTTYPE) membuat objek sensor bernama dht.
- Serial.begin(115200) mengatur komunikasi serial dengan baud rate 115200.
- dht.begin() menginisialisasi sensor DHT11.
- dht.readHumidity() membaca nilai kelembaban.
- dht.readTemperature() membaca nilai suhu dalam derajat Celsius.
- isnan() memeriksa apakah hasil pembacaan sensor bernilai NaN atau tidak valid.
- Jika data tidak valid, program menampilkan pesan kegagalan pembacaan.
- Jika data valid, suhu dan kelembaban ditampilkan pada Serial Monitor.
- delay(2000) memberikan jeda pembacaan selama 2 detik.

### 5. Hasil Pengamatan Percobaan 1A

| No. | Waktu | Kondisi Sensor | Suhu (°C) | Kelembaban (%) | Status |
|---|---|---|---:|---:|---|
| 1 | 00:00 | Normal | 28,00 | 47,4 | Valid |
| 2 | 00:02 | Disentuh api | 32,30 | 42,2 | Valid |
| 3 | 00:04 | Didekati ke AC | 28,90 | 40,6 | Valid |

### 6. Analisis

Pada kondisi normal, sensor membaca suhu 28,00°C dengan kelembaban 47,4%. Ketika sensor disentuh api, suhu meningkat menjadi 32,30°C dan kelembaban turun menjadi 42,2%. Ketika sensor didekatkan ke AC, suhu turun menjadi 28,90°C dan kelembaban menjadi 40,6%.

Ketiga pembacaan berstatus valid. Hasil ini menunjukkan bahwa sensor DHT11 berhasil membaca data suhu dan kelembaban serta menampilkannya pada Serial Monitor setiap 2 detik.

## D. Modifikasi Percobaan 1A: Rata-Rata Lima Pembacaan

### 1. Tujuan

Memodifikasi program agar data suhu dan kelembaban dirata-ratakan dari lima kali pembacaan sebelum ditampilkan.

### 2. File Program

code/modul1a_rata_rata.ino

### 3. Penjelasan Program

- JUMLAH_SAMPEL 5 menentukan jumlah pembacaan sensor yang akan dirata-ratakan.
- totalSuhu digunakan untuk menampung jumlah seluruh data suhu yang valid.
- totalKelembaban digunakan untuk menampung jumlah seluruh data kelembaban yang valid.
- dataValid digunakan untuk menghitung jumlah pembacaan yang berhasil.
- Perulangan for melakukan pembacaan sensor sebanyak lima kali.
- !isnan(h) && !isnan(t) memastikan hanya data suhu dan kelembaban yang valid yang dijumlahkan.
- totalSuhu += t menambahkan nilai suhu ke total suhu.
- totalKelembaban += h menambahkan nilai kelembaban ke total kelembaban.
- dataValid++ menambah penghitung data valid.
- delay(2000) memberikan jeda 2 detik antar pembacaan.
- Setelah perulangan selesai, total suhu dan kelembaban dibagi dengan jumlah data valid.
- Apabila tidak terdapat data valid, program menampilkan pesan kegagalan pembacaan.

Karena setiap sampel diberi jeda 2 detik, satu nilai rata-rata baru ditampilkan setiap 10 detik.

## E. Percobaan 2A: Kendali Aktuator Relay Berdasarkan Data Sensor

### 1. Tujuan

Memahami dan mengimplementasikan kendali aktuator relay secara otomatis berdasarkan data suhu yang diperoleh dari sensor DHT11.

Relay atau LED simulasi akan menyala ketika suhu melebihi ambang batas 30°C dan mati ketika suhu tidak melebihi ambang batas tersebut.

### 2. Konfigurasi Rangkaian

| Komponen | Koneksi |
|---|---|
| DATA DHT11 | GPIO 4 (D2) |
| IN Relay / Anoda LED | GPIO 5 (D1) |
| VCC Relay | VIN ESP8266 |
| GND Relay / Katoda LED | GND |

### 3. File Program

code/modul1b_relay.ino

### 4. Penjelasan Program

- #include <DHT.h> memanggil library untuk membaca sensor DHT11.
- DHTPIN 4 menentukan pin sensor pada GPIO 4 (D2).
- RELAYPIN 5 menentukan pin kendali relay atau LED pada GPIO 5 (D1).
- suhuThreshold = 30.0 menetapkan nilai ambang batas suhu sebesar 30°C.
- Serial.begin(115200) mengaktifkan komunikasi serial.
- dht.begin() menginisialisasi sensor DHT11.
- pinMode(RELAYPIN, OUTPUT) mengatur pin relay sebagai output.
- digitalWrite(RELAYPIN, LOW) memastikan aktuator mati pada kondisi awal.
- dht.readTemperature() membaca suhu dari sensor.
- isnan(suhu) memeriksa apakah pembacaan suhu valid.
- if (suhu > suhuThreshold) memeriksa apakah suhu lebih dari 30°C.
- Jika suhu lebih dari 30°C, pin relay diberi nilai HIGH sehingga aktuator aktif.
- Jika suhu kurang dari atau sama dengan 30°C, pin relay diberi nilai LOW sehingga aktuator mati.
- delay(2000) memberikan jeda pembacaan selama 2 detik.

### 5. Hasil Pengamatan Percobaan 2A

| No. | Waktu | Suhu (°C) | Threshold (°C) | Status Aktuator |
|---|---|---:|---:|---|
| 1 | 00:00 | 26,3 | 30 | OFF |
| 2 | 00:02 | 26,7 | 30 | ON |
| 3 | 00:04 | 27,0 | 30 | OFF |

### 6. Analisis

Sistem kendali menggunakan threshold sebesar 30°C. Berdasarkan uraian hasil pengamatan pada BCP, aktuator berada dalam kondisi OFF ketika suhu berada di bawah atau sama dengan 30°C. Aktuator berubah menjadi ON ketika suhu meningkat melewati 30°C.

Hasil tersebut menunjukkan bahwa ESP8266 dapat menggunakan data suhu dari sensor DHT11 sebagai dasar untuk menentukan kondisi aktuator.

## F. Modifikasi Percobaan 2A: Kendali Histerisis

### 1. Tujuan

Memodifikasi program kendali aktuator menggunakan dua ambang batas, yaitu aktuator menyala ketika suhu di atas 30°C dan mati ketika suhu di bawah 28°C.

### 2. File Program

code/modul1b_histerisis.ino

### 3. Penjelasan Program

- batasAtas = 30.0 menentukan suhu untuk mengaktifkan aktuator.
- batasBawah = 28.0 menentukan suhu untuk menonaktifkan aktuator.
- aktuatorOn menyimpan kondisi aktuator saat ini.
- Jika suhu lebih dari batas atas, aktuatorOn diubah menjadi true.
- Jika suhu kurang dari batas bawah, aktuatorOn diubah menjadi false.
- Jika suhu berada di antara 28°C dan 30°C, status aktuator tidak berubah.
- digitalWrite(RELAYPIN, aktuatorOn ? HIGH : LOW) mengatur keluaran relay berdasarkan status aktuator.
- Serial.println() menampilkan status ON atau OFF pada Serial Monitor.

### 4. Prinsip Kendali Histerisis

Kendali histerisis menggunakan dua nilai ambang batas untuk mengurangi perubahan kondisi aktuator yang terlalu sering.

- Suhu lebih dari 30°C: aktuator ON.
- Suhu kurang dari 28°C: aktuator OFF.
- Suhu antara 28°C sampai 30°C: kondisi aktuator dipertahankan.

## G. Jawaban Pertanyaan Praktikum Percobaan 1A

### 1. Gambarkan diagram alur proses akuisisi data sensor DHT11!

Mulai → Inisialisasi Serial dan sensor DHT11 → Baca kelembaban dan suhu dari sensor DHT11 → Data valid (bukan NaN)?

Jika tidak, tampilkan pesan gagal membaca sensor lalu lanjut ke delay 2 detik.

Jika ya, tampilkan data suhu dan kelembaban ke Serial Monitor → Delay 2 detik → Ulangi dari pembacaan data.

### 2. Apa fungsi perintah isnan() pada program tersebut?

Fungsi isnan() digunakan untuk memeriksa apakah hasil pembacaan sensor bernilai NaN (Not a Number). Library DHT akan mengembalikan nilai NaN apabila pembacaan gagal, misalnya karena kabel data tidak terhubung dengan benar atau sensor tidak merespons.

Dengan isnan(), program dapat mendeteksi kegagalan tersebut dan menampilkan pesan peringatan, sehingga data yang tidak valid tidak ditampilkan atau diolah sebagai data suhu dan kelembaban.

### 3. Mengapa diperlukan jeda minimal sekitar 2 detik antar pembacaan sensor DHT11?

Sensor seri DHT memiliki laju pengambilan data (sampling rate) yang terbatas. DHT11 maksimal sekitar 1 Hz atau satu pembacaan per detik, sedangkan DHT22 maksimal sekitar 0,5 Hz atau satu pembacaan per 2 detik.

Di dalam sensor, proses konversi dan pengiriman data membutuhkan waktu, dan hasil pengukuran hanya diperbarui pada interval tersebut. Karena modul menetapkan jeda sekitar 2 detik, delay(2000) memenuhi batas minimum kedua jenis sensor sehingga pembacaan stabil.

Apabila sensor dibaca lebih cepat dari kemampuannya, data yang didapat dapat berupa nilai lama atau gagal terbaca sehingga menghasilkan NaN.

### 4. Modifikasi program agar data suhu dan kelembaban dirata-ratakan dari lima kali pembacaan sebelum ditampilkan!

Modifikasi dilakukan dengan menambahkan konstanta JUMLAH_SAMPEL bernilai 5 sebagai jumlah pembacaan. Variabel totalSuhu, totalKelembaban, dan dataValid digunakan untuk menampung jumlah nilai serta banyaknya pembacaan yang valid.

Perulangan for membaca sensor sebanyak lima kali dengan jeda 2 detik. Hanya data yang bukan NaN yang dijumlahkan. Setelah perulangan selesai, jumlah dibagi dengan dataValid untuk memperoleh nilai rata-rata yang kemudian ditampilkan pada Serial Monitor.

## H. Jawaban Pertanyaan Praktikum Percobaan 2A

### 1. Mengapa diperlukan nilai ambang batas (threshold) dalam sistem kendali aktuator berbasis sensor?

Threshold diperlukan sebagai batas keputusan bagi mikrokontroler untuk menentukan kapan aktuator harus aktif dan kapan harus nonaktif. Tanpa threshold, program tidak memiliki acuan untuk mengubah data sensor yang berupa angka menjadi perintah kendali.

Dengan adanya threshold, aktuator hanya bekerja ketika kondisi lingkungan telah mencapai nilai yang dianggap perlu ditangani, sehingga sistem dapat berjalan otomatis dan tidak bekerja secara berlebihan.

### 2. Apa yang akan terjadi apabila nilai suhuThreshold diturunkan menjadi 20,0°C?

Apabila suhuThreshold diturunkan menjadi 20,0°C, aktuator akan menyala hampir sepanjang waktu karena suhu ruangan pada percobaan, sekitar 24 sampai 35°C, sudah berada di atas nilai tersebut.

Aktuator tidak lagi merespons perubahan suhu yang berarti sehingga fungsi kendali otomatis menjadi tidak efektif dan dapat menyebabkan pemborosan energi.

### 3. Apa perbedaan kendali aktuator secara terus-menerus dengan kendali menggunakan histerisis?

Pada kendali dengan kondisi tunggal, hanya digunakan satu ambang batas sehingga aktuator berubah status setiap kali suhu melewati nilai tersebut. Ketika suhu berada di sekitar threshold, aktuator dapat berpindah ON dan OFF berulang kali dengan cepat.

Pada kendali histerisis digunakan dua ambang batas, yaitu batas atas untuk menyalakan aktuator dan batas bawah untuk mematikannya. Selisih antara kedua batas tersebut membuat perubahan status aktuator lebih stabil dan mengurangi keausan pada relay.

### 4. Modifikasi program agar menggunakan dua ambang batas (histerisis)!

Modifikasi dilakukan dengan menggunakan dua konstanta, yaitu batasAtas sebesar 30°C dan batasBawah sebesar 28°C, serta variabel aktuatorOn untuk menyimpan status aktuator terakhir.

Aktuator dinyalakan ketika suhu lebih dari batas atas dan dimatikan ketika suhu kurang dari batas bawah. Ketika suhu berada di antara 28°C dan 30°C, status aktuator tidak diubah sehingga tetap mengikuti kondisi sebelumnya.

## I. Pertanyaan Analisis

### 1. Uraikan hasil tugas pada praktikum yang telah dilakukan pada setiap percobaan!

Pada percobaan 1A, ESP8266 berhasil membaca data suhu dan kelembaban dari sensor DHT11 dan menampilkannya pada Serial Monitor setiap 2 detik. Suhu terbaca mulai dari 28,00°C hingga 32,30°C dengan kelembaban berkisar antara 42,00% hingga 52,00%, dan seluruh data valid tanpa nilai NaN.

Pada percobaan 2A, ESP8266 berhasil mengendalikan aktuator berdasarkan data suhu dengan threshold 30°C. Aktuator berstatus OFF ketika suhu berada di bawah atau sama dengan 30°C dan berubah menjadi ON ketika suhu melewati threshold.

### 2. Bagaimana pengaruh akurasi dan waktu tanggap sensor terhadap kecepatan reaksi aktuator pada sistem IoT?

Akurasi sensor menentukan ketepatan keputusan yang diambil sistem. Jika pembacaan sensor tidak akurat, mikrokontroler dapat menerima nilai suhu yang tidak sesuai dengan kondisi sebenarnya sehingga aktuator berpotensi menyala atau mati pada waktu yang tidak tepat.

Waktu tanggap sensor menentukan seberapa cepat perubahan kondisi lingkungan dapat dibaca oleh sistem. Semakin cepat sensor memberikan data yang sesuai, semakin cepat pula mikrokontroler dapat memproses data dan memberikan perintah kepada aktuator.

### 3. Apa keuntungan penggunaan histerisis dibandingkan satu nilai threshold?

Penggunaan histerisis memberikan kestabilan pada sistem kendali karena aktuator memiliki batas berbeda untuk kondisi ON dan OFF. Dengan demikian, perubahan suhu kecil di sekitar satu nilai threshold tidak langsung menyebabkan aktuator berganti kondisi berulang kali.

## J. Kesimpulan

Praktikum Modul 1 menunjukkan bahwa ESP8266 dapat digunakan untuk melakukan akuisisi data suhu dan kelembaban menggunakan sensor DHT11 serta mengendalikan aktuator relay berdasarkan hasil pembacaan sensor.

Pada percobaan 1A, sensor berhasil membaca dan menampilkan suhu serta kelembaban pada Serial Monitor. Modifikasi rata-rata lima pembacaan dilakukan untuk memperoleh nilai rata-rata dari beberapa data sensor.

Pada percobaan 2A, aktuator dikendalikan menggunakan threshold 30°C. Modifikasi histerisis menggunakan batas atas 30°C dan batas bawah 28°C agar perubahan status aktuator lebih stabil.

Dengan demikian, praktikum ini memperlihatkan hubungan antara proses pembacaan sensor, pengolahan data, dan pengendalian aktuator pada sistem Internet of Things.