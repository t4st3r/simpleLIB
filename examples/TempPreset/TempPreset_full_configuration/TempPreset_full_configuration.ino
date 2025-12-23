#include "simpleLIB.h"
#include <EEPROM_SPI_WE.h>

TempPreset preset(1); //create TempPreset object, assign number ID 1

//EEPROM_SPI_WE eeprom = EEPROM_SPI_WE(PA_4); //Create EEPROM object according to the EEPROM_SPI_WE library, with CS on pin PA4 (uncomment if using EEPROM)

float sysTemp = 20;

bool presetInUse = false;

void setup() {
  Serial.begin(115200);
  preset.initWith(30, 1, true, Serial); //initialize "preset" with temperature 30, memory address 1, using serial "Serial"

}

void loop() {
  presetInUse = preset.inUse(sysTemp); //compare sysTemp to preset temperature
  delay(500);
  preset.setTemperature(35); //set preset temperature to 35
  delay(500);
  //preset.saveTo(eeprom); //save "preset" temperature to "eeprom"
  //preset.recallFrom(eeprom); //retrieve "preset" temperature from "eeprom"
}