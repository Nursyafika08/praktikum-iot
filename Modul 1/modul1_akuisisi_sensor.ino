#include <DHT.h>

#define DHTPIN 4       // Pin data DHT22 terhubung ke GPIO 4
#define DHTTYPE DHT22  // Tipe sensor yang digunakan

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin(); // Inisialisasi sensor DHT22

  Serial.println("Memulai akuisisi data sensor DHT22...");
}

void loop() {
  // Membaca data kelembaban dan suhu
  float kelembaban = dht.readHumidity();
  float suhu = dht.readTemperature();

  // Memeriksa apakah pembacaan berhasil
  if (isnan(kelembaban) || isnan(suhu)) {
    Serial.println("Gagal membaca data dari sensor DHT22!");
  } else {
    Serial.print("Suhu: ");
    Serial.print(suhu);
    Serial.print(" °C, Kelembaban: ");
    Serial.print(kelembaban);
    Serial.println(" %");
  }

  // Jeda pembacaan setiap 2 detik
  delay(2000);
}