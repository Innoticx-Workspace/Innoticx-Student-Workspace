#include <DHT.h>  // Include the DHT library needed for temperature & humidity sensor

// ---------- PIN DEFINITIONS ----------

// DHT11 Sensor Pins
#define DHT_DATA_PIN   26     // Data pin connected to DHT11
#define DHTTYPE        DHT11  // Define the sensor type (DHT11)

// Soil Moisture Sensor Pin
#define SOIL_AO_PIN    34     // Analog output pin of soil moisture sensor

// MQ2 Gas Sensor Pin
#define MQ2_AO_PIN     35     // Analog output pin of MQ2 gas sensor

// Create the DHT object using pin 26 and sensor type DHT11
DHT dht(DHT_DATA_PIN, DHTTYPE);

void setup() {
  Serial.begin(9600);     // Start serial communication at 9600 baud rate
  delay(500);            // Small delay for Serial Monitor to initialize

  dht.begin();            // Initialize the DHT11 sensor

  // Print startup message
  Serial.println("ESP32 Sensor Interface Started");
  Serial.println("DHT11 | Soil Moisture | MQ2 Active");
  Serial.println("MQ2 warm-up: wait 2–3 minutes for stable readings");
}

void loop() {

  // -------- READ DHT11 SENSOR --------
  float humidity = dht.readHumidity();         // Read humidity (%)
  float temperature = dht.readTemperature();   // Read temperature (Celsius)

  // -------- READ SOIL MOISTURE SENSOR --------
  int soilRaw = analogRead(SOIL_AO_PIN);  // Read raw analog value (0–4095)

  // Convert the raw soil moisture reading to a percentage
  // These numbers (3500 = dry, 1200 = wet) must be calibrated for YOUR sensor
  int soilPercent = map(soilRaw, 3500, 1200, 0, 100);
  soilPercent = constrain(soilPercent, 0, 100); // Force value within 0–100%

  // -------- READ MQ2 GAS SENSOR --------
  int mq2Raw = analogRead(MQ2_AO_PIN);   // Read raw gas sensor value (0–4095)

  // -------- PRINT SENSOR READINGS TO SERIAL --------
  Serial.println("--------------------------------");

  // Print DHT11 values
  if (isnan(humidity) || isnan(temperature)) {  // Check if reading failed
    Serial.println("DHT11 Read Error — Check wiring");
  } else {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C | Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  // Print soil moisture values
  Serial.print("Soil Moisture Raw: ");
  Serial.print(soilRaw);
  Serial.print(" | Moisture: ");
  Serial.print(soilPercent);
  Serial.println(" %");

  // Print MQ2 gas sensor value
  Serial.print("MQ2 Gas Raw Value: ");
  Serial.println(mq2Raw);

  delay(2000); // DHT11 requires at least 2 seconds between readings
}
