// MQ2 AO  → GPIO35
// MQ2 VCC → VIN (5V)
// MQ2 GND → GND


#define MQ2_AO_PIN 35

void setup() {
  Serial.begin(9600);
  delay(1000);

  Serial.println("MQ2 Gas Sensor Test Started");
  Serial.println("Warming up MQ2... wait 2–3 minutes");
}

void loop() {
  int mq2Raw = analogRead(MQ2_AO_PIN);

  Serial.print("MQ2 Gas Raw Value: ");
  Serial.println(mq2Raw);

  delay(2000);
}