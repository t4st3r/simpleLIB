#include "Arduino.h"
#include "simpleLIB.h"
#include <EEPROM_SPI_WE.h>

//Class TempPreset to be used with thermostatic applications and such.

TempPreset::TempPreset() {}

bool TempPreset::inUse(int set) {
  if (this->temp == set) {
    return true;
  } else {
    return false;
  }
}

void TempPreset::setAddress(int addr) {
  this->memoryAddress = addr;
}

void TempPreset::initTemp(int _temp) {
  this->temp = _temp;
}

void TempPreset::saveTo(EEPROM_SPI_WE &mem) {
  mem.put(this->memoryAddress, this->temp);
  Serial.println("Preset saved!");
}

void TempPreset::recallFrom(EEPROM_SPI_WE &mem) {
  mem.get(this->memoryAddress, this->temp);
}

//Class BasicButton to be used for basic button controlled applications, including protection for holding buttons down and some functions for the buttons.

BasicButton::BasicButton() {}

void BasicButton::initializeWithPin(PinName Bpin) {

  this->buttonPin = Bpin;

  pinMode(this->buttonPin, INPUT_PULLUP);
  
  state = digitalRead(this->buttonPin);
  lastState = digitalRead(this->buttonPin);

}

bool BasicButton::buttonPressed() {
  
  this->state = digitalRead(this->buttonPin);

  bool wasPressed (this->state != this->lastState && this->state == 0);
  this->lastState = this->state;
  return wasPressed;
  
}

//Class TempSensor to be used in conjunction with a thermistor

TempSensor::TempSensor() {}

void TempSensor::initWith(float adcRefV, float adcBitCount, float beta, PinName Tpin, float resAtRoomTemp) { //used instead of begin()
  this->adcU = adcRefV;
  this->adcB = adcBitCount;
  this->ntcB = beta;
  this->sensorPin = Tpin;
  this->resAt25 = resAtRoomTemp;

}

float TempSensor::read() {
  this->rawTemp = analogRead(this->sensorPin);
  this->adcRealU = this->rawTemp * (this->adcU/this->adcB);
  this->realTemp = (1.0 / ((log(((this->adcRealU * this->resAt25) / (this->adcRealU - this->adcU)) / this->resAt25) * (1.0 / ntcBeta)) + (1.0 / 298.15)) - 273.15); // output in Celsius
  return this->realTemp;

}

//Misc functions for anything you can think of :)

void toggle(bool &toggled) {toggled = !toggled;}


