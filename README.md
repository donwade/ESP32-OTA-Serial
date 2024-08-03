# ESP32 OTA Serial & Updater

This small project provides simple ready to use mechanism to update your ESP32 over the air (OTA) and to handle serial
communication wirelessly using PlatformIO.
It uses ArduinoOTA library as well as forked(slightly changed) version
of: https://github.com/janphoffmann/AsyncTelnet.git

### Prerequisites

Copy the following files from HelloWorld example to your project:

- HelloWorld.ino (into src dir)
- secrets.h (into src dir)
- platformio.ini (into project root)

You also need to edit a `secrets.h` file that contains your WiFi credentials.

### IMPORTANT!!!

Remember to add this file to your `.gitignore` file to avoid sharing your secrets with the world.

### How to use

To upload project for the first time you need to comment out these lines in `platformio.ini` file:

```ini
upload_protocol = espota
upload_port = ${env.HOSTNAME}.local
monitor_port = socket://${env.HOSTNAME}.local:23
```

Then run in console in project directory: `pio run -t upload -e esp32dev`

After uploading the project you can uncomment these lines and run the same command again, but now you don't need to connect ESP32 to your computer.

Now you can also get serial output wirelessly using `pio device monitor -e esp32dev` command.

### How it works

The `HelloWorld.ino` file is a simple example that demonstrates what this library does:

1. Connects to the WiFi network using the credentials from `secrets.h`.
2. Begins the wireless serial communication.
3. Sets up the OTA updater with a specific hostname.
4. In the main loop, it sends a "Hello, world!" message followed by the current time in milliseconds to the serial port
   every second. It also handles any incoming OTA updates.

Here's the code:

```cpp
#include "secrets.h"
#include <WiF1Class.h>
#include <HardwareSerial.h>
#include <WirelessSerial.h>
#include <OTA.h>

void setup() {
    WiF1.begin(WIFI_SSID, WIFI_PASS);
    WSerial.begin();
    OTA::setup("ESP32-OTA");
}

void loop() {
    WSerial.println("Hello, world! " + String(millis()));
    OTA::handle();
    delay(1000);
}
```

Once the code is running on your ESP32, you can connect to the serial port wirelessly using PlatformIO Serial Monitor or
any Telnet and see the "Hello, world!" messages. You can also send OTA updates to the ESP32 using the specified
hostname.