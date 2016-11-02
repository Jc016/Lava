#include "LavaGame.h"
#include <Arduino.h>

#define PLAYER_NORMAL_COLOR 0xFF03738C
#define PLAYER_JUMP_COLOR 0xFF9AEDFF
#define PLAYER_POSITION 11
#define PLAYER_PIN 4
#define SPEAKER_PIN 9
#define JUMP_LENGTH 6
#define JUMP_ACTION LOW
#define IDDLE HIGH
#define REFRESH_RATE 120
#define INCREMENT_DIFFICULTY_TIME  18000
#define DIFFICULTY_MULTIPLYER 2;
#define BASE_GAME_CLOCK 80
#define START_ANIMATION_COLOR 0x00FFEEFF
#define DEATH_ANIMATION_COLOR 0x00FF0000
#define DEATH_ANIMATION_INTERVAL 10
#define SONG_INTERVAL  30

LavaGame::LavaGame() {
  _hasTouchGround = false;
  _isJumping = false;
  _hasGameBegun = false;
  _clockSpeed = BASE_GAME_CLOCK;
  _lavaLayer = LavaLayer();
  _rockLayer = RockLayer();
  _gameClock.start();
  _melodyClock.start();
  _difficultyClock.start();
  _playerTimeJumping = 0;
  _songInterval = SONG_INTERVAL;
  _refreshChronoStrip.start();
  _strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
  _strip.begin();
  _songPosition = 0;
}

void LavaGame::reset() {
  _hasTouchGround = false;
  _isJumping = false;
  _hasGameBegun = false;
  _clockSpeed = BASE_GAME_CLOCK;
  _songInterval = SONG_INTERVAL;
  _lavaLayer = LavaLayer();
  _rockLayer = RockLayer();
  _gameClock.restart();
  _melodyClock.restart();
  _difficultyClock.restart();
  _playerTimeJumping = 0;
  _refreshChronoStrip.restart();
  _songPosition = 0;
  for (int i = 0; i < NUMPIXELS; i ++) {
    _strip.setPixelColor(i,  START_ANIMATION_COLOR);
    _strip.show();
    delay(DEATH_ANIMATION_INTERVAL);
  }
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

  if (_hasGameBegun && _melodyClock.hasPassed(_songInterval) && ! _isJumping) {
    //processSong();
    //_melodyClock.restart();
  }

  _hasTouchGround = BUTTONSTATE == IDDLE;
  if (_gameClock.hasPassed(_clockSpeed)) {


    if (_hasGameBegun) {
      _rockLayer.process();
      _lavaLayer.updateLavaLines();

    }




    if (_isJumping) {
      _playerTimeJumping++;

    } else if (_hasTouchGround) {
      _playerTimeJumping = 0;
    }

    _isJumping = BUTTONSTATE == JUMP_ACTION && _playerTimeJumping < JUMP_LENGTH;
    if(BUTTONSTATE == JUMP_ACTION && _playerTimeJumping == 0 && _hasGameBegun){
        tone(SPEAKER_PIN, 3300, 25);
    }
    if (_lavaLayer._pixels[PLAYER_POSITION] != 0x00000000 && !_isJumping ) {
      noTone(SPEAKER_PIN);
      for (int i = NUMPIXELS; i >= 0 ; i --) {
        _strip.setPixelColor(i, DEATH_ANIMATION_COLOR);
        _strip.show();
        delay(DEATH_ANIMATION_INTERVAL);

      }
      delay(200);
      reset();

    }
    _gameClock.restart();
  }

  if (_difficultyClock.hasPassed(INCREMENT_DIFFICULTY_TIME)) {
    _clockSpeed /= DIFFICULTY_MULTIPLYER;
    _songInterval / DIFFICULTY_MULTIPLYER;
    Serial.println(_clockSpeed);
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

void LavaGame::processSong() {
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

  tone(SPEAKER_PIN, tones[(int)random(8)], _songInterval);

  _songPosition ++;




}
