#include <ESP8266WiFi.h>
#include "secrets.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

const int ledPin = D2;

void hubungkanWiFi() {
  Serial.print("Menghubungkan ke WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi berhasil terhubung!");

  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());

  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());

  Serial.print("RSSI (dBm) : ");
  Serial.println(WiFi.RSSI());

  digitalWrite(ledPin, HIGH); // LED menyala saat terhubung
}

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  WiFi.mode(WIFI_STA);

  hubungkanWiFi();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Status: Terhubung");
  } else {
    Serial.println("Status: Terputus");
    digitalWrite(ledPin, LOW);

    Serial.println("Mencoba menghubungkan ulang...");

    WiFi.disconnect();          // putuskan sisa koneksi lama
    hubungkanWiFi();            // ulangi proses koneksi
  }

  delay(5000);
}
