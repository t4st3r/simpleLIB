#include "simpleLIB.h"

VoltageSensor sensor(1); //create VoltageSensor instance with ID number 1

float sensorOutput;

void setup() {
  Serial.begin(115200);
  sensor.initWith(PA_1, 1, 12, 3.3, true, &Serial); //initialize voltage sensor on pn PA1, 1V/V voltage sensitivity, using serial monitoring on "Serial"
}

void loop () {
  sensorOutput = sensor.read();
  delay(500);
}