#include "otaupdate.h"
#include <ESP8266httpUpdate.h>

OTAUpdate::OTAUpdate() {}

void OTAUpdate::initialize(const char* password) {
  Serial.println("Initializing OTA...");
  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname("sh-lighthouse");

  // No authentication by default
  ArduinoOTA.setPassword(password);

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
}

void OTAUpdate::update() {
  ArduinoOTA.handle();
}

void OTAUpdate::requestUpdate(String url, String currentVersion) {
  Serial.println("Requesting new firmware.");
  WiFiClient wifi;
  t_httpUpdate_return ret = ESPhttpUpdate.update(wifi, url, currentVersion);
  switch (ret) {
    case HTTP_UPDATE_FAILED:
      Serial.println("[OTA-Update] Update failed.");
      break;
    case HTTP_UPDATE_NO_UPDATES:
      Serial.println("[OTA-Update] No Update.");
      break;
    case HTTP_UPDATE_OK:
      Serial.println("[OTA-Update] Update ok."); // may not called we reboot the ESP
      break;
    default:
      Serial.println("[OTA-Update] Unkown status.");
      break;
  }
}
