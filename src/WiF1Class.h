#ifndef ESP32-OTA-Serial-And-Updater_WIF1_H
#define ESP32-OTA-Serial-And-Updater_WIF1_H

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

#endif //ESP32-OTA-Serial-And-Updater_WIF1_H
