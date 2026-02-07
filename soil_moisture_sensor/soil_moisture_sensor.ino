#define SOIL_AO_PIN 34    // ESP32 pin connected to the soil moisture sensor's analog output (AO)

void setup() {
  Serial.begin(9600);     // Start serial communication at 9600 baud rate

  delay(500);             // Small delay to allow serial communication to stabilize
  Serial.println("Soil Moisture Sensor Test Started");
}

void loop() {
  // Read the raw analog value from the soil moisture sensor
  // ESP32 ADC range = 0 to 4095
  int soilRaw = analogRead(SOIL_AO_PIN);

  // Print the raw analog value to the Serial Monitor
  Serial.print("Soil Moisture Raw Value: ");
  Serial.println(soilRaw);

  // Wait for 2 seconds before the next reading
  delay(2000);
}
