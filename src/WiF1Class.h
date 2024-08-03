#ifndef ESP32_OTA_H
#define ESP32_OTA_H

#include <WiFi.h>

class WiF1Class : public WiFiClass {
public:
    void begin(const char *ssid, const char *pass) {
        WiFiSTAClass::begin(ssid, pass);
        setAutoReconnect(true);
        while (waitForConnectResult() != WL_CONNECTED) {
            delay(2000);
            ESP.restart();
        }
    }
};

WiF1Class WiF1;

#endif //ESP32_OTA_H
