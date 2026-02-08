// DHT11 DATA → GPIO26
// DHT11 VCC  → GPIO14 (OUTPUT HIGH ≈ 3.3V)
// DHT11 GND  → GND




#include <DHT.h>

#define DHT_DATA_PIN   26
#define DHT_POWER_PIN  14
#define DHTTYPE        DHT11

DHT dht(DHT_DATA_PIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  pinMode(DHT_POWER_PIN, OUTPUT);
  digitalWrite(DHT_POWER_PIN, HIGH);  // Power DHT11

  delay(1000);
  dht.begin();

  Serial.println("DHT11 Test Started");
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("DHT11 Read Error");
  } else {
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" °C | Humidity: ");
    Serial.print(h);
    Serial.println(" %");
  }

  delay(2000);
}