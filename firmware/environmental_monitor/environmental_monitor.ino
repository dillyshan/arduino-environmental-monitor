/*
 * Project: Smart Environmental Monitoring System
 * Board: Arduino Uno R3
 * Sensor: DHT11 Temperature and Humidity Sensor
 *
 * Description:
 * Reads temperature and humidity from a DHT11 sensor
 * and displays the measurements in Serial Monitor.
 *
 * Connections:
 * DHT11 Signal -> Arduino D2
 * DHT11 VCC    -> Arduino 5V
 * DHT11 GND    -> Arduino GND
 */

#include <DHT.h>

// Define the digital pin connected to the DHT11
#define DHTPIN 2

// Specify which DHT sensor we're using
#define DHTTYPE DHT11

// Create the DHT sensor object
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Initialize serial communication at 9600 baud
  Serial.begin(9600);

  // Initialize the temperature and humidity sensor
  dht.begin();

  // Display startup messages
  Serial.println("Environmental Monitoring System");
  Serial.println("DHT11 Sensor Initialized");
}

void loop() {
  // Read relative humidity as a percentage
  float humidity = dht.readHumidity();

  // Read temperature in degrees Celsius
  float temperature = dht.readTemperature();

  // Check whether either measurement failed
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Error: Failed to read DHT11!");

    // Wait before trying again
    delay(2000);
    return;
  }

  // Display the temperature reading
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C");

  // Display the humidity reading
  Serial.print(" | Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Take another measurement after 2 seconds
  delay(2000);
}
