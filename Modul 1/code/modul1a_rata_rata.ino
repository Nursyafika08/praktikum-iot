#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11
#define JUMLAH_SAMPEL 5

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  float totalSuhu = 0;
  float totalKelembaban = 0;
  int dataValid = 0;

  for (int i = 0; i < JUMLAH_SAMPEL; i++) {
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (!isnan(h) && !isnan(t)) {
      totalSuhu += t;
      totalKelembaban += h;
      dataValid++;
    }

    delay(2000);
  }

  if (dataValid > 0) {
    Serial.print("Rata-rata Suhu: ");
    Serial.print(totalSuhu / dataValid);
    Serial.print(" °C, Rata-rata Kelembaban: ");
    Serial.print(totalKelembaban / dataValid);
    Serial.println(" %");
  } else {
    Serial.println("Gagal membaca data dari sensor DHT11!");
  }
}

