#ifndef simpleLIB_h
#define simpleLIB_h

#include "Arduino.h"
#include <EEPROM_SPI_WE.h>

class TempPreset {
  public:
  TempPreset(int presNum);
  float temp = 0;
  bool serialUsed;
  int memoryAddress = 0;
  int presetNumber = 0;
  Stream &serial = Serial;
  bool inUse(int set);
  void initWith(int _temp, int addr, bool useSer = false, Stream &ser = Serial);
  void saveTo(EEPROM_SPI_WE& mem);
  void recallFrom(EEPROM_SPI_WE& mem);
  
};

class BasicButton {
  public:
  BasicButton(int butNum); //constructor, sets the number ID of button
  int state = false;
  int lastState = false;
  int buttonNumber = 0;
  int mod;
  int actOn;
  bool wasPressed = false;
  bool pressed = false;
  bool serialUsed;
  PinName buttonPin;
  Stream &serial = Serial;
  bool buttonPressed(); //returns true if button press is detected, otherwise returns false
  void initWith(PinName Bpin, int mode = 0, int activeOn = 0, bool useSer = false, Stream &ser = Serial); //used instead of begin()
  /*Bpin: pin used by button; mode: 0 = internal pullup (button pulling down), 1 = internal pulldown (button pulling up), any other value = no internal pullup/down;
  activeOn: 0 = input low active, 1 = input high active (only to be used with mode other than 0 or 1); useSer: true = serial monitoring used, false = serial monitoring not used, default false;
  &ser = serial interface to be used for monitoring, default "Serial"*/
  void waitForPress(); //waits until button is pressed
  bool beingPressed(); //returns true if button is continuously pressed, otherwise false

};

class TempSensor {
  public:
  TempSensor(int sensNum);
  float ntcB;
  float adcU;
  float adcSteps;
  float rawTemp;
  float realTemp;
  float resAt25;
  float adcRealU;
  int sensorNumber = 0;
  bool serialUsed;
  Stream &serial = Serial;
  PinName sensorPin;
  void initWith(PinName sensPin, float adcRefV, float adcBits, float beta, float resAtRoomTemp, bool useSer = false, Stream &ser = Serial);
  float read();

};

class CurrentSensor {
  public:
  CurrentSensor(int sensNum);
  float rawCurrent;
  float adcSteps;
  float adcR;
  float actualCurrent;
  float sensorResistance;
  float sensorVoltPerVolt;
  int sensorNumber = 0;
  bool serialUsed;
  Stream &serial = Serial;
  PinName currentPin;
  void initWith(PinName currPin, float sensR, float sensVpV, float adcBits, float adcRange, bool useSer = false, Stream &ser = Serial);
  float read();

};

class VoltageSensor {
  public:
  VoltageSensor(int sensNum);
  float rawVoltage;
  float adcSteps;
  float adcR;
  float actualVoltage;
  float sensorVoltPerVolt;
  int sensorNumber;
  bool serialUsed;
  Stream &serial = Serial;
  PinName voltagePin;
  void initWith(PinName voltPin, float sensVpV, float adcBits, float adcRange, bool useSer = false, Stream &ser = Serial);
  float read();

};

void toggle(bool &toggled);

float toActualValue(float reading, float adcVolt, float adcBits);

#endif