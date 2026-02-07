#include <DHT.h>  // Include the DHT sensor library

// ------- Pin & Type Configuration -------
#define DHT_DATA_PIN   26   // The ESP32 pin where the DHT11 DATA pin is connected
#define DHTTYPE        DHT11 // Define the type of DHT sensor being used (DHT11)

// Create a DHT sensor object using the pin and sensor type
DHT dht(DHT_DATA_PIN, DHTTYPE);

void setup() {
  Serial.begin(9600);   // Start serial communication at 9600 baud rate

  delay(1000);          // Small delay to allow sensor and serial to stabilize
  dht.begin();          // Initialize the DHT11 sensor

  Serial.println("DHT11 Test Started"); // Print a message to indicate setup is done
}

void loop() {
  // Read humidity and temperature values from DHT11 sensor.
  // These functions return NAN if the reading fails.
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // Default is Celsius

  // Check if either reading failed
  if (isnan(h) || isnan(t)) {
    Serial.println("DHT11 Read Error"); // Message if the sensor failed to read
  } else {
    // Print the temperature and humidity values
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" °C | Humidity: ");
    Serial.print(h);
    Serial.println(" %");
  }

  delay(2000); // Wait 2 seconds before the next reading
}
