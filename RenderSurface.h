

#ifndef RENDER_SURFACE_H
#define RENDER_SURFACE_H

#include "Arduino.h"
#include "Adafruit_NeoPixel.h"
#include "Layer.h"

class RenderSurface{
  public:
  void render();
  private:
  Adafruit_NeoPixel _ledStrip;
  Layer _layers[3];
  
  
}

#endif
