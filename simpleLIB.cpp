#include "Arduino.h"
#include "simpleLIB.h"
#include <EEPROM_SPI_WE.h>

//Class TempPreset to be used with thermostatic applications and such.

TempPreset::TempPreset(int presNum) {
  this->presetNumber = presNum;

}

void TempPreset::initWith(int _temp, int addr, bool useSer, Stream &ser) {
  this->temp = _temp;
  this->memoryAddress = addr;
  this->serialUsed = useSer;
  this->serial = ser;
}

bool TempPreset::inUse(int set) {
  if (this->temp == set) {
    if (this->serialUsed == true) {this->serial.print("Preset number "); this->serial.print(this->presetNumber); this->serial.println(" set!");}
    return true;
  } else {
    return false;
  }
}

void TempPreset::saveTo(EEPROM_SPI_WE &mem) {
  mem.put(this->memoryAddress, this->temp);
  if (this->serialUsed == true) {
    this->serial.print("Preset number "); this->serial.print(this->presetNumber); this->serial.println(" saved!");
  }
}

void TempPreset::recallFrom(EEPROM_SPI_WE &mem) {
  mem.get(this->memoryAddress, this->temp);
  if (this->serialUsed == true) {
    this->serial.print("Preset number "); this->serial.print(this->presetNumber); this->serial.println(" loaded!");
  }
}

//end of class TempPreset

//Class BasicButton to be used for basic button controlled applications, including protection for holding buttons down and key press detection.

BasicButton::BasicButton(int butNum) {
  this->buttonNumber = butNum;

}

void BasicButton::initWith(PinName Bpin, int mode, int activeOn, bool useSer, Stream &ser) {
  this->serialUsed = useSer;
  this->serial = ser;
  this->buttonPin = Bpin;
  this->mod = mode;
  this->actOn = activeOn;

  if (this->mod == 0) {
    pinMode(this->buttonPin, INPUT_PULLUP);
    this->actOn = 0;
  } else if (this->mod == 1) {
    pinMode(this->buttonPin, INPUT_PULLDOWN);
    this->actOn = 1;
  } else {
    pinMode(this->buttonPin, INPUT);
  }
  state = digitalRead(this->buttonPin);
  lastState = digitalRead(this->buttonPin);

}

bool BasicButton::buttonPressed() {
  
  this->state = digitalRead(this->buttonPin);
  this->wasPressed = (this->state != this->lastState && this->state == this->actOn);
  this->lastState = this->state;
  if (this->serialUsed == true && this->wasPressed == true) {
    this->serial.print("Button number "); this->serial.print(this->buttonNumber); this->serial.println(" pressed!");
  }
  return this->wasPressed;
}

void BasicButton::waitForPress() {
  
  while(this->wasPressed == false) {
    this->state = digitalRead(this->buttonPin);
    this->wasPressed = (this->state != this->lastState && this->state == this->actOn);
    this->lastState = this->state;
    delay(5);
  }
  this->wasPressed = false;
  if (this->serialUsed == true) {
    this->serial.print("Button number "); this->serial.print(this->buttonNumber); this->serial.println(" was pressed!");
  }
}

bool BasicButton::beingPressed() {
  
  this->state = digitalRead(this->buttonPin);
  this->pressed = (this->state == this->lastState && this->state == this->actOn);
  this->lastState = this->state;
  delay(5);

  if (this->serialUsed == true && this->pressed == true) {
    this->serial.print("Button number "); this->serial.print(this->buttonNumber); this->serial.println(" is being pressed!");
  }
  this->pressed = false;
  return this->pressed;
}

//end of class BasicButton

//Class TempSensor to be used in conjunction with a thermistor

TempSensor::TempSensor(int sensNum) {
  this->sensorNumber = sensNum;

}

void TempSensor::initWith(PinName sensPin, float adcRefV, float adcBits, float beta, float resAtRoomTemp, bool useSer, Stream &ser) { //used instead of begin()
  this->adcU = adcRefV;
  this->adcSteps = pow(2, adcBits) - 1;
  this->ntcB = beta;
  this->sensorPin = sensPin;
  this->resAt25 = resAtRoomTemp;
  this->serialUsed = useSer;
  this->serial = ser;
  analogReadResolution(this->adcSteps);

}

float TempSensor::read() {
  this->rawTemp = analogRead(this->sensorPin);
  this->adcRealU = this->rawTemp * (this->adcU/this->adcSteps);
  this->realTemp = (1.0 / ((log(((this->adcRealU * this->resAt25) / (this->adcRealU - this->adcU)) / this->resAt25) * (1.0 / ntcB)) + (1.0 / 298.15)) - 273.15); // output in Celsius
  return this->realTemp;

}

//end of class TempSensor

//Class CurrentSensor to be used with conjuction with a current measuring amplifier connected to the MCU ADC

CurrentSensor::CurrentSensor(int sensNum) {
  this->sensorNumber = sensNum;
}

void CurrentSensor::initWith(PinName currPin, float sensR, float sensVpV, float adcBits, float adcRange, bool useSer, Stream &ser) {
  this->adcSteps = pow(2, adcBits) - 1;
  this->adcR = adcRange;
  this->sensorResistance = sensR;
  this->sensorVoltPerVolt = sensVpV;
  this->serialUsed = useSer;
  this->serial = ser;
  this->currentPin = currPin;
  analogReadResolution(this->adcSteps);

}

float CurrentSensor::read() {
  this->rawCurrent = analogRead(this->currentPin);
  this->actualCurrent = (this->rawCurrent * (this->adcR/this->adcSteps) * (1 / this->sensorVoltPerVolt)) / this->sensorResistance;
  if (this->serialUsed == true) {
    this->serial.print("Sensor number "); this->serial.print(this->sensorNumber); this->serial.print(" value: "); this->serial.println(this->actualCurrent);
  }
  return this->actualCurrent;
  
}

//end of class CurrentSensor

VoltageSensor::VoltageSensor(int sensNum) {
  this->sensorNumber = sensNum;

}

void VoltageSensor::initWith(PinName voltPin, float sensVpV, float adcBits, float adcRange, bool useSer, Stream &ser) {
  this->adcSteps = pow(2, adcBits) - 1;
  this->adcR = adcRange;
  this->sensorVoltPerVolt = sensVpV;
  this->serialUsed = useSer;
  this->serial = ser;
  this->voltagePin = voltPin;

}

float VoltageSensor::read() {
  this->rawVoltage = analogRead(voltagePin);
  this->actualVoltage = this->rawVoltage * (this->adcR/this->adcSteps) * (1 / this->sensorVoltPerVolt);
  if (this->serialUsed == true) {
    this->serial.print("Sensor number "); this->serial.print(this->sensorNumber); this->serial.print(" value: "); this->serial.println(this->actualVoltage);
  }
  return this->actualVoltage;
}

//Misc functions for anything you can think of :)

void toggle(bool &toggled) {toggled = !toggled;}

float toActualValue(float reading, float adcVolt, float adcBits) {
  return (reading * (adcVolt / pow(2, adcBits)));
}


