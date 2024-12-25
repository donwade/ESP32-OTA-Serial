#ifndef WIRELESSSERIAL_H
#define WIRELESSSERIAL_H

#include <HardwareSerial.h>
#include <AsyncTelnet.h>

#define BAUD_RATE 115200
#define NEWLINE "\r\n"

class WirelessSerial {

public:
    explicit WirelessSerial(HardwareSerial *serial) {
        _serial = serial;
        isClientConnected = false;
        _telnet = new AsyncTelnet();
    }

    void beginLocally(unsigned long baudrate = BAUD_RATE) { // Useful before WiFi.begin()
        _serial->begin(baudrate);
    }

    void begin(unsigned long baudrate = BAUD_RATE) {
        _serial->println();
        _telnet->onConnect([=](void *, AsyncClient *client) {
            _serial->println("\nClient connected");
            isClientConnected = true;
        });

        _telnet->onDisconnect([=](AsyncClient *client) {
            _serial->println("\nClient disconnected");
            isClientConnected = false;
        });

        _telnet->onIncomingData([=](const std::string &data) {
            _serial->print(data.c_str());
        });

        _telnet->begin(false, false);
    }

    void printlnLocally(const std::string &data) {
        _serial->println(data.c_str());
    }

    void print(const std::string &data) {
        print(data.c_str());
    }

    void print(const String &data) {
        print(data.c_str());
    }

    void print(const long data) {
        print(String(data).c_str());
    }

    void print(const bool data) {
        print(data ? "1" : "0");
    }

    void print(const char *data) {
        if (isClientConnected) {
            _telnet->write(data);
        }
        _serial->print(data);
    }

    void println(const std::string &data) {
        println(data.c_str());
    }

    void println(const String &data) {
        println(data.c_str());
    }

    void println(const long data) {
        println(String(data).c_str());
    }

    void println(const bool data) {
        println(data ? "1" : "0");
    }

    void println() {
        println("");
    }

    void println(const char *data) {
        if (isClientConnected) {
            _telnet->write(data);
            _telnet->write(NEWLINE);
        }
        _serial->println(data);
    }

    void setOnIncomingData(std::function<void(std::string)> callback) {
        _telnet->onIncomingData(callback);
    }

private:
    HardwareSerial *_serial;
    AsyncTelnet *_telnet;
    bool isClientConnected;
};

WirelessSerial WSerial(&Serial);

#endif //WIRELESSSERIAL_H
