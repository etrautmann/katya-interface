#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "Arduino.h"
#include "HotTubGlobals.h"
#include <SoftwareSerial.h>

void InitUserInterface(void);

void UpdateUserInterface(HotTub *ht);

void clearDisplay(void);

void setBrightness(byte value);

void setDecimals(byte decimals);

#endif
