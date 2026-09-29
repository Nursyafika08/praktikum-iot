# Modul 1 - Sensor dan Aktuator

**Nama:** Nursyafika  
**NIM:** H1H024023  
**Program Studi:** Teknik Komputer  

## Tools dan Komponen

- ESP32 DevKit
- Sensor DHT22
- Modul Relay 1 Channel
- LED
- Resistor 220 Ohm
- Breadboard
- Kabel Jumper
- Kabel USB
- Arduino IDE
- DHT Sensor Library

## Percobaan 1A - Akuisisi Data Sensor DHT22

Percobaan 1A dilakukan untuk memahami proses akuisisi data suhu dan kelembaban menggunakan sensor DHT22 pada ESP32.

### Konfigurasi Pin

- VCC DHT22 → 3.3V ESP32
- DATA DHT22 → GPIO 4
- GND DHT22 → GND
- Baud rate → 115200

Program membaca suhu dan kelembaban dari sensor DHT22 dan menampilkan hasilnya pada Serial Monitor setiap 2 detik. Program juga menggunakan fungsi `isnan()` untuk memeriksa apakah hasil pembacaan sensor valid.

### Hasil Percobaan

Hasil pembacaan sensor ditampilkan pada Serial Monitor. Beberapa hasil yang diperoleh:

```text
Suhu: 28.00 °C, Kelembaban: 47.00 %
Suhu: 28.50 °C, Kelembaban: 47.00 %
Suhu: 29.30 °C, Kelembaban: 49.00 %
Suhu: 30.20 °C, Kelembaban: 49.00 %
Suhu: 31.30 °C, Kelembaban: 50.00 %
Suhu: 31.80 °C, Kelembaban: 44.00 %
Suhu: 32.20 °C, Kelembaban: 43.00 %
Suhu: 32.30 °C, Kelembaban: 42.00 %
````

Berdasarkan hasil pengujian, ESP32 berhasil membaca data suhu dan kelembaban dari sensor DHT22.

## Modifikasi 1A - Rata-rata 5 Pembacaan

Program dimodifikasi agar melakukan lima kali pembacaan sensor sebelum menampilkan hasil. Data suhu dan kelembaban yang diperoleh kemudian dijumlahkan dan dibagi dengan jumlah pembacaan yang valid untuk mendapatkan nilai rata-rata.

File program:

`modul1_rata_rata_5_pembacaan.ino`

## Percobaan 2A - Kendali Aktuator Berdasarkan Data Sensor

Percobaan 2A menggunakan data suhu dari sensor DHT22 untuk mengendalikan relay atau LED sebagai aktuator.

### Konfigurasi Pin

* DATA DHT22 → GPIO 4
* IN Relay / Anoda LED → GPIO 26
* GND Relay / Katoda LED → GND

Threshold suhu yang digunakan adalah 30°C. Jika suhu lebih dari 30°C, aktuator diaktifkan. Jika suhu tidak melebihi threshold, aktuator dimatikan.

### Hasil Percobaan

Hasil pengujian pada Serial Monitor:

```text
Suhu: 24.80 °C -> Aktuator: OFF
Suhu: 25.30 °C -> Aktuator: OFF
Suhu: 27.60 °C -> Aktuator: OFF
Suhu: 28.90 °C -> Aktuator: OFF
Suhu: 30.20 °C -> Aktuator: OFF
Suhu: 31.50 °C -> Aktuator: ON
Suhu: 32.80 °C -> Aktuator: ON
Suhu: 33.80 °C -> Aktuator: ON
Suhu: 34.70 °C -> Aktuator: ON
Suhu: 35.60 °C -> Aktuator: ON
```

Berdasarkan hasil pengamatan, aktuator berada pada kondisi OFF pada sebagian besar pembacaan suhu awal dan mulai menunjukkan kondisi ON pada suhu 31.50°C hingga 35.60°C.

## Modifikasi 2A - Hysteresis

Program kendali aktuator dimodifikasi menggunakan hysteresis dengan dua batas suhu.

* Suhu > 30°C → Aktuator ON
* Suhu < 28°C → Aktuator OFF
* Suhu 28°C sampai 30°C → Kondisi aktuator dipertahankan

Penggunaan hysteresis bertujuan agar aktuator tidak terlalu sering berubah kondisi ketika suhu berada di sekitar batas threshold.

File program:

`modul1_histeresis.ino`

## Kendala yang Dihadapi

Selama pelaksanaan praktikum sempat terdapat beberapa kendala pada proses pengujian sehingga dilakukan pengecekan kembali terhadap program, rangkaian, dan koneksi komponen. Setelah dilakukan pengecekan, sensor dan aktuator dapat digunakan untuk melakukan percobaan.

## Kesimpulan

Praktikum Modul 1 menunjukkan bahwa ESP32 dapat digunakan untuk membaca suhu dan kelembaban menggunakan sensor DHT22. Data hasil pembacaan dapat digunakan sebagai input untuk mengendalikan aktuator berdasarkan nilai threshold.

Modifikasi rata-rata lima pembacaan digunakan untuk mengolah data sensor, sedangkan hysteresis digunakan untuk memberikan batas ON dan OFF yang berbeda pada kendali aktuator.
