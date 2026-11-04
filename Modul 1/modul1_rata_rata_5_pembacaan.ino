#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  Serial.println("Pembacaan rata-rata 5 kali sensor DHT22...");
}

void loop() {
  float totalSuhu = 0;
  float totalKelembaban = 0;
  int jumlahPembacaan = 0;

  // Melakukan 5 kali pembacaan
  for (int i = 0; i < 5; i++) {
    float kelembaban = dht.readHumidity();
    float suhu = dht.readTemperature();

    if (isnan(kelembaban) || isnan(suhu)) {
      Serial.println("Gagal membaca data sensor!");
    } else {
      totalSuhu += suhu;
      totalKelembaban += kelembaban;
      jumlahPembacaan++;
    }

    delay(2000);
  }

  // Menghitung dan menampilkan rata-rata
  if (jumlahPembacaan > 0) {
    float rataSuhu = totalSuhu / jumlahPembacaan;
    float rataKelembaban = totalKelembaban / jumlahPembacaan;

    Serial.print("Rata-rata Suhu: ");
    Serial.print(rataSuhu);
    Serial.print(" °C, Rata-rata Kelembaban: ");
    Serial.print(rataKelembaban);
    Serial.println(" %");
  } else {
    Serial.println("Tidak ada data sensor yang valid.");
  }

  delay(2000);
}