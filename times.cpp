#include "Times.h"

Times::Times() {
  timeClient = new NTPClient (ntpUDP);
}

Times::~Times() {
  delete timeClient;
}

void Times::update() {
  updateTime();
  updateSunset();
}


void Times::updateTime() {
  timeClient->update();
}

void Times::initialize(double latitude, double longitude, int timezone, unsigned long durationInSeconds) {
  Serial.println("Initializing NTP...");
  this->durationInSeconds = durationInSeconds;
  timeClient->begin();
  Serial.println("Initializing Sunset...");
  sun.setPosition(latitude, longitude, timezone);
}

unsigned long Times::getTimeOfDayInSeconds() {
  return timeClient->getSeconds() + timeClient->getMinutes() * 60 + timeClient->getHours() * 60 * 60;
}

void Times::updateSunset() {
  unsigned long epochTime = timeClient->getEpochTime();
  struct tm *ptm = gmtime ((time_t *)&epochTime);

  int day = ptm->tm_mday;
  int month = ptm->tm_mon + 1;
  int year = ptm->tm_year + 1900;

  sun.setCurrentDate(year, month, day);
  sunsetInSeconds = sun.calcSunset() * 60;
}

bool Times::isNight() {
  unsigned long timeInSeconds = getTimeOfDayInSeconds();
  if (timeInSeconds < noonInSeconds) {
    timeInSeconds += dayInSeconds;
  }  
  return timeInSeconds > sunsetInSeconds && timeInSeconds < sunsetInSeconds + durationInSeconds;
}

unsigned long Times::secondsTillSunset() {
  return sunsetInSeconds - getTimeOfDayInSeconds();
}
