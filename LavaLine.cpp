#include "LavaLine.h"
#include <Arduino.h>

#define MIN_SPAWN_POSITION 75
#define MAX_SPAWN_POSITION 56

#define MIN_LENGTH 1
#define MAX_LENGTH 5

#define spa


LavaLine::LavaLine() {
}

void LavaLine::setId(int id){
  _id = id + id * MAX_LENGTH*8 +3;
   reset();
}
void   LavaLine::reset() {
  //randomSeed(analogRead());
  _x = (int)rand() % (MAX_SPAWN_POSITION-MIN_SPAWN_POSITION+1) + MIN_SPAWN_POSITION + _id;
  _length= (int)rand() % (MAX_LENGTH-MIN_LENGTH) + MIN_LENGTH;
}
void   LavaLine::process() {
  _x--;
  if (_x + _length < 0) {
    reset();
  }

}
