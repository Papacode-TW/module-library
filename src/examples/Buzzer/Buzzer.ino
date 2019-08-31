#include <Modules.h>
#include <pitches.h>

Buzzer buzzer;

void setup() {
  // put your setup code here, to run once:
  buzzer.setFrequency(NOTE_C4);   //defined in pitches.h
}

void loop() {
  // put your main code here, to run repeatedly:
  buzzer.start();
  delay(1000);
  buzzer.stop();
  delay(1000);
}
