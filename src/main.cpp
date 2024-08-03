#include "HardwareSerial.h"
#include "secrets.h"
#include "WirelessSerial.h"
#include "OTA.h"
#include "WiF1Class.h"

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