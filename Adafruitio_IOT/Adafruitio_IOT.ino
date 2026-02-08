#include <WiFi.h>
#include <DHT.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// -------- WiFi --------
#define WIFI_SSID "YOUR SSID"
#define WIFI_PASS "YOUR PASSWORD"

// -------- Adafruit IO --------
#define AIO_SERVER     "io.adafruit.com"
#define AIO_PORT       1883
#define AIO_USERNAME   "YOUR USERNAME"
#define AIO_KEY        "YOUR API KEY"

// -------- Pins --------
#define DHT_DATA_PIN   26
#define DHT_POWER_PIN  14
#define DHTTYPE        DHT11

#define SOIL_POWER_PIN 32
#define SOIL_AO_PIN    34

#define MQ2_AO_PIN     35

// -------- Objects --------
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_PORT,
                          AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Publish feedTemp =
  Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperature");

Adafruit_MQTT_Publish feedHum =
  Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidity");

Adafruit_MQTT_Publish feedSoil =
  Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/soil");

Adafruit_MQTT_Publish feedGas =
  Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/gas");

DHT dht(DHT_DATA_PIN, DHTTYPE);

// -------- MQTT CONNECT --------
void mqtt_connect() {
  while (!mqtt.connected()) {
    if (mqtt.connect() == 0) {
      Serial.println("MQTT Connected");
    } else {
      Serial.println("MQTT Retry...");
      delay(3000);
    }
  }
}

// -------- SETUP --------
void setup() {
  Serial.begin(9600);

  pinMode(DHT_POWER_PIN, OUTPUT);
  digitalWrite(DHT_POWER_PIN, HIGH);

  pinMode(SOIL_POWER_PIN, OUTPUT);
  digitalWrite(SOIL_POWER_PIN, HIGH);

  dht.begin();

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected");

  mqtt_connect();
}

// -------- LOOP --------
void loop() {
  mqtt_connect();

  float temperature = dht.readTemperature();
  float humidity    = dht.readHumidity();

  int soilRaw = analogRead(SOIL_AO_PIN);
  float soilPercent = map(soilRaw, 3500, 1200, 0, 100);
  soilPercent = constrain(soilPercent, 0, 100);

  int mq2Raw = analogRead(MQ2_AO_PIN);

  // ---- Serial ----
  Serial.println("--------------------");
  Serial.print("Temp: "); Serial.println(temperature);
  Serial.print("Humidity: "); Serial.println(humidity);
  Serial.print("Soil: "); Serial.println(soilPercent);
  Serial.print("Gas: "); Serial.println(mq2Raw);

  // ---- Publish (EXPLICIT TYPE) ----
  feedTemp.publish(temperature);
  feedHum.publish(humidity);
  feedSoil.publish((float)soilPercent);
  feedGas.publish((float)mq2Raw);

  delay(10000);   // rate-limit safe
}