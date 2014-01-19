#ifndef SERVERINTERFACE_H
#define SERVERINTERFACE_H

#include "Arduino.h"
#include "HotTubGlobals.h"
#include <SPI.h>
#include <WiFi.h>

//void httpRequest(WiFiClient client);
//
//void printWifiStatus();

//void pullStateFromServer(WiFiClient client, HotTub *ht);

void parseReturnJson(WiFiClient client, HotTub *ht); 

//void httpRequest(WiFiClient client, char* server);

//void printWifiStatus();

#endif
