#ifndef LAVA_GAME_H
#define LAVA_GAME_H

#include <Adafruit_NeoPixel.h>
#define NUMPIXELS 58
#define PIN 6

class LavaGame{
  public: 
  LavaGame();
  play();

  private:

  Adafruit_NeoPixel _strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
}

#endif
