#ifndef WIF1CLASS_H
#define WIF1CLASS_H

#include <WiFi.h>

class WiF1Class : public WiFiClass {
public:
    void begin(const char *ssid, const char *pass) {
        WiFiSTAClass::begin(ssid, pass);
        setAutoReconnect(true);
        while (waitForConnectResult() != WL_CONNECTED) {
            delay(5000);
            ESP.restart();
        }
    }
};

WiF1Class WiF1;

#endif //WIF1CLASS_H
