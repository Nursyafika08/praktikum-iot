#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "secrets.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;

const char* topicPerintah = "KelompokDediPyka/perintah";
const char* topicBuzzer = "KelompokDediPyka/buzzer";

const int ledPin = 4;     // GPIO4 (D2)
const int buzzerPin = D5; // GPIO14 (D5)

WiFiClient espClient;
PubSubClient client(espClient);

// Callback membedakan perintah berdasarkan topic
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
  bool nyala = (String(perintah) == "ON");

  if (strcmp(topic, topicPerintah) == 0) {
    digitalWrite(ledPin, nyala ? HIGH : LOW);

    Serial.print("LED -> ");

  } else if (strcmp(topic, topicBuzzer) == 0) {
    digitalWrite(buzzerPin, nyala ? HIGH : LOW);

    Serial.print("Buzzer -> ");
  }

  Serial.println(perintah);
}

void hubungkanWiFi() {
  WiFi.begin(ssid, password);

  Serial.print("Menghubungkan ke WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi berhasil terhubung!");
}

void hubungkanMQTT() {
  while (!client.connected()) {
    Serial.print("Menghubungkan ke broker MQTT...");

    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("berhasil terhubung!");

      // Subscribe ke topic LED dan buzzer
      client.subscribe(topicPerintah);
      client.subscribe(topicBuzzer);

      Serial.println("Subscribe topic LED dan buzzer berhasil");
    } else {
      Serial.print("Koneksi gagal, rc=");
      Serial.println(client.state());

      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, LOW);

  hubungkanWiFi();

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    hubungkanMQTT();
  }

  client.loop();
}