#include <Modules.h>
#include <pitches.h>

Ultrasound us;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(us.getDistanceCM());
  Serial.print(" cm, ");
  Serial.print(us.getDistanceINCH());
  Serial.println(" inch");
  delay(50);
}
