#ifndef __WIFI_H__
#define __WIFI_H__

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

class WiFiConnection {
  public:
    WiFiConnection();
    ~WiFiConnection();
    void initialize(const String localserver);
    bool verify();
  private:
    String localserver;
};

#endif
