/*
 * Project: Smart Environmental Monitoring System
 * Board: Arduino Uno R3
 *
 * Features:
 * - Read temperature and humidity using DHT11
 * - Activate warning LED at 26 C or above
 * - Output measurements in CSV format
 * - Record elapsed time since Arduino startup
 *
 * Connections:
 * DHT11 Signal -> D2
 * DHT11 VCC    -> 5V
 * DHT11 GND    -> GND
 * Warning LED  -> D8 through 220 ohm resistor
 */

#include <DHT.h>

// Sensor configuration
#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Warning LED configuration
const int warningLED = 8;

// Temperature threshold in Celsius
const float temperatureLimit = 26.0;

// Time between sensor measurements
unsigned long previousRead = 0;
const unsigned long readInterval = 2000;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize DHT11 sensor
  dht.begin();

  // Configure warning LED
  pinMode(warningLED, OUTPUT);
  digitalWrite(warningLED, LOW);

  // Print CSV column headings
  Serial.println("time_ms,temperature_c,humidity_pct,status");
}

void loop() {
  // Get elapsed time since Arduino startup
  unsigned long currentTime = millis();

  // Take a measurement every 2 seconds
  if (currentTime - previousRead >= readInterval) {

    previousRead = currentTime;

    // Read sensor measurements
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    // Handle sensor reading errors
    if (isnan(temperature) || isnan(humidity)) {
      digitalWrite(warningLED, HIGH);

      Serial.print(currentTime);
      Serial.println(",NaN,NaN,SENSOR_ERROR");
      return;
    }

    // Determine system status
    const char* status;

    if (temperature >= temperatureLimit) {
      digitalWrite(warningLED, HIGH);
      status = "WARNING";
    } else {
      digitalWrite(warningLED, LOW);
      status = "NORMAL";
    }

    // Output measurement as CSV
    Serial.print(currentTime);
    Serial.print(",");

    Serial.print(temperature);
    Serial.print(",");

    Serial.print(humidity);
    Serial.print(",");

    Serial.println(status);
  }
}
