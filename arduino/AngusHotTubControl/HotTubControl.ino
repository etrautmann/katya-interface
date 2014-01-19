#include <Bounce.h>
#include <SoftwareSerial.h>
#include "HotTubGlobals.h"
#include "UserInput.h"
#include "UserInterface.h"
#include "RealtimeControl.h"

static HotTub ht;

//SETUP
void setup() 
{

  // Initialize hot tub state variables
  ht.setTemp = 100;
  ht.currentTemp = 100;
  ht.heaterEnabled = 0;
  ht.heaterOn = 0;
  ht.serverConnected = 0;
  ht.tempUpHit = 0;
  ht.tempDownHit = 0;
  ht.heaterEnableHit = 0;
  ht.jetsOnHit = 0;
  ht.lastTempUpHit = 0;
  ht.lastTempDownHit = 0;
  ht.lastHeaterEnableHit = 0;
  ht.lastJetsOnHit = 0;
  
  //Init user inputs
  InitUserInput();

  //Init user interface
  InitUserInterface();
  
  //Init user interface
  InitRealtimeControl();
}
//WAITING FOR ACTION
void loop()
{

  //======================================================
  // READ USER INPUTS. AFAP
    // Read button states
    GetButtonStates(&ht);
    // Read current temp
    GetTemp(&ht);
    
    // Update State Variables
    if (ht.tempUpHit == LOW && ht.lastTempUpHit != ht.tempUpHit)
    {
      ht.setTemp++;
    }
    else if (ht.tempDownHit == LOW && ht.lastTempDownHit != ht.tempDownHit) 
    {
      ht.setTemp--;
    }
  
  //======================================================
  //CHECK SERVER INPUTS. 0.2HZ LOOP
    //IF DISCONNECTED
      //IF JUST CONNECTED
        //DOCUMENT USER INPUT STATE
      //ATTEMPT CONNECTION. 0.1HZ LOOP
    //IF CONNECTED
      //IF JUST DISCONNECTED && NO USER INPUT DURING DISCONNECT
        //PULL SERVER INPUTS
        //UPDATE STATE VARIABLES
      //ELSE
        //PUSH USER INPUTS
  //======================================================                
  //REALTIME CONTROLLER. 10HZ LOOP
  SetHeater(&ht);
  //======================================================
    
  //UPDATE USER INFTERFACE. 10Hz LOOP
  UpdateUserInterface(&ht);  
}


