/*
 * Solar-Powered Smart Home Automation System
 *
 * Developed by:
 * - Meha Goswami
 *
 * Features:
 * - MQTT-based room control
 * - Automatic lighting using PIR + LDR
 * - Temperature and humidity monitoring
 * - Gas detection
 * - Motion detection
 * - Emergency alarm system
 * - Solar-powered operation
 */

#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT11.h"

// WiFi Credentials
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// MQTT Broker
const char* mqtt_server = "test.mosquitto.org";

// Pin Definitions
#define DHTPIN 15
#define MQ_PIN 34
#define LDR_PIN 4
#define PIR_PIN 27
#define BUZZER 25

#define ROOM1 18
#define ROOM2 19
#define ROOM3 23

// MQTT Topics
#define TEMP_TOPIC "esp32/temp"
#define HUM_TOPIC "esp32/hum"
#define GAS_TOPIC "esp32/gas"
#define MOTION_TOPIC "esp32/motion"
#define LIGHT_TOPIC "esp32/light"

#define ROOM1_TOPIC "esp32/room1"
#define ROOM2_TOPIC "esp32/room2"
#define ROOM3_TOPIC "esp32/room3"

#define EMERGENCY_TOPIC "esp32/emergency"

// Objects
WiFiClient espClient;
PubSubClient client(espClient);
DHT11 dht(DHTPIN);

// Room Control Overrides
int room1_override = -1;
int room2_override = -1;
int room3_override = -1;

// Emergency State
bool emergency = false;

// Connect to WiFi
void setup_wifi() {

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

// MQTT Callback Function
void callback(char* topic, byte* payload, unsigned int length) {

  String msg = "";

  for (int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }

  if (String(topic) == ROOM1_TOPIC) {
    if (msg == "ON")
      room1_override = 1;
    else if (msg == "OFF")
      room1_override = 0;
    else if (msg == "AUTO")
      room1_override = -1;
  }

  if (String(topic) == ROOM2_TOPIC) {
    if (msg == "ON")
      room2_override = 1;
    else if (msg == "OFF")
      room2_override = 0;
    else if (msg == "AUTO")
      room2_override = -1;
  }

  if (String(topic) == ROOM3_TOPIC) {
    if (msg == "ON")
      room3_override = 1;
    else if (msg == "OFF")
      room3_override = 0;
    else if (msg == "AUTO")
      room3_override = -1;
  }

  if (String(topic) == EMERGENCY_TOPIC) {
    if (msg == "ON")
      emergency = true;
    else
      emergency = false;
  }
}

// Reconnect to MQTT Broker
void reconnect() {

  while (!client.connected()) {

    String clientId = "ESP32-" + String(random(1000, 9999));

    if (client.connect(clientId.c_str())) {

      client.subscribe(ROOM1_TOPIC);
      client.subscribe(ROOM2_TOPIC);
      client.subscribe(ROOM3_TOPIC);
      client.subscribe(EMERGENCY_TOPIC);

    } else {

      delay(2000);
    }
  }
}

void setup() {

  Serial.begin(115200);

  pinMode(LDR_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);

  pinMode(ROOM1, OUTPUT);
  pinMode(ROOM2, OUTPUT);
  pinMode(ROOM3, OUTPUT);

  pinMode(BUZZER, OUTPUT);

  digitalWrite(BUZZER, LOW);

  setup_wifi();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected())
    reconnect();

  client.loop();

  // Read Sensors
  int ldr = digitalRead(LDR_PIN);
  int motion = digitalRead(PIR_PIN);

  // Automatic Lighting Logic
  // LDR LOW = Dark
  // PIR HIGH = Motion Detected
  bool autoLight = (ldr == LOW && motion == HIGH);

  // Room 1 Control
  if (room1_override == 1)
    digitalWrite(ROOM1, HIGH);
  else if (room1_override == 0)
    digitalWrite(ROOM1, LOW);
  else
    digitalWrite(ROOM1, autoLight);

  // Room 2 Control
  if (room2_override == 1)
    digitalWrite(ROOM2, HIGH);
  else if (room2_override == 0)
    digitalWrite(ROOM2, LOW);
  else
    digitalWrite(ROOM2, autoLight);

  // Room 3 Control
  if (room3_override == 1)
    digitalWrite(ROOM3, HIGH);
  else if (room3_override == 0)
    digitalWrite(ROOM3, LOW);
  else
    digitalWrite(ROOM3, autoLight);

  // Emergency Alarm
  if (emergency)
    digitalWrite(BUZZER, HIGH);
  else
    digitalWrite(BUZZER, LOW);

  // Temperature & Humidity
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    temp = 0;
    hum = 0;
  }

  // Gas Sensor Reading
  int gasValue = analogRead(MQ_PIN);

  // Publish Sensor Data
  client.publish(TEMP_TOPIC, String(temp).c_str());
  client.publish(HUM_TOPIC, String(hum).c_str());
  client.publish(GAS_TOPIC, String(gasValue).c_str());

  if (motion == HIGH)
    client.publish(MOTION_TOPIC, "Motion Detected");
  else
    client.publish(MOTION_TOPIC, "No Motion");

  client.publish(LIGHT_TOPIC, autoLight ? "ON" : "OFF");

  delay(2000);
}
