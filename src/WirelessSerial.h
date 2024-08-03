#ifndef OTA_WIRELESSSERIAL_H
#define OTA_WIRELESSSERIAL_H

#include <HardwareSerial.h>
#include <AsyncTelnet.h>

#define BAUD_RATE 115200

class WirelessSerial {

public:
    explicit WirelessSerial(HardwareSerial *serial) {
        _serial = serial;
        isClientConnected = false;
        _telnet = new AsyncTelnet();
    }

    void begin(unsigned long baudrate = BAUD_RATE) {
        _serial->begin(baudrate);
        _telnet->onConnect([=](void *, AsyncClient *client) {
            _serial->println("Client connected");
            isClientConnected = true;
        });

        _telnet->onDisconnect([=](AsyncClient *client) {
            _serial->println("Client disconnected");
            isClientConnected = false;
        });

        _telnet->begin(false, false);
    }

    void print(const char *data) {
        if (isClientConnected) {
            _telnet->write(data);
        }
        _serial->print(data);
    }

    void println(const char *data) {
        if (isClientConnected) {
            _telnet->write(data);
            _telnet->write("\n");
        }
        _serial->println(data);
    }

    bool isClientConnected;
private:
    HardwareSerial *_serial;
    AsyncTelnet *_telnet;
};

#endif //OTA_WIRELESSSERIAL_H
