# esp8266-lighthouse

LED-Animation for a miniature lighthouse using an esp8266

## History & Idea

It started about three years ago with [Arduino-Lighthouse](https://github.com/dennisfabri/arduino-lighthouse).
This implementation would have been enough to get a miniature lighthouse running. Now I wanted to add some
unnecessary features:

1. On-The-Fly WiFi-Configuration on first boot.
2. WiFi-Connection with NTP-time synchronization.
3. Calculation of sunset based on time and gps-coordinates.
4. LED-animation using a WS2812B-strip.
5. OTA-Updates.

## Implementation status

I have implemented points 1-5. The code of the OTA-Update-Server is currently missing in the repository.

The wiring information is still missing, though it is quite straight forward.

## Future vision ;-)

6. Low-Power-Implementation (for a solar-powered and battery backuped version).
7. Browser based configuration.
