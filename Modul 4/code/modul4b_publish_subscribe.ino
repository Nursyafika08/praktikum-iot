#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <DHT.h>
#include "secrets.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;

const char* topicData = "KelompokDediPyka/data";
const char* topicPerintah = "KelompokDediPyka/perintah";

#define DHTPIN 5
#define DHTTYPE DHT11

const int ledPin = 4;

DHT dht(DHTPIN, DHTTYPE);

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long waktuTerakhirPublish = 0;
const long intervalPublish = 5000;

// Menerima perintah LED dari broker
void callback(char* topic, byte* payload, unsigned int length) {
  String pesan;

  for (unsigned int i = 0; i < length; i++) {
    pesan += (char)payload[i];
  }

  JsonDocument doc;

  if (deserializeJson(doc, pesan)) {
    Serial.println("Gagal parsing JSON");
    return;
  }

  const char* perintah = doc["perintah"];

  digitalWrite(ledPin, String(perintah) == "ON" ? HIGH : LOW);

  Serial.print("Perintah diterima -> Aktuator: ");
  Serial.println(perintah);
}

void hubungkanWiFi() {
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  Serial.println("WiFi berhasil terhubung!");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void hubungkanMQTT() {
  while (!client.connected()) {
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      client.subscribe(topicPerintah);
      Serial.println("Terhubung dan subscribe topic perintah");
    } else {
      Serial.print("Koneksi MQTT gagal, rc=");
      Serial.println(client.state());

      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  dht.begin();

  hubungkanWiFi();

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    hubungkanMQTT();
  }

  // Memproses pesan masuk secara terus-menerus
  client.loop();

  // Publish data sensor setiap 5 detik tanpa delay panjang
  if (millis() - waktuTerakhirPublish >= intervalPublish) {
    waktuTerakhirPublish = millis();

    float suhu = dht.readTemperature();

    if (!isnan(suhu)) {
      JsonDocument doc;
      doc["suhu"] = suhu;

      char buffer[128];
      serializeJson(doc, buffer);

      client.publish(topicData, buffer);

      Serial.print("Data terkirim: ");
      Serial.println(buffer);
    } else {
      Serial.println("Gagal membaca sensor DHT11");
    }
  }
}