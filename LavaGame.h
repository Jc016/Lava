#ifndef LAVA_GAME_H
#define LAVA_GAME_H
#include "Adafruit_NeoPixel.h"
#include "LavaLayer.h"
#include "RockLayer.h"
#include <Chrono.h>
//class LavaGame
// Main controller of the game

#define NUMPIXELS 58
#define PIN 6

class LavaGame{
  public: 
  LavaGame();
  void update();
  void updateAndDraw();
  void printLayersToSrip();
  void reset();


  private:
  Chrono _refreshChronoStrip, _gameClock, _difficultyClock, _melodyClock;
  LavaLayer _lavaLayer;
  RockLayer _rockLayer;
  Adafruit_NeoPixel _strip;
  bool _isJumping;
  int _clockSpeed;
  void processGameRules();
  int _playerTimeJumping;
  bool _hasTouchGround;
  bool _hasGameBegun;
  void processSong();
  int _songPosition;
  int _songInterval;
};

#endif
