#include <ESP8266mDNS.h>

#include "config.h"
#include "otaupdate.h"
#include "wifi.h"
#include "times.h"
#include "pixel.h"

const String LIGHTHOUSE_VERSION = "1.0.2";

const int NETWORK_FAIL = 1;

Times ntp;
OTAUpdate ota;
Pixel pixel;
WiFiConnection wifi;

void setup() {
  initializeSerial();

  pixel.initialize(14, 0);
  signal();

  initializeDeepSleep();
  signal();

  wifi.initialize(localserver);
  signal();

  ota.initialize(OTA_PASSWORD);
  ota.requestUpdate(OTA_URL, LIGHTHOUSE_VERSION);
  signal();

  ntp.initialize(LATITUDE, LONGITUDE, TIMEZONE, durationInSeconds);
  ntp.update();
  signal();

  checkConnectivity();
  signal();

  if (!ntp.isNight()) {
    pixel.reset();
    pixel.animate();
    pixel.animate();
  }
  pixel.reset();
}

void initializeDeepSleep() {
    pinMode(14, INPUT);
}

void initializeSerial() {
  Serial.begin(115200);
  Serial.setTimeout(2000);
  // Wait for serial to initialize.
  while (!Serial) { }
  Serial.println("Booting...");
}

void loop() {
  Serial.println();
  if (ntp.isNight()) {
    pixel.animate();
  } else {
    pixel.reset();

    ota.update();
    ntp.update();
    ota.requestUpdate(OTA_URL, LIGHTHOUSE_VERSION);
    mySleep(ntp.secondsTillSunset());
  }
}

const unsigned long hourInMillis = 60 * 60 * 1000;

void myDelay(unsigned long millis) {
  if (millis > hourInMillis) {
    millis = hourInMillis;
  }
  if (millis > 100) {
    while (millis > 100) {
      millis -= 100;
      delay(100);
      ota.update();
    }
  }
  delay(millis);
  ota.update();
}

void mySleep(unsigned long maxDelayInSeconds) {
  if (maxDelayInSeconds > 60 * 60) {
    maxDelayInSeconds = 60 * 60;
  }
  myDelay(maxDelayInSeconds * 1000);
}

void signal() {
  pixel.signalProgress();
  delay(200);
}

void signalError(int id) {
  pixel.signalError(id);
  delay(10000);
}

void checkConnectivity() {
  if (!wifi.verify()) {
    Serial.println("DNS lookup failed.");
    Serial.flush();

    signalError(NETWORK_FAIL);
    ESP.reset();
  }
}
