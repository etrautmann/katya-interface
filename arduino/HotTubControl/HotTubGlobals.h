#ifndef HOTTUBGLOBALS_H
#define HOTTUBGLOBALS_H

#include "Arduino.h"
#include <Bounce.h>
//define buttons for I/O

#define B_TEMP_UP 2
#define B_TEMP_DOWN 3
#define B_HEATER_ENABLE 5
#define B_JETS_ON 6
#define LED_PIN 13

#define DISPLAY_RX_PIN 7
#define DISPLAY_TX_PIN 8

//Define hot tub state struct
typedef struct HotTubs{
   int  setTemp;
   int  currentTemp;
   boolean  heaterEnabled;
   boolean  heaterOn;
   boolean  serverConnected;
   boolean  tempUpHit;
   boolean  tempDownHit;
   boolean  heaterEnableHit;
   boolean  jetsOnHit;
   boolean  lastTempUpHit;
   boolean  lastTempDownHit;
   boolean  lastHeaterEnableHit;
   boolean  lastJetsOnHit;
} HotTub;

#endif
