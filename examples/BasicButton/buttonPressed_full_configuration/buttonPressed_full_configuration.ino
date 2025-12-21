//Fully configured buttonPressed instance
#include <simpleLIB.h>

BasicButton button(1); //create a BasicButton object, assigned number 1

void setup() {
  Serial.begin(115200);
  button.initWith(PA_0, 0, 0, true, Serial); //initialize button with pin PA_0, mode 0, active on 0, serial monitoring enabled on "Serial"
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  if (button.buttonPressed() == true) { //if the button is pressed, turn on the builtin LED for 1 second
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
    digitalWrite(LED_BUILTIN, HIGH);
  }
}