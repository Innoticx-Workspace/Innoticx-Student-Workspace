// Soil AO  → GPIO34
// Soil VCC → GPIO32 (OUTPUT HIGH ≈ 3.3V)
// Soil GND → GND


#define SOIL_POWER_PIN 32
#define SOIL_AO_PIN    34

void setup() {
  Serial.begin(9600);

  pinMode(SOIL_POWER_PIN, OUTPUT);
  digitalWrite(SOIL_POWER_PIN, HIGH); // Power soil sensor

  delay(500);
  Serial.println("Soil Moisture Sensor Test Started");
}

void loop() {
  int soilRaw = analogRead(SOIL_AO_PIN);

  Serial.print("Soil Moisture Raw Value: ");
  Serial.println(soilRaw);

  delay(2000);
}