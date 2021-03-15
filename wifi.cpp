#include "wifi.h"

WiFiConnection::WiFiConnection() {
}

WiFiConnection::~WiFiConnection() {
}

bool WiFiConnection::verify() {
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("WiFi not connected!");
    return false;
  }
  IPAddress serverIP;
  if ((WiFi.hostByName(localserver.c_str(), serverIP) != 1) || (serverIP == 0xFFFFFFFF)) {
    Serial.println("Cannot resolve <localserver>!");
    return false;
  }
  if ((WiFi.hostByName("pool.ntp.org", serverIP) != 1) || (serverIP == 0xFFFFFFFF)) {
    Serial.println("Cannot resolve 'pool.ntp.org'!");
    return false;
  }
  return true;
}

void WiFiConnection::initialize(const String localserver) {
  Serial.println("Initializing WiFi...");

  this->localserver = localserver;

  char apName[20];
  sprintf(apName, "Lighthouse_%i", ESP.getChipId());

  // WiFiManager
  // Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;

  wifiManager.setHostname("sh-lighthouse");
  
  // wifiManager.resetSettings();
  wifiManager.autoConnect(apName);
}
