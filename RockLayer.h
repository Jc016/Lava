//class RockLayer
// Process the rock layer on the led strip
#ifndef ROCK_LAYER_H
#define ROCK_LAYER_H

#include <Arduino.h>

#define NUMPIXELS 58

class RockLayer {
  public :
    RockLayer();
    void process();
    void clean();
    uint32_t _pixels [NUMPIXELS];

    private:
    int _id;

    int _pattern[NUMPIXELS];


};

#endif
