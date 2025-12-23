#include "simpleLIB.h"

NTCTempSensor sensor(1);


float readTemp;

void setup() {
  Serial.begin(115200);
  sensor.initWith(PA_1, 3.3, 12, 3435, 10000, 10000, true, Serial);

}

void loop() {
  readTemp = sensor.read();
  delay(500);
}