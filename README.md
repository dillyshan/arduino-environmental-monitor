# Smart Environmental Monitoring System

An Arduino-based environmental monitoring system that measures temperature and humidity, automatically detects high-temperature conditions, and records sensor data for analysis.

This project was developed to gain practical experience in embedded systems, sensor interfacing, hardware integration, and data acquisition.

## Project Overview

The system uses an Arduino Uno R3 and a DHT11 sensor to monitor environmental conditions in real time.

When the measured temperature reaches or exceeds 26°C, the Arduino activates a red warning LED.

Temperature, humidity, elapsed time, and system status are transmitted over serial communication in CSV format for analysis and visualization.

## Features

- Real-time temperature monitoring in degrees Celsius
- Relative humidity monitoring (%)
- Automatic high-temperature warning at 26°C
- Red LED visual alert
- Sensor error detection
- Non-blocking measurement scheduling using millis()
- CSV-formatted serial output every 2 seconds
- Temperature and humidity data visualization

## Hardware Components

| Component | Purpose |
|---|---|
| Arduino Uno R3 | Main microcontroller |
| DHT11 Sensor Module | Temperature and humidity measurements |
| Red LED | Visual temperature warning |
| 220 Ohm Resistor | Limits LED current |
| Breadboard | Circuit prototyping |
| Jumper Wires | Electrical connections |
| USB Cable | Power, programming, and serial communication |

## Hardware Connections

| Component | Arduino Connection |
|---|---|
| DHT11 Signal (S) | Digital Pin 2 |
| DHT11 VCC (+) | 5V |
| DHT11 GND (-) | GND |
| Red LED Anode (+) | Digital Pin 8 through 220 Ohm resistor |
| Red LED Cathode (-) | GND |

## Software and Libraries

- Arduino IDE
- Arduino C/C++
- Adafruit DHT Sensor Library
- Adafruit Unified Sensor Library
- Google Sheets for data visualization
- GitHub for version control and documentation

## System Operation

1. The Arduino initializes the DHT11 sensor and serial communication.
2. Temperature and humidity are measured every 2 seconds.
3. The measured temperature is compared against a 26°C threshold.
4. If the threshold is reached, the warning LED turns ON.
5. Otherwise, the LED remains OFF.
6. Measurements and system status are transmitted in CSV format.
7. The recorded data can be analyzed using spreadsheet software.

### Warning Conditions

| Temperature | LED State | System Status |
|---|---|---|
| Below 26°C | OFF | NORMAL |
| 26°C or higher | ON | WARNING |
| Invalid sensor reading | ON | SENSOR_ERROR |

## Data Logging

The Arduino sends measurements through USB serial communication at 9600 baud.

The output format is:

```text
time_ms,temperature_c,humidity_pct,status
2000,22.60,52.00,NORMAL
4000,22.60,52.00,NORMAL
6000,22.60,52.00,NORMAL
```

Time is measured in milliseconds since Arduino startup.

Serial output was collected and saved manually as a CSV file for analysis.

[View Sample Sensor Dataset](data/sample_readings.csv)

## Experimental Results

A 70-second recording was collected with 35 sensor measurements at approximately 2-second intervals.

### Temperature vs. Time

![Temperature vs Time](images/temperature_vs_time.png)

Temperature remained stable at approximately 22.6°C during the recorded test.

### Humidity vs. Time

![Humidity vs Time](images/humidity_vs_time.png)

Relative humidity varied between 52% and 53% during the recorded test.

### Observations

- Temperature remained stable throughout the sample recording.
- Humidity showed small variations of approximately 1 percentage point.
- The system remained in NORMAL status during the recorded dataset.
- The warning LED was separately tested by increasing the temperature measured by the DHT11 until the 26°C threshold was reached.

## Testing and Verification

The following tests were successfully completed:

- Arduino initialization and serial heartbeat test
- DHT11 temperature measurement test
- DHT11 humidity measurement test
- Warning LED startup test
- Temperature threshold activation test
- Normal operating condition test
- CSV serial output verification
- Data visualization using recorded measurements

## Repository Structure

```text
arduino-environmental-monitor/
├── README.md
├── firmware/
│   └── environmental_monitor/
│       └── environmental_monitor.ino
├── data/
│   └── sample_readings.csv
└── images/
    ├── README.md
    ├── temperature_vs_time.png
    └── humidity_vs_time.png
```

## How to Run

1. Assemble the circuit according to the hardware connections table.
2. Install the Adafruit DHT Sensor Library and its dependencies.
3. Open `firmware/environmental_monitor/environmental_monitor.ino` in Arduino IDE.
4. Select Arduino Uno and the correct COM port.
5. Verify and upload the firmware.
6. Open Serial Monitor at 9600 baud.
7. Observe live temperature, humidity, and system status readings.

## Engineering Skills Demonstrated

- Embedded C/C++ programming
- Digital sensor interfacing
- Hardware prototyping and circuit assembly
- Conditional logic and threshold-based control
- Non-blocking timing with millis()
- UART serial communication
- Sensor data acquisition and CSV formatting
- Data visualization and experimental testing
- Git version control and technical documentation

## Future Improvements

- Integrate an I2C LCD for standalone monitoring
- Add an audible alarm using a suitable buzzer driver
- Introduce adjustable temperature thresholds
- Improve sensor fault handling and recovery
- Add automatic computer-side data logging
- Create a permanent circuit diagram and enclosure
