#include "simpleLIB.h"

CurrentSensor sensor(1); //create CurrentSensor instance with ID number 1

float sensorOutput;

void setup() {
  Serial.begin(115200);
  sensor.initWith(PA_1, 0.1, 10, 12, 3.3, true, &Serial); //initialize current sensor on pin PA1, with sense resistor 0.1 ohm, 10V/V current measurement amplifier gain, 12 bit ADC used, 3.3V ADC reference voltage, using serial monitoring on "Serial"
}

void loop () {
  sensorOutput = sensor.read();
  delay(500);
}