
#include <Arduino.h>

#include <WiFi.h>
#include <ThingSpeak.h>

#include "secrets.h"

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const int sensorPin = 34;
WiFiClient client;

unsigned long channelID = 3532489;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");

  ThingSpeak.begin(client);
  Serial.println("ThingSpeak Initialized");
  Serial.println("Water Level Monitoring Started");
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  float waterLevel = (sensorValue / 4095.0) * 100.0;

  Serial.print("Sensor Reading: ");
  Serial.print(sensorValue);

  Serial.print(" | Water Level: ");
  Serial.print(waterLevel);
  Serial.println("%");

  ThingSpeak.setField(1, waterLevel);
  int response = ThingSpeak.writeFields(channelID, writeAPIKey);

  if (response == 200) {
    Serial.println("ThingSpeak update successful!");
  } else {
    Serial.print("ThingSpeak error: ");
    Serial.println(response);
  }

  delay(20000);
}
