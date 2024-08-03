#ifndef OTA_WIRELESSSERIAL_H
#define OTA_WIRELESSSERIAL_H

#include <HardwareSerial.h>
#include <AsyncTelnet.h>

#define BAUD_RATE 115200

class WirelessSerial : public AsyncTelnet {

public:
    explicit WirelessSerial(HardwareSerial *serial) : AsyncTelnet(23) {
        _serial = serial;
        isClientConnected = false;
    }

    void begin(unsigned long baudrate = BAUD_RATE) {
        Serial.begin(baudrate);
        AsyncTelnet::onConnect([=](void *, AsyncClient *client) {
            Serial.println("Client connected");
            isClientConnected = true;
        });

        AsyncTelnet::onDisconnect([=](AsyncClient *client) {
            Serial.println("Client disconnected");
            isClientConnected = false;
        });

        AsyncTelnet::begin(false, false);
    }

    void print(const char *data) {
        if (isClientConnected) {
            AsyncTelnet::write(data);
        }
        Serial.print(data);
    }

    void println(const char *data) {
        if (isClientConnected) {
            AsyncTelnet::write(data);
            AsyncTelnet::write("\n");
        }
        Serial.println(data);
    }

    bool isClientConnected;
private:
    HardwareSerial *_serial;
};

#endif //OTA_WIRELESSSERIAL_H
