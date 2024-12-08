#include <ESP8266WiFi.h>
#include <PubSubClient.h>  // For MQTT communication
#include <DHT.h>

// WiFi credentials
const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";

// MQTT broker details
const char* mqtt_server = "broker.hivemq.com";  // Public MQTT broker
const char* topic = "smart_irrigation/status";

// Pin Definitions
#define SOIL_MOISTURE_PIN A0
#define DHT_PIN D4
#define RELAY_PIN D5

// DHT Sensor Configuration
#define DHTTYPE DHT11
DHT dht(DHT_PIN, DHTTYPE);

// WiFi and MQTT clients
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  
  // Initialize components
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);  // Relay off initially
  dht.begin();

  // Connect to WiFi
  connectToWiFi();
  
  // Configure MQTT
  client.setServer(mqtt_server, 1883);
  connectToMQTT();
}

void loop() {
  if (!client.connected()) {
    connectToMQTT();
  }
  client.loop();

  // Read sensor data
  int soilMoisture = analogRead(SOIL_MOISTURE_PIN);
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check soil moisture level
  if (soilMoisture > 700) {  // Adjust threshold based on your soil moisture sensor
    digitalWrite(RELAY_PIN, LOW);  // Turn on the pump
    client.publish(topic, "Pump ON: Soil moisture low");
  } else {
    digitalWrite(RELAY_PIN, HIGH);  // Turn off the pump
    client.publish(topic, "Pump OFF: Soil moisture adequate");
  }

  // Send sensor data via MQTT
  char payload[100];
  snprintf(payload, 100, "Temp: %.2f°C, Humidity: %.2f%%, Soil Moisture: %d", temp, humidity, soilMoisture);
  client.publish(topic, payload);

  // Wait for a minute before sending the next update
  delay(60000);
}

void connectToWiFi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
}

void connectToMQTT() {
  Serial.print("Connecting to MQTT...");
  while (!client.connected()) {
    if (client.connect("NodeMCUClient")) {
      Serial.println("\nMQTT connected");
    } else {
      Serial.print(".");
      delay(1000);
    }
  }
}
