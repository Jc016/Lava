#ifndef ROCK_LAYER_H
#define ROCK_LAYER_H

#include <Arduino.h>

#define NUMPIXELS 58

class RockLayer {
  public :
    RockLayer();
    void process(int clockTime);
      void clean();
    uint32_t _pixels [NUMPIXELS];
};

#endif
