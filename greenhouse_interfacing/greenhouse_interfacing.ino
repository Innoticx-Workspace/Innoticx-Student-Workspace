#include <DHT.h>

// ---------- PIN DEFINITIONS ----------
// DHT11
#define DHT_DATA_PIN   26
#define DHT_POWER_PIN  14
#define DHTTYPE        DHT11

// Soil Moisture
#define SOIL_POWER_PIN 32
#define SOIL_AO_PIN    34

// MQ2
#define MQ2_AO_PIN     35

DHT dht(DHT_DATA_PIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  delay(1000);

  // ---- Power pins ----
  pinMode(DHT_POWER_PIN, OUTPUT);
  digitalWrite(DHT_POWER_PIN, HIGH);   // ~3.3V to DHT11

  pinMode(SOIL_POWER_PIN, OUTPUT);
  digitalWrite(SOIL_POWER_PIN, HIGH);  // ~3.3V to Soil sensor

  delay(1000); // sensor stabilization

  dht.begin();

  Serial.println("ESP32 Sensor Interface Started");
  Serial.println("DHT11 | Soil Moisture | MQ2");
  Serial.println("MQ2 warm-up: wait 2–3 minutes");
}

void loop() {
  // -------- DHT11 --------
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // Celsius

  // -------- Soil Moisture --------
  int soilRaw = analogRead(SOIL_AO_PIN);
  // Adjust these after calibration
  int soilPercent = map(soilRaw, 3500, 1200, 0, 100);
  soilPercent = constrain(soilPercent, 0, 100);

  // -------- MQ2 --------
  int mq2Raw = analogRead(MQ2_AO_PIN);

  // -------- Serial Output --------
  Serial.println("--------------------------------");

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("DHT11 Read Error");
  } else {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C | Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  Serial.print("Soil Moisture Raw: ");
  Serial.print(soilRaw);
  Serial.print(" | Moisture: ");
  Serial.print(soilPercent);
  Serial.println(" %");

  Serial.print("MQ2 Gas Raw Value: ");
  Serial.println(mq2Raw);

  delay(2000); // DHT11 minimum delay
}