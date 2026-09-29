````markdown
# Modul 1 - Sensor dan Aktuator

**Nama:** Nursyafika  
**NIM:** H1H024023  

## Tools dan Komponen

- ESP32 DevKit
- Sensor DHT22
- Relay 1 Channel
- LED
- Resistor 220 Ohm
- Breadboard
- Kabel Jumper
- Arduino IDE

## Percobaan 1A - Akuisisi Data Sensor DHT22

Percobaan ini dilakukan untuk membaca data suhu dan kelembaban menggunakan sensor DHT22 yang terhubung dengan ESP32.

### Konfigurasi

- DHT22 DATA → GPIO 4
- DHT22 VCC → 3.3V
- DHT22 GND → GND
- Baud Rate → 115200

Program membaca suhu dan kelembaban setiap 2 detik dan menampilkan hasilnya pada Serial Monitor.

### Hasil

```text
Suhu: 28.00 °C, Kelembaban: 47.00 %
Suhu: 29.30 °C, Kelembaban: 49.00 %
Suhu: 31.30 °C, Kelembaban: 50.00 %
Suhu: 32.30 °C, Kelembaban: 42.00 %
````

Hasil percobaan menunjukkan bahwa sensor DHT22 dapat membaca data suhu dan kelembaban menggunakan ESP32.

## Modifikasi 1A - Rata-rata 5 Pembacaan

Program dimodifikasi dengan melakukan lima kali pembacaan sensor terlebih dahulu. Hasil pembacaan kemudian dijumlahkan dan dihitung nilai rata-ratanya sebelum ditampilkan pada Serial Monitor.

File program:

`modul1_rata_rata_5_pembacaan.ino`

## Percobaan 2A - Kendali Aktuator Berdasarkan Data Sensor

Percobaan ini menggunakan data suhu dari DHT22 untuk mengendalikan relay sebagai aktuator.

### Konfigurasi

* DHT22 DATA → GPIO 4
* Relay IN → GPIO 26
* Relay VCC → VIN/5V
* Relay GND → GND

Threshold suhu yang digunakan adalah 30°C. Aktuator dikendalikan berdasarkan hasil pembacaan suhu.

### Hasil

```text
Suhu: 24.80 °C -> Aktuator: OFF
Suhu: 25.30 °C -> Aktuator: OFF
Suhu: 28.90 °C -> Aktuator: OFF
Suhu: 30.20 °C -> Aktuator: OFF
Suhu: 31.50 °C -> Aktuator: ON
Suhu: 32.80 °C -> Aktuator: ON
Suhu: 33.80 °C -> Aktuator: ON
Suhu: 34.70 °C -> Aktuator: ON
Suhu: 35.60 °C -> Aktuator: ON
```

Pada pengujian, aktuator mulai menunjukkan kondisi ON pada pembacaan suhu 31.50°C hingga 35.60°C.

## Modifikasi 2A - Hysteresis

Program dimodifikasi menggunakan dua batas suhu untuk mengendalikan aktuator.

* Suhu > 30°C → Aktuator ON
* Suhu < 28°C → Aktuator OFF
* Suhu 28°C–30°C → Kondisi aktuator dipertahankan

Hysteresis digunakan agar perubahan kondisi aktuator tidak terlalu sering ketika suhu berada di sekitar batas threshold.

File program:

`modul1_histeresis.ino`

## Kendala

Selama praktikum sempat terdapat beberapa kendala pada proses pengujian. Dilakukan pengecekan kembali pada program, rangkaian, dan koneksi komponen sebelum melanjutkan pengujian.

## Kesimpulan

Pada Modul 1, ESP32 digunakan untuk membaca suhu dan kelembaban menggunakan sensor DHT22 serta mengendalikan aktuator berdasarkan data suhu. Modifikasi dilakukan dengan menghitung rata-rata lima pembacaan sensor dan menerapkan hysteresis pada kendali aktuator.

````

