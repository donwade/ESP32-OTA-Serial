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
    OTAHandle();
    delay(1000);
}