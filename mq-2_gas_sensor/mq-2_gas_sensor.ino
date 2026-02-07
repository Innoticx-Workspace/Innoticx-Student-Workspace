#define MQ2_AO_PIN 35   // Define the ESP32 pin where MQ2 analog output (AO) is connected

void setup() {
  Serial.begin(9600);   // Start serial communication at 9600 baud rate
  delay(1000);          // Small delay to allow Serial to initialize properly

  // Initial message to the user
  Serial.println("MQ2 Gas Sensor Test Started");
  Serial.println("Warming up MQ2... wait 2–3 minutes"); 
  // MQ2 requires a warm-up time for the heating element to stabilize
}

void loop() {
  // Read raw analog value from MQ2 AO pin (0–4095 on ESP32)
  int mq2Raw = analogRead(MQ2_AO_PIN);

  // Print the raw sensor value
  // Higher value = less gas, lower value = more gas (depends on load resistor)
  Serial.print("MQ2 Gas Raw Value: ");
  Serial.println(mq2Raw);

  delay(2000);  // Wait 2 seconds before taking the next reading
}
