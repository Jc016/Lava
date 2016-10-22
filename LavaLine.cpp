#include "LavaLine.h"
#include <Arduino.h>
#define MIN_SPAWN_POSITION 60
#define MAX_SPAWN_POSITION 40

#define MIN_LENGTH 1
#define MAX_LENGTH 3

#define spa


LavaLine::LavaLine() {
}

void LavaLine::setId(int id){
  _id=(id + MAX_LENGTH) * MAX_LENGTH*4+1;
  reset();
}
void   LavaLine::reset() {
  randomSeed(analogRead(0));
  _x = (int)random(MIN_SPAWN_POSITION, MAX_SPAWN_POSITION)+_id;
  _length= (int)random(MIN_LENGTH, MAX_LENGTH);
}
void   LavaLine::process() {
  _x--;
  if (_x + _length < 0) {
    reset();
  }

}
