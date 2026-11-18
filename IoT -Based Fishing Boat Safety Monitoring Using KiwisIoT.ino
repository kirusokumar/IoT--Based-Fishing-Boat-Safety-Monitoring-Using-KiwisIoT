#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <KiwisIoT.h>

// WiFi Credentials
const char* ssid = "YOUR_WIFI_NAME";
const char* pass = "YOUR_WIFI_PASSWORD";

// KiwisIoT Topic ID
const char* topic = "YOUR_TOPIC_ID";

// Sensor Pins
#define GPS_RX D6
#define GPS_TX D7

#define LEAK_PIN D5
#define SOS_PIN D1

// GPS Configuration
SoftwareSerial gpsSerial(GPS_RX, GPS_TX);
TinyGPSPlus gps;

// KiwisIoT
KiwisIoT kiwisiot(ssid, pass, topic);

unsigned long previousMillis = 0;

void setup() {

  Serial.begin(115200);
  gpsSerial.begin(9600);

  pinMode(LEAK_PIN, INPUT);
  pinMode(SOS_PIN, INPUT_PULLUP);

  kiwisiot.begin();

  Serial.println("Fishing Boat Safety Monitoring Started");
}

void loop() {

  kiwisiot.run();

  // Read GPS information
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  if (millis() - previousMillis >= 5000) {

    previousMillis = millis();

    // Read water leakage sensor
    int leakReading = digitalRead(LEAK_PIN);

    String leakStatus =
      (leakReading == LOW) ? "WATER DETECTED" : "NORMAL";

    // Read SOS button
    int sosReading = digitalRead(SOS_PIN);

    String sosStatus =
      (sosReading == LOW) ? "EMERGENCY" : "SAFE";

    Serial.println("\n--- BOAT SAFETY STATUS ---");

    Serial.print("Water Leakage: ");
    Serial.println(leakStatus);

    Serial.print("SOS Status: ");
    Serial.println(sosStatus);

    // Send safety information
    kiwisiot.send("2", leakStatus);
    kiwisiot.send("3", sosStatus);

    // Send GPS information only when valid
    if (gps.location.isValid() &&
        gps.location.age() < 10000) {

      double latitude = gps.location.lat();
      double longitude = gps.location.lng();

      Serial.print("Latitude: ");
      Serial.println(latitude, 6);

      Serial.print("Longitude: ");
      Serial.println(longitude, 6);

      kiwisiot.send("0", String(latitude, 6));
      kiwisiot.send("1", String(longitude, 6));

    } else {

      Serial.println("Waiting for GPS Signal...");

    }
  }
}