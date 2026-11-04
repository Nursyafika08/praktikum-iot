#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11
#define RELAYPIN 5 // pin kendali relay/LED indikator (GPIO 5 / D1)

DHT dht(DHTPIN, DHTTYPE);

const float batasAtas = 30.0;  // aktuator ON jika suhu di atas nilai ini
const float batasBawah = 28.0; // aktuator OFF jika suhu di bawah nilai ini
bool aktuatorOn = false;       // menyimpan status aktuator saat ini

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(RELAYPIN, OUTPUT);
  digitalWrite(RELAYPIN, LOW);
}

void loop() {
  float suhu = dht.readTemperature();

  if (isnan(suhu)) {
    Serial.println("Gagal membaca data sensor!");
  } else {
    if (suhu > batasAtas) {
      aktuatorOn = true; // suhu melewati batas atas
    } else if (suhu < batasBawah) {
      aktuatorOn = false; // suhu turun di bawah batas bawah
    } // di antara 28-30°C status tidak berubah

    digitalWrite(RELAYPIN, aktuatorOn ? HIGH : LOW);

    Serial.print("Suhu: ");
    Serial.print(suhu);
    Serial.print(" °C -> Aktuator: ");
    Serial.println(aktuatorOn ? "ON" : "OFF");
  }

  delay(2000);
}