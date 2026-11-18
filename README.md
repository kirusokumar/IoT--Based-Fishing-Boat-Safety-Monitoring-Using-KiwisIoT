# IoT-Based Fishing Boat Safety Monitoring Using KiwisIoT

## Project Overview
This project improves fishing boat safety using a NodeMCU ESP8266, GPS module, water leakage sensor, and SOS emergency button. It monitors the boat's location and safety status, then sends the information to the KiwisIoT platform for remote monitoring.

## Hardware Components
- NodeMCU ESP8266
- NEO-6M GPS Module
- Water Leakage Sensor
- Push Button (SOS)
- Jumper Wires
- Power Supply

## Software Requirements
- Arduino IDE
- ESP8266 Board Package
- KiwisIoT Arduino Library
- TinyGPS++ Library
- SoftwareSerial Library

## Circuit Connections

| Component | ESP8266 Pin |
|---|---|
| GPS TX | D6 (GPS RX) |
| GPS RX | D7 (GPS TX) |
| Water Leakage Sensor | D5 |
| SOS Button | D1 |

The SOS button uses the ESP8266 internal pull-up resistor. Connect the button between D1 and GND.

## Working Principle
The GPS module provides the boat's latitude and longitude. The water leakage sensor detects water inside the boat, while the SOS button allows the user to trigger an emergency status.

Every 5 seconds, the ESP8266 sends the safety information to KiwisIoT. GPS coordinates are transmitted only when a valid and recent GPS location is available.

## KiwisIoT Dashboard

| Channel | Data |
|---|---|
| Channel 0 | GPS Latitude |
| Channel 1 | GPS Longitude |
| Channel 2 | Water Leakage Status |
| Channel 3 | SOS Emergency Status |

## Configuration
Update your Wi-Fi credentials and KiwisIoT Topic ID in the Arduino code:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* pass = "YOUR_WIFI_PASSWORD";
const char* topic = "YOUR_TOPIC_ID";
```

Upload the code to the NodeMCU ESP8266 and monitor boat location and safety information through the KiwisIoT dashboard.

## Applications
- Fishing boat safety monitoring
- Boat water leakage detection
- GPS-based location tracking
- Emergency SOS alert systems
- Marine safety monitoring

## Project Blog
[Read the full project on Hackster.io](https://www.hackster.io/kirusokumar/iot-based-fishing-boat-safety-monitoring-using-kiwisiot-9cce51)

## Recommended Platform
[KiwisIoT – IoT Monitoring Platform](https://www.kiwisiot.in/)

**Arduino Library:** https://github.com/Kiwistron/KiwisIoT

**Example Projects:** https://github.com/Kiwistron/KiwisIoT-Projects/tree/main

---
**Author:** Kirusokumar