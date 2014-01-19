#include "RealtimeControl.h"

long controlInterval = 100;            //10 HZ loop

char tempError = 3; //± bounds for the temperature hysteresis in degrees F

void InitRealtimeControl()
{
  // DO STUFF
}

void SetHeater(HotTub *ht)
{
  unsigned long currentMillis = millis();
  static long previousMillis = 0;
  
  if(currentMillis - previousMillis > controlInterval) 
  {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   
    //If the heater is enabled
    if(ht->heaterEnabled)
    {
      //Regulate the heater to meet the temp setpoint
      if(ht->currentTemp >= ht->setTemp + tempError)
      {
        ht->heaterOn = 0;
      }
      else if(ht->currentTemp <= ht->setTemp + tempError)
      {
        ht->heaterOn = 1;
      }
    }
  }
}
