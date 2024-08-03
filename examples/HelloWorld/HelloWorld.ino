#include "secrets.h"
#include <WiF1Class.h>
#include <HardwareSerial.h>
#include <WirelessSerial.h>
#include <OTA.h>

void setup() {
    WiF1.begin(WIFI_SSID, WIFI_PASS);
    WSerial.begin();
    OTA::setup("ESP32-OTA");
}

void loop() {
    WSerial.println("Hello, world! " + String(millis()));
    OTA::handle();
    delay(1000);
}