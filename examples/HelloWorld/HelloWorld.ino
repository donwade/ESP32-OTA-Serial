#include "secrets.h"
#include <OTA.h>

void setup() {
    OTA::setupWiFi(WIFI_SSID, WIFI_PASS);
    OTA::start("ESP32-OTA");
}

void loop() {
    WSerial.println("Hello, world! " + String(millis()));
    delay(1000);
}