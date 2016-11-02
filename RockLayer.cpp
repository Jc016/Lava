#include "RockLayer.h"


#define NUMPIXELS 58

RockLayer::RockLayer() {
  for(int i = 0 ; i <NUMPIXELS; i++ ){
    _pattern[i] = i%2;  
  }
  clean();
}


void RockLayer::process() {
  const uint32_t ROCK_COLOR [2] = {0xFF000000, 0x00050505};
  clean();
  for (int i = 0; i < NUMPIXELS; i++) {
    _pixels[i] = ROCK_COLOR [ _pattern[i]];
    _pattern[i] = !_pattern[i];
  }
}




void RockLayer::clean() {
  for (int i = 0; i < NUMPIXELS; i++) {
    _pixels[i] = 0x00000000;
  }
}
