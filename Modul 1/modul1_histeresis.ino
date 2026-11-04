#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22
#define RELAYPIN 26

DHT dht(DHTPIN, DHTTYPE);

// Batas suhu untuk menyalakan dan mematikan aktuator
const float suhuNyala = 30.0;
const float suhuMati = 28.0;

bool aktuatorAktif = false;

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
    delay(2000);
    return;
  }

  // Aktuator menyala jika suhu lebih dari 30°C
  if (!aktuatorAktif && suhu > suhuNyala) {
    aktuatorAktif = true;
  }

  // Aktuator mati jika suhu kurang dari 28°C
  if (aktuatorAktif && suhu < suhuMati) {
    aktuatorAktif = false;
  }

  // Mengatur kondisi relay
  digitalWrite(RELAYPIN, aktuatorAktif ? HIGH : LOW);

  // Menampilkan hasil pada Serial Monitor
  Serial.print("Suhu: ");
  Serial.print(suhu);
  Serial.print(" °C -> Aktuator: ");

  if (aktuatorAktif) {
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }

  delay(2000);
}