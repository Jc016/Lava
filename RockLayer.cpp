#include "RockLayer.h"


#define NUMPIXELS 58

RockLayer::RockLayer() {
  clean();
}

void RockLayer::process(int clockTime) {
  const uint32_t ROCK_COLOR [2] = {0xFF000000, 0x00050505};
  int startColor = clockTime%2;
  clean();
  for (int i = 0; i < NUMPIXELS; i++) {
    _pixels[i] = ROCK_COLOR [(startColor+i)%2];
  }
}




void RockLayer::clean() {
  for (int i = 0; i < NUMPIXELS; i++) {
    _pixels[i] = 0x00000000;
  }
}
