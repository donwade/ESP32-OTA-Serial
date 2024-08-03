#include "HardwareSerial.h"
#include "util.h"
#include "WirelessSerial.h"

WirelessSerial wSerial(&Serial);

void setup() {
    connectToWiFi();
    wSerial.begin();
    OTASetup();
}

void loop() {
    wSerial.println(wSerial.isClientConnected ? "Client connected" : "Client disconnected");
    OTAHandle();
    delay(1000);
}