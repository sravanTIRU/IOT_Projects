// Includes the basic Arduino functions for ESP32
#include <Arduino.h>

// Library for connecting the ESP32 to Wi-Fi
#include <WiFi.h>

// Library for sending data to ThingSpeak
#include <ThingSpeak.h>

// Contains the private ThingSpeak Write API Key
// This file must remain excluded from GitHub
#include "secrets.h"

// Wi-Fi network name and password provided by Wokwi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ESP32 GPIO 34 receives the simulated water-level sensor input
const int sensorPin = 34;

// Creates a Wi-Fi client for communicating with ThingSpeak
WiFiClient client;

// ID of the ThingSpeak channel where readings are stored
unsigned long channelID = 3532489;

void setup() {
  // Starts serial communication at 115200 baud
  Serial.begin(115200);

  // Starts connecting the ESP32 to the Wi-Fi network
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  // Waits until the ESP32 successfully connects to Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);             // Waits for half a second
    Serial.print(".");      // Displays connection progress
  }

  // Displays a message after connecting to Wi-Fi
  Serial.println("\nWiFi Connected!");

  // Initializes the ThingSpeak library using the Wi-Fi client
  ThingSpeak.begin(client);

  // Displays startup messages in the serial terminal
  Serial.println("ThingSpeak Initialized");
  Serial.println("Water Level Monitoring Started");
}

void loop() {
  // Reads the analog sensor value (ESP32 ADC range: 0 to 4095)
  int sensorValue = analogRead(sensorPin);

  // Converts the sensor value into a percentage from 0% to 100%
  float waterLevel = (sensorValue / 4095.0) * 100.0;

  // Displays the raw sensor reading
  Serial.print("Sensor Reading: ");
  Serial.print(sensorValue);

  // Displays the calculated water-level percentage
  Serial.print(" | Water Level: ");
  Serial.print(waterLevel);
  Serial.println("%");

  // Stores the water-level percentage in ThingSpeak Field 1
  ThingSpeak.setField(1, waterLevel);

  // Uploads the reading to ThingSpeak using the channel ID and API key
  int response = ThingSpeak.writeFields(channelID, writeAPIKey);

  // HTTP status code 200 indicates a successful update
  if (response == 200) {
    Serial.println("ThingSpeak update successful!");
  } else {
    // Displays the error code if the upload fails
    Serial.print("ThingSpeak error: ");
    Serial.println(response);
  }

  // Waits 20 seconds before the next reading and upload
  // This respects ThingSpeak's typical free-channel update interval
  delay(20000);
}