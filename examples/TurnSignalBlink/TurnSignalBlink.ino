#include <Modules.h>
#include <pitches.h>

TurnSignal ts;

void setup() {
  // put your setup code here, to run once:
  
  ts.initBlink();  //INIT TIMER 1 INTERRUPT
}

void loop() {
  // put your main code here, to run repeatedly:
  ts.setBlinkRight(true);
  delay(5000);
  ts.setBlinkRight(false);
  ts.setBlinkLeft(true);
  delay(5000);
  ts.setBlinkLeft(false);
}
