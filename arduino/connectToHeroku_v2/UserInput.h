#ifndef USERINPUT_H
#define USERINPUT_H

#include "Arduino.h"
#include "HotTubGlobals.h"
#include <Bounce.h>
#include <SoftwareSerial.h>

void InitUserInput(void);

void GetButtonStates(HotTub *ht);

void GetTemp(HotTub *ht);

#endif
