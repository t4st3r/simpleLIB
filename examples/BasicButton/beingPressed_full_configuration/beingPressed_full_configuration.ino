//Full config for beingPressed

#include <simpleLIB.h>

BasicButton button(1); //create a BasicButton object, assigned number 1

void setup() {
  Serial.begin(115200);
  button.initWith(PA_0, 0, 0, true, Serial); //button on pin PA0, mode 0, active on 0, using serial monitoring on "Serial"
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  if (button.beingPressed() == true) { //checks if the button is being continuously pressed, if true, turns the builtin LED on
    digitalWrite(LED_BUILTIN, LOW);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
  }
}
