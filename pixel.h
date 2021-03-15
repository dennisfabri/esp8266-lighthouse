#ifndef __PIXEL_H__
#define __PIXEL_H__

#include <Adafruit_NeoPixel.h>

class Pixel {
  public:
    Pixel();
    ~Pixel();
    void initialize(int ledCount, int pin);

    void reset();
    
    void animate();
    void signalProgress();
    void signalError(int value);
  private:
    Adafruit_NeoPixel* strip;
    int NUM_LEDS;
    int pin;

    int progress;
    
    void showStrip();
    void setAll(byte red, byte green, byte blue);
    
    void setPixel(int pixel, byte red, byte green, byte blue);
    void setPixel(int pixel, byte value);
    void rotate();
    void setPixels(int pixel, int colorDown, int colorUp);
};

#endif
