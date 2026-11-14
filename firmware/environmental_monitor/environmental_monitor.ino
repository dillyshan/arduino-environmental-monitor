/*
 * Project: Smart Environmental Monitoring System
 * Board: Arduino Uno R3
 * Purpose: Test the Arduino using an LED heartbeat
 */

const int statusLED = LED_BUILTIN;

unsigned long previousTime = 0;
const unsigned long blinkInterval = 1000;

bool ledState = false;

void setup() {
  pinMode(statusLED, OUTPUT);
  Serial.begin(9600);

  Serial.println("Environmental Monitor");
  Serial.println("System initialized");
  Serial.println("Hardware test running...");
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - previousTime >= blinkInterval) {
    previousTime = currentTime;

    ledState = !ledState;
    digitalWrite(statusLED, ledState);

    Serial.println("System heartbeat: OK");
  }
}
