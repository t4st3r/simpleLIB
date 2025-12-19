#ifndef simpleLIB_h
#define simpleLIB_h

#include "Arduino.h"
#include <EEPROM_SPI_WE.h>

class TempPreset {
  public:
  TempPreset();
  float temp = 0;
  bool inUse(int set);
  void setAddress(int addr);
  void initTemp(int _temp);
  void saveTo(EEPROM_SPI_WE& mem);
  void recallFrom(EEPROM_SPI_WE& mem);
  int memoryAddress = 0;
};

class BasicButton {
  public:
  BasicButton();
  int state = false;
  int lastState = false;
  PinName buttonPin;
  bool buttonPressed();
  void initializeWithPin(PinName Bpin); //used instead of begin()

};

class TempSensor {
  public:
  TempSensor();
  float ntcB;
  float adcU;
  float adcB;
  float rawTemp;
  float realTemp;
  float resAt25;
  float adcRealU;
  PinName sensorPin;
  void initWith(float adcRefV, float adcBitCount, float beta, PinName Tpin, float resAtRoomTemp);
  float read();

}

#endif