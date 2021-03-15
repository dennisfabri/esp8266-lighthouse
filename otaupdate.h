#ifndef __OTAUPDATE_H__
#define __OTAUPDATE_H__

#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>

class OTAUpdate {
  public:
    OTAUpdate();
    void initialize(const char* password);
    void update();
    void requestUpdate(String url, String currentVersion);
};

#endif
