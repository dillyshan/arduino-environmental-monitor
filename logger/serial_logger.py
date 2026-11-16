"""
Project: Smart Environmental Monitoring System
File: serial_logger.py

Purpose:
Automatically collect temperature and humidity
data from Arduino and save it to a CSV file.
"""

import serial
import csv
from datetime import datetime
from pathlib import Path

# Arduino serial communication settings
PORT = "COM23"
BAUD_RATE = 9600

# Create a unique CSV filename for each recording
timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
filename = f"readings_{timestamp}.csv"

# Save the CSV in the same folder as this script
file_path = Path(__file__).resolve().parent / filename

try:
    # Connect to Arduino through USB
    with serial.Serial(PORT, BAUD_RATE, timeout=3) as arduino:

        # Create the CSV file
        with open(file_path, "w", newline="") as file:
            writer = csv.writer(file)

            # Write CSV column headings
            writer.writerow([
                "time_ms",
                "temperature_c",
                "humidity_pct",
                "status"
            ])

            print("Connected to Arduino!")
            print("Recording sensor measurements...")
            print("Press Ctrl+C to stop.")

            # Continuously collect Arduino readings
            while True:
                line = arduino.readline().decode(
                    "utf-8", errors="replace"
                ).strip()

                # Ignore empty lines and CSV headers
                if not line or line.startswith("time_ms"):
                    continue

                # Split the received CSV data
                values = next(csv.reader([line]))

                # Accept only valid measurement records
                if (
                    len(values) == 4
                    and values[3] in ("NORMAL", "WARNING", "SENSOR_ERROR")
                ):
                    writer.writerow(values)

                    # Save measurements immediately
                    file.flush()

                    print("Saved:", line)

except KeyboardInterrupt:
    print("\nRecording stopped.")

except serial.SerialException as error:
    print("Serial connection error:", error)

print("CSV file:", file_path)
