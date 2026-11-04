#include <Arduino.h>
#include <math.h>

const int N = 5;

float buffer[N];
int indeks = 0;
int jumlah = 0;

float suhuMin = 1000.0;
float suhuMax = -1000.0;

// Mock function pengganti sensor DHT22
float bacaSuhuMock() {
  static unsigned long jumlahBaca = 0;
  jumlahBaca++;

  float suhuDasar = 28.0 + 2.0 * sin(jumlahBaca * 0.08);
  float noise = random(-5, 6) * 0.1;

  float suhu = suhuDasar + noise;

  if (jumlahBaca % 25 == 0) {
    suhu += 8.0;
  }

  return suhu;
}

// Menghitung moving average
float hitungMovingAverage(float nilaiBaru) {
  buffer[indeks] = nilaiBaru;

  indeks = (indeks + 1) % N;

  if (jumlah < N) {
    jumlah++;
  }

  float total = 0;

  for (int i = 0; i < jumlah; i++) {
    total += buffer[i];
  }

  return total / jumlah;
}

// Menghitung simpangan baku
float hitungStdDev(float rataRata) {
  if (jumlah < 2) {
    return 0.0;
  }

  float jumlahKuadrat = 0;

  for (int i = 0; i < jumlah; i++) {
    float selisih = buffer[i] - rataRata;
    jumlahKuadrat += selisih * selisih;
  }

  return sqrt(jumlahKuadrat / (jumlah - 1));
}

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(A0));

  Serial.println("Moving Average dan Statistik");
}

void loop() {
  float suhu = bacaSuhuMock();

  if (isnan(suhu)) {
    Serial.println("Pembacaan gagal, data diabaikan");
  } else {
    float suhuFilter = hitungMovingAverage(suhu);

    float stdDev = hitungStdDev(suhuFilter);

    if (suhu < suhuMin) {
      suhuMin = suhu;
    }

    if (suhu > suhuMax) {
      suhuMax = suhu;
    }

    Serial.print("Mentah: ");
    Serial.print(suhu);

    Serial.print(" | Filter: ");
    Serial.print(suhuFilter);

    Serial.print(" | Min: ");
    Serial.print(suhuMin);

    Serial.print(" | Max: ");
    Serial.print(suhuMax);

    Serial.print(" | StdDev: ");
    Serial.println(stdDev);
  }

  delay(2000);
}
