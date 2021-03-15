#ifndef __TIMES_H__
#define __TIMES_H__

#include <WiFiUdp.h>
#include <NTPClient.h>

#include <sunset.h>
#include <time.h>

class Times {
  public:
    Times();
    ~Times();
    void initialize(double latitude, double longitude, int timezone, unsigned long durationInSeconds);
    void update();
    bool isNight();
    unsigned long secondsTillSunset();
  private:
    WiFiUDP ntpUDP;               // Create an instance of the WiFiUDP class to send and receive
    NTPClient* timeClient;         // UTC and Update every hour
    SunSet sun;

    unsigned long sunsetInSeconds = 0;
    unsigned long durationInSeconds = 0;

    const unsigned long noonInSeconds = 12 * 60 * 60;
    const unsigned long dayInSeconds = 24 * 60 * 60;

    void updateTime();
    void updateSunset();
    unsigned long getTimeOfDayInSeconds();
};

#endif
