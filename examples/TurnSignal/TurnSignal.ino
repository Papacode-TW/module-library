#include <Modules.h>
#include <pitches.h>

TurnSignal turnSignal;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  turnSignal.setRight(true);
  delay(500);
  turnSignal.setRight(false);
  delay(500);
  turnSignal.setLeft(true);
  delay(500);
  turnSignal.setLeft(false);
  delay(500);
}
