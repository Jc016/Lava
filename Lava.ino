/*Lava Arduino Game
November 2nd 2016
by Jean-Christophe Leclerc-Massé
jclm1992@gmail.com
*/

#include "LavaGame.h"
#include <Adafruit_NeoPixel.h>




LavaGame lavaGame = LavaGame();

void setup() {
  Serial.begin(9600);

}

void loop() {
  lavaGame.updateAndDraw();
}
