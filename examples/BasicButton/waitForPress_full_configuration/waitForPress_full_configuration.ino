//Full config for waitForPress

#include <simpleLIB.h>

BasicButton button(1); //create a BasicButton object, assigned number 1

void setup() {
  Serial.begin(115200);
  button.initWith(PA_0, 0, 0, true, &Serial); //button on pin PA0, mode 0, active on 0, using serial monitoring on "Serial"
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  button.waitForPress(); //waits for button press, turns on builtin LED for 1 second after button is pressed
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
  
}
