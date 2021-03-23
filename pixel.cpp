#include "pixel.h"

const int colorsUp[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 16, 18, 20, 22, 24, 27, 30, 33, 36, 40, 44, 48, 53, 58, 64, 70, 77, 84, 92, 101, 111, 121, 132, 144, 157, 172, 188, 205, 224, 245};
const int colorsDown[] = {224, 205, 188, 172, 157, 144, 132, 121, 111, 101, 92, 84, 77, 70, 64, 58, 53, 48, 44, 40, 36, 33, 30, 27, 24, 22, 20, 18, 16, 14, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
const int valueCount = 43;

Pixel::Pixel() {
  progress = 0;
  strip = NULL;
}

Pixel::~Pixel() {
  if (strip != NULL) {
    delete strip;
  }
}


void Pixel::initialize(int ledCount, int pin) {
  Serial.println("Initializing LEDs...");

  if (strip != NULL) {
    delete strip;
  }

  strip = new Adafruit_NeoPixel(ledCount, pin, NEO_GRB + NEO_KHZ800);

  this->NUM_LEDS = ledCount;
  this->pin = pin;

  strip->begin();
  strip->setBrightness(30);
  reset();
}

void Pixel::showStrip() {
  strip->show();
}

void Pixel::setPixel(int pixel, byte red, byte green, byte blue) {
  strip->setPixelColor(pixel, strip->Color(red, green, blue));
}

void Pixel::setPixel(int pixel, byte value) {
  setPixel(pixel, value, value, value);
}

void Pixel::setPixels(int pixel, int colorDown, int colorUp) {
  int nextPixel = (pixel + 1) % NUM_LEDS;
  setPixel(pixel, colorDown);
  setPixel(nextPixel, colorUp);
}

void Pixel::rotate() {
  for (int pixel = 0; pixel < NUM_LEDS; pixel++) {
    for (int step = 0; step < valueCount; step++) {
      setPixels(pixel, colorsDown[step], colorsUp[step]);
      // setPixels((pixel + NUM_LEDS / 2) % NUM_LEDS, colorsDown[step], colorsUp[step]);
      showStrip();
      delay(3);
    }
  }
}

void Pixel::setAll(byte red, byte green, byte blue) {
  for (int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue);
  }
  showStrip();
}

void Pixel::reset() {
  setAll(0, 0, 0);
}

void Pixel::animate() {
  rotate();
}

void Pixel::signalProgress() {
  progress++;
  reset();
  for (int x = 0; x < progress; x++) {
    setPixel(x, 0, 32, 0);
  }
  showStrip();
}

void Pixel::signalError(int amount) {
  reset();
  for (int x = 0; x < amount; x++) {
    setPixel(x, 64, 0, 0);
  }
  showStrip();
}
