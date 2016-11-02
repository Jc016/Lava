//class LavaLayer
// Process the lava layer on the strip

#ifndef LAVA_LAYER_H
#define LAVA_LAYER_H


#include <Arduino.h>
#include "LavaLine.h"

#define LAVA_LINE_COUNT 8

#define NUMPIXELS 58

class LavaLayer {
  public :
    LavaLayer();
    void process();
    void clean();
    void reset();
    void updateLavaLines();
    uint32_t _pixels [NUMPIXELS];
    LavaLine _lavaLines [LAVA_LINE_COUNT];
};

#endif
