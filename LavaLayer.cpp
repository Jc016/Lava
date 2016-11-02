
#include <TrueRandom.h>
#include "LavaLayer.h"


#define NUMPIXELS 58

  LavaLayer::LavaLayer() {
  reset();
}

void LavaLayer::reset() {
  for (int i = 0; i < LAVA_LINE_COUNT; i ++) {
   _lavaLines[i].setId(i);
  }
  clean();
}

void LavaLayer::updateLavaLines() {
  for (int i = 0; i < LAVA_LINE_COUNT; i ++) {
    _lavaLines[i].process();
  }
}

void LavaLayer::process() {
  const uint32_t LAVA_COLOR [3] = {0xFFF28705, 0xFFF25C05, 0xFFF22A05};
  clean();


  for (int i = 0; i < LAVA_LINE_COUNT; i++) {
    for (int j = _lavaLines[i]._x; j < (_lavaLines[i]._x + _lavaLines[i]._length); j++) {
      if (j > 0 && j < NUMPIXELS) {
        _pixels[j] = LAVA_COLOR [(int)random(0, 3)];
      }
    }
  }

}




void LavaLayer::clean() {
  for (int i = 0; i < NUMPIXELS; i++) {
    _pixels[i] = 0x00000000;
  }
}
