#include "UserInput.h"

// Instantiate switch debouncer object

Bounce debouncer1 = Bounce(); 
Bounce debouncer2 = Bounce(); 
Bounce debouncer3 = Bounce(); 
Bounce debouncer4 = Bounce(); 


void InitUserInput()
{
  // Setup the button
  pinMode(B_TEMP_UP,INPUT);
  pinMode(B_TEMP_DOWN,INPUT);
  pinMode(B_HEATER_ENABLE,INPUT);
  pinMode(B_JETS_ON,INPUT);

  // Activate internal pull-up
  digitalWrite(B_TEMP_UP,HIGH);
  digitalWrite(B_TEMP_DOWN,HIGH);
  digitalWrite(B_HEATER_ENABLE,HIGH);
  digitalWrite(B_JETS_ON,HIGH);

  // After setting up the button, setup debouncer
  debouncer1.attach(B_TEMP_UP);
  debouncer2.attach(B_TEMP_DOWN);
  debouncer3.attach(B_HEATER_ENABLE);
  debouncer4.attach(B_JETS_ON);

  debouncer1.interval(5);
  debouncer2.interval(5);
  debouncer3.interval(5);
  debouncer4.interval(5);
 
}

void GetButtonStates(HotTub *ht)
{
  
   // Update the debouncer
  debouncer1.update();
  debouncer2.update();
  debouncer3.update();
  debouncer4.update();

  // Get the update value
   ht->lastTempUpHit = ht->tempUpHit;
   ht->tempUpHit = debouncer1.read();
   ht->lastTempDownHit = ht->tempDownHit;
   ht->tempDownHit = debouncer2.read();
   ht->lastHeaterEnableHit = ht->heaterEnableHit;
   ht->heaterEnableHit = debouncer3.read();
   ht->lastJetsOnHit = ht->jetsOnHit;
   ht->jetsOnHit = debouncer4.read();
}

void GetTemp(HotTub *ht)
{
   //Read Temp 
}
