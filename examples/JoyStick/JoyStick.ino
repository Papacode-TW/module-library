#include <Modules.h>
#include <pitches.h>

JoyStick js;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(js.readX());
  Serial.print(" ");
  Serial.print(js.readY());
  Serial.print(" ");
  if(js.isClicked()){
    Serial.print("clicked ");
  }
  if(js.up()){
    Serial.print("up ");
  }
  if(js.down()){
    Serial.print("down ");
  }
  if(js.left()){
    Serial.print("left ");
  }
  if(js.right()){
    Serial.print("right ");
  }
  Serial.print("\n");;
  delay(100);
}