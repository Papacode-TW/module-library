#include <Modules.h>
#include <pitches.h>

TurnSignal ts;

void setup() {
  // put your setup code here, to run once:
  
  ts.initBlink(2);  //INIT TIMER 1 INTERRUPT in Hz
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
