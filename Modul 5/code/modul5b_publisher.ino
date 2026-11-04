#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <math.h>
#include "secrets.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;

// Topic MQTT
const char* topicPerintah = "KelompokDediPyka/perintah";
const char* topicData = "KelompokDediPyka/data";

const int ledPin = 4; // GPIO4 (D2 pada NodeMCU)

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastSend = 0;

// Mock function pengganti sensor DHT22
float bacaSuhuMock() {
  static unsigned long jumlahBaca = 0;
  jumlahBaca++;

  // Suhu dasar berubah secara bertahap
  float suhuDasar = 28.0 + 2.0 * sin(jumlahBaca * 0.08);

  // Noise kecil untuk mensimulasikan fluktuasi sensor
  float noise = random(-5, 6) * 0.1;

  float suhu = suhuDasar + noise;

  // Lonjakan suhu setiap 25 pembacaan
  if (jumlahBaca % 25 == 0) {
    suhu += 8.0;
  }

  return suhu;
}

// Fungsi callback untuk menerima perintah LED
void callback(char* topic, byte* payload, unsigned int length) {
  String pesan;

  for (unsigned int i = 0; i < length; i++) {
    pesan += (char)payload[i];
  }

  Serial.print("Pesan diterima [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(pesan);

  // Deserialisasi data JSON
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, pesan);

  if (error) {
    Serial.print("Gagal parsing JSON: ");
    Serial.println(error.c_str());
    return;
  }

  const char* perintah = doc["perintah"];

  if (perintah != NULL) {
    if (String(perintah) == "ON") {
      digitalWrite(ledPin, HIGH);
      Serial.println("Aktuator: ON");
    } else if (String(perintah) == "OFF") {
      digitalWrite(ledPin, LOW);
      Serial.println("Aktuator: OFF");
    }
  }
}

void hubungkanWiFi() {
  WiFi.begin(ssid, password);

  Serial.print("Menghubungkan ke WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi berhasil terhubung!");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void hubungkanMQTT() {
  while (!client.connected()) {
    Serial.print("Menghubungkan ke broker MQTT...");

    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("berhasil terhubung!");

      client.subscribe(topicPerintah);

      Serial.print("Subscribe ke topic: ");
      Serial.println(topicPerintah);
    } else {
      Serial.print("gagal, rc=");
      Serial.print(client.state());
      Serial.println(" coba lagi dalam 2 detik");

      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  randomSeed(analogRead(A0));

  hubungkanWiFi();

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    hubungkanMQTT();
  }

  // Memproses pesan MQTT yang masuk
  client.loop();

  // Mengirim data suhu setiap 2 detik
  unsigned long now = millis();

  if (now - lastSend > 2000) {
    lastSend = now;

    float suhu = bacaSuhuMock();

    // Membuat payload JSON
    JsonDocument doc;
    doc["suhu"] = suhu;

    char buffer[128];
    serializeJson(doc, buffer);

    // Publish data ke topic
    client.publish(topicData, buffer);

    Serial.print("Publish data suhu: ");
    Serial.println(buffer);
  }
}

