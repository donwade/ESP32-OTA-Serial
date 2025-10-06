#ifndef OTA_H
#define OTA_H

#ifdef ESP32
#include <WiFi.h>
#define DEFAULT_PORT 3232
#elif defined(ESP8266)
#define DEFAULT_PORT 8266
#include <string>
#endif
#include <ArduinoOTA.h>
#include <utility>
#include <vector>
#include <numeric>
#include "WirelessSerial.h"

static std::function<void()> disableInterruptsCallback = nullptr;

class OTA {
public:
    static void setupWiFi(const char *ssid,
                          const char *pass,
                          std::function<void()> unableConnectWifiCallback = nullptr) {
        WSerial.beginLocally();

        WSerial.println("\nConnecting to Wi-Fi...");
        WSerial.println(std::string("SSID: ") + ssid);
        WSerial.println(std::string("Password: ") + pass);

        WiFi.begin(ssid, pass);
        WiFi.setAutoReconnect(true);
        while (WiFi.waitForConnectResult() != WL_CONNECTED) {
            WSerial.println("Failed to connect to Wi-Fi");
            if (unableConnectWifiCallback != nullptr) {
                unableConnectWifiCallback();
            }
            delay(500);
            ESP.restart();
        }
    }

    static void start(const char *hostname,
                      const char *password = "",
                      unsigned int port = DEFAULT_PORT) {
        WSerial.begin();

        ArduinoOTA.setPort(port);
        ArduinoOTA.setHostname(hostname);
        ArduinoOTA.setPassword(password);

        ArduinoOTA.onStart([]() {
            WSerial.println("Start updating...");
            if (disableInterruptsCallback == nullptr) {
                WSerial.println("\nDisabling all pins to prevent interrupts");
                disableInterruptsAllPins();
            } else {
                WSerial.println("\nRunning custom callback to disable interrupts");
                disableInterruptsCallback();
            }
            String type;
            if (ArduinoOTA.getCommand() == U_FLASH)
                type = "sketch";
            else // U_SPIFFS
                type = "filesystem";

            // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
            WSerial.println("Start updating " + type);
        });
        ArduinoOTA.onEnd([]() {
            WSerial.println("\nEnd");
        });
        ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
            WSerial.printf("Progress: %u%%\r", (progress / (total / 100)));
        });
        ArduinoOTA.onError([](ota_error_t error) {
            WSerial.printf("Error[%u]: ", error);
            if (error == OTA_AUTH_ERROR) WSerial.println("Auth Failed");
            else if (error == OTA_BEGIN_ERROR) WSerial.println("Begin Failed");
            else if (error == OTA_CONNECT_ERROR) WSerial.println("Connect Failed");
            else if (error == OTA_RECEIVE_ERROR) WSerial.println("Receive Failed");
            else if (error == OTA_END_ERROR) WSerial.println("End Failed");

            WSerial.println("Rebooting...");
            delay(100);
            ESP.restart();
        });

        ArduinoOTA.begin();

        WSerial.println("Ready");
        WSerial.print("IP address: ");
        WSerial.println(WiFi.localIP().toString());
    }

    static void setDisableInterruptsCallback(std::function<void()> _disableInterruptsCallback) {
        disableInterruptsCallback = std::move(_disableInterruptsCallback);
    }

    static void setDisableInterruptsCallback(const std::vector<int> &_pins) {
        disableInterruptsCallback = std::bind(disableInterruptsDefaultCallback, _pins);
    }

    static void handle() {
        ArduinoOTA.handle();
    }

private:
    static void disableInterruptsAllPins() {
        std::vector<int> pins(40);
        std::iota(pins.begin(), pins.end(), 0);
        disableInterruptsDefaultCallback(pins);
    }

    static void disableInterruptsDefaultCallback(const std::vector<int> &pins) {
        for (int pin: pins) {
            WSerial.println("Disabling pin " + String(pin));
            detachInterrupt(pin);
        }
    }
};

#endif //OTA_H
