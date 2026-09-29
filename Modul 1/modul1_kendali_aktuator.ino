#include <DHT.h>

#define DHTPIN 4       // Pin data DHT22
#define DHTTYPE DHT22
#define RELAYPIN 26    // Pin kendali relay/LED

DHT dht(DHTPIN, DHTTYPE);

const float suhuThreshold = 30.0; // Ambang batas suhu

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(RELAYPIN, OUTPUT);
  digitalWrite(RELAYPIN, LOW); // Aktuator mati saat awal
}

void loop() {
  float suhu = dht.readTemperature();

  if (isnan(suhu)) {
    Serial.println("Gagal membaca data sensor!");
  } else {
    Serial.print("Suhu: ");
    Serial.print(suhu);
    Serial.print(" °C -> ");

    // Kendali aktuator berdasarkan threshold
    if (suhu > suhuThreshold) {
      digitalWrite(RELAYPIN, HIGH);
      Serial.println("Aktuator: ON");
    } else {
      digitalWrite(RELAYPIN, LOW);
      Serial.println("Aktuator: OFF");
    }
  }

  delay(2000);
}