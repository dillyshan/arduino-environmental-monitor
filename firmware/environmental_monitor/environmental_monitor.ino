/*
 * Project: Smart Environmental Monitoring System
 * Board: Arduino Uno R3
 *
 * Features:
 * - Monitor temperature and humidity using DHT11
 * - Activate warning LED at 26 C or higher
 * - Display readings and system status in Serial Monitor
 *
 * Connections:
 * DHT11 Signal -> Arduino D2
 * DHT11 VCC    -> Arduino 5V
 * DHT11 GND    -> Arduino GND
 *
 * Warning LED anode -> 220 ohm resistor -> D8
 * Warning LED cathode -> GND
 */

#include <DHT.h>

// DHT11 sensor configuration
#define DHTPIN 2
#define DHTTYPE DHT11

// Warning LED pin
const int warningLED = 8;

// Temperature warning threshold (Celsius)
const float temperatureLimit = 26.0;

// Initialize DHT11 sensor
DHT dht(DHTPIN, DHTTYPE);

// Sensor measurement interval
unsigned long previousRead = 0;
const unsigned long readInterval = 2000;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Start the DHT11 sensor
  dht.begin();

  // Configure warning LED
  pinMode(warningLED, OUTPUT);

  // Perform LED startup test
  digitalWrite(warningLED, HIGH);
  delay(1000);
  digitalWrite(warningLED, LOW);

  // Display initialization messages
  Serial.println("Environmental Monitoring System");
  Serial.println("Temperature Warning System Ready");
}

void loop() {
  // Get current Arduino runtime in milliseconds
  unsigned long currentTime = millis();

  // Read the sensor every 2 seconds
  if (currentTime - previousRead >= readInterval) {

    // Update last reading time
    previousRead = currentTime;

    // Read temperature and humidity
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    // Check for sensor errors
    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("Error: DHT11 reading failed!");
      return;
    }

    // Display measurements
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" C | Humidity: ");
    Serial.print(humidity);
    Serial.print(" %");

    // Check temperature threshold
    if (temperature >= temperatureLimit) {

      // Activate warning LED
      digitalWrite(warningLED, HIGH);
      Serial.println(" | Status: WARNING");

    } else {

      // Turn warning LED off
      digitalWrite(warningLED, LOW);
      Serial.println(" | Status: NORMAL");
    }
  }
}
