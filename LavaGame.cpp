#include "LavaGame.h"
#include <Arduino.h>

#define PLAYER_NORMAL_COLOR 0xFF03738C
#define PLAYER_JUMP_COLOR 0xFF9AEDFF
#define PLAYER_POSITION 11
#define PLAYER_PIN 4
#define JUMP_LENGTH 7
#define JUMP_ACTION LOW
#define IDDLE HIGH
#define REFRESH_RATE 120
#define INCREMENT_DIFFICULTY_TIME  15000
#define DIFFICULTY_MULTIPLYER 2;
#define BASE_GAME_CLOCK 100
#define DEATH_ANIMATION_COLOR 0x00FF0000
#define DEATH_ANIMATION_INTERVAL 50

LavaGame::LavaGame() {
  _hasTouchGround = false;
  _isJumping = false;
  _hasGameBegun = false;
  _clockSpeed = BASE_GAME_CLOCK;
  _lavaLayer = LavaLayer();
  _rockLayer = RockLayer();
  _gameClock.start();
  _difficultyClock.start();
  _playerTimeJumping = 0;
  _refreshChronoStrip.start();
  _strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
  _strip.begin();
}

void LavaGame::reset() {
  _hasTouchGround = false;
  _isJumping = false;
  _hasGameBegun = false;
  _clockSpeed = BASE_GAME_CLOCK;
  _lavaLayer = LavaLayer();
  _rockLayer = RockLayer();
  _gameClock.restart();
  _difficultyClock.restart();
  _playerTimeJumping = 0;
  _refreshChronoStrip.restart();
}

void LavaGame::update() {
  processGameRules();
  if (_refreshChronoStrip.hasPassed(REFRESH_RATE)) {

    _lavaLayer.process();
    _refreshChronoStrip.restart();
  }

  printLayersToSrip();
}

void LavaGame::updateAndDraw() {
  update();
}

void LavaGame::processGameRules() {
  const bool BUTTONSTATE = digitalRead(PLAYER_PIN);

  if (!_hasGameBegun && BUTTONSTATE == IDDLE) {
    _hasGameBegun = true;
  }
  if (BUTTONSTATE == IDDLE) {
    _isJumping = false;
    _playerTimeJumping = 0;
  }

  _hasTouchGround = BUTTONSTATE == IDDLE;
  if (_gameClock.hasPassed(_clockSpeed)) {

    _rockLayer.process(_gameClock.elapsed());
    _lavaLayer.updateLavaLines();

    if (_lavaLayer._pixels[PLAYER_POSITION] != 0x00000000 && !_isJumping ) {
      for (int i = 0; i < NUMPIXELS; i ++) {
        _strip.setPixelColor(i,DEATH_ANIMATION_COLOR);
        _strip.show();
        delay(DEATH_ANIMATION_INTERVAL);

        reset();
      }

    }

    if (_isJumping) {
      _playerTimeJumping++;

    } else if (_hasTouchGround) {
      _playerTimeJumping = 0;
    }

    _isJumping = BUTTONSTATE == JUMP_ACTION && _playerTimeJumping < JUMP_LENGTH;
    _gameClock.restart();
  }

  if (_difficultyClock.hasPassed(INCREMENT_DIFFICULTY_TIME)) {
    _clockSpeed / DIFFICULTY_MULTIPLYER;
    _difficultyClock.restart();
  }
}

void LavaGame::printLayersToSrip() {

  for (int i = 0; i < NUMPIXELS; i ++) {

    if (_rockLayer._pixels[i] != 0x000000) {
      _strip.setPixelColor(i, _rockLayer._pixels[i]);
    }

    if (_lavaLayer._pixels[i] != 0x000000) {
      _strip.setPixelColor(i, _lavaLayer._pixels[i]);
    }


    //set player position
    if (_hasGameBegun) {
      _strip.setPixelColor(PLAYER_POSITION, _isJumping ? PLAYER_JUMP_COLOR  : PLAYER_NORMAL_COLOR );
    }

    _strip.setBrightness(120);

    _strip.show();
  }

}
