#include <ESP8266WiFi.h>
#include "secrets.h"

const char* ssid = WIFI_SSID;       // WiFi yang dituju (mode STA)
const char* password = WIFI_PASSWORD;

const char* ap_ssid = "APLAFF";     // jaringan yang dibuat ESP8266 (mode AP)
const char* ap_password = AP_PASSWORD; // minimal 8 karakter

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_AP_STA);              // aktifkan mode AP+STA
  WiFi.softAP(ap_ssid, ap_password);   // jalankan Access Point
  WiFi.begin(ssid, password);          // hubungkan ke WiFi (STA)

  Serial.print("Menghubungkan ke WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Mode AP+STA aktif!");

  Serial.print("IP Address STA : ");
  Serial.println(WiFi.localIP());

  Serial.print("IP Address AP : ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  Serial.print("Status STA: ");
  Serial.println(
    WiFi.status() == WL_CONNECTED ? "Terhubung" : "Terputus"
  );

  Serial.print("Jumlah perangkat terhubung ke AP: ");
  Serial.println(WiFi.softAPgetStationNum());

  delay(5000);
}


### 5\. File Modul 2/code/secrets.h

Karena kode menggunakan #include "secrets.h", kamu perlu membuat satu file tambahan bernama secrets.h di dalam folder Modul 2/code/.

File ini hanya untuk komputer kamu dan jangan di-push ke GitHub. Isi dengan SSID dan password WiFi yang kamu gunakan saat praktikum.

cpp

#ifndef SECRETS_H
#define SECRETS_H

#define WIFI_SSID "ISI_SSID_WIFI"
#define WIFI_PASSWORD "ISI_PASSWORD_WIFI"

#define AP_PASSWORD "ISI_PASSWORD_ACCESS_POINT"

#endif