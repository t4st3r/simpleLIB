#ifndef simpleLIB_h
#define simpleLIB_h

#include "Arduino.h"
#include <EEPROM_SPI_WE.h>

class TempPreset {
  public:
  TempPreset(int presNum); //constructor, sets the number ID of preset
  float temp = 0;
  bool serialUsed;
  int memoryAddress = 0;
  int presetNumber = 0;
  Stream *serial;
  bool inUse(int set); //checks if the preset is currently used, set: temperature to be compared with preset temperature, returns true if the temperature of the preset equals the set system temperature
  /*_temp: preset temperature (default 0), addr: address in EEPROM memory (if used, default 0), useSer: use/not use serial monitoring (default false); 
  &ser: serial to be used, HAS TO BE CALLED AS A REFERENCE e.g. &Serial (default null, no serial interface defined)*/
  void initWith(int _temp = 0, int addr = 0, bool useSer = false, Stream *ser = nullptr);
  void saveTo(EEPROM_SPI_WE& mem); //save preset to EEPROM memory at the address that is set through initWith
  void recallFrom(EEPROM_SPI_WE& mem); //load preset from EEPROM memory at the address that is set through initWith
  void setTemperature(float temperature); //change preset temperature to passed temperature value

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
  Stream *serial;
  bool buttonPressed(); //returns true if button press is detected, otherwise returns false
  /*Bpin: pin used by button; mode (default 0): 0 = internal pullup (button pulling down), 1 = internal pulldown (button pulling up), any other value = no internal pullup/down;
  activeOn (default 0): 0 = input low active, 1 = input high active (only to be used with mode other than 0 or 1); useSer (default false): true = serial monitoring used, false = serial monitoring not used;
  &ser = serial interface to be used for monitoring, HAS TO BE CALLED AS A REFERENCE e.g. &Serial (default null, no serial interface defined)*/
  void initWith(PinName Bpin, int mode = 0, int activeOn = 0, bool useSer = false, Stream *ser = nullptr); //used instead of begin()
  void waitForPress(); //waits until button is pressed
  bool beingPressed(); //returns true if button is continuously pressed, otherwise returns false

};

class NTCTempSensor {
  public:
  NTCTempSensor(int sensNum); //constructor, create NTCTempSensor object with number ID
  float ntcB;
  float adcU;
  float adcSteps;
  float rawTemp;
  float realTemp;
  float resAt25;
  float adcRealU;
  float serR;
  int sensorNumber = 0;
  bool serialUsed;
  Stream *serial;
  PinName sensorPin;
  /*sensPin: pin to read voltage from, has to be ADC-capable; adcRefV: ADC reference voltage/voltage range; adcBits: ADC bit count; beta: NTC thermistor beta parameter;
  resAtRoomTemp: thermistor resistance at room temperature (25°C); seriesResistor: pull up resistor value; useSer: serial monitoring enabled/disabled (default false);
  &ser: serial interface used for monitoring, HAS TO BE CALLED AS A REFERENCE e.g. &Serial (default null, no serial interface defined)*/
  void initWith(PinName sensPin, float adcRefV, float adcBits, float beta, float resAtRoomTemp, float seriesResistor, bool useSer = false, Stream *ser = nullptr);
  float read(); //returns measured temperature from sensor in °C

};

class CurrentSensor {
  public:
  CurrentSensor(int sensNum);
  float rawCurrent;
  float adcSteps;
  float adcU;
  float actualCurrent;
  float sensorResistance;
  float sensorVoltPerVolt;
  int sensorNumber = 0;
  bool serialUsed;
  Stream *serial;
  PinName currentPin;
  /*currPin: pin used for measurement input, pin must be ADC-capable; sensR: sensing resistor resistance; sensVpV: volt/volt value of used current measurement amplifier (usually found in datasheet);
  adcBits: bit count of ADC used for measurement; adcRefV: ADC reference voltage/voltage range; useSer: true = serial monitoring used, false = serial monitoring no used (default false);
  *ser: serial monitoring to be used, HAS TO BE CALLED AS A REFERENCE e.g. &Serial (default null, no serial interface defined)*/
  void initWith(PinName currPin, float sensR, float sensVpV, float adcBits, float adcRefV, bool useSer = false, Stream *ser = nullptr);
  float read(); //returns measured current from sensor in A

};

class VoltageSensor {
  public:
  VoltageSensor(int sensNum);
  float rawVoltage;
  float adcSteps;
  float adcU;
  float actualVoltage;
  float sensorVoltPerVolt;
  int sensorNumber;
  bool serialUsed;
  Stream *serial;
  PinName voltagePin;
  /*voltPin: pin on which to read voltage, pin has to be ADC-capable; sensVpV: volt/volt of voltage measurement, when using resistor divider or a preamplifier for example; adcBits: bit count of ADC used for measurement;
  adcRefV: ADC reference voltage/voltage range; useSer: true = serial monitoring used, false = serial monitoring no used (default false); *ser = serial monitoring to be used, HAS TO BE CALLED AS A REFERENCE e.g. &Serial (default null, no serial interface defined)*/
  void initWith(PinName voltPin, float sensVpV, float adcBits, float adcRefV, bool useSer = false, Stream *ser = nullptr);
  float read();

};

void toggle(bool &toggled); //flips the value of a bool (TRUE to FALSE or FALSE to TRUE), &toggled: bool to be flipped

float toActualValue(float reading, float adcRefV, float adcBits); //converts raw ADC reading to actual voltage value, reading: raw ADC reading; adcRefV: ADC reference voltage/voltage range; adcBits: bit count of ADC used for measurement

#endif