#include "Arduino.h"
#include "RenderSurface.h"
#include "Layer.h"


#define PIN 6
#define NUMPIXELS 60

RenderSurface::RenderSurface() {
  _ledStrip = Adafruit_NeoPixel;
  _ledStrip.begin();
}

void RenderSurface::render() {
  
}
