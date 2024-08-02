#include "HardwareSerial.h"
#include "AsyncTelnetSerial.h"
#include "util.h"

#define BAUD_RATE 115200

AsyncTelnetSerial telnetSerial(&Serial);

void setup() {
    Serial.begin(BAUD_RATE);
    connectToWiFi();
    OTASetup();
    telnetSerial.begin();
}

void loop() {
    OTAHandle();
    Serial.print("Hello World");
    delay(100);
}