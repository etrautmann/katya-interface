
#include <aJSON.h>
#include <Bounce.h>
#include <SoftwareSerial.h>

#include <SPI.h>
#include <WiFi.h>
//#include <json_arduino.h>
#include "HotTubGlobals.h"
#include "RealtimeControl.h"
#include "UserInput.h"
#include "UserInterface.h"
#include "serverInterface.h"



static HotTub ht;

//char ssid[] = "SHWAYDAR";    //  your network SSID (name) 
//char pass[] = "typethatpasswordformebaby";    // your network password

// server address:
char server[] = "katyakrunktank.herokuapp.com";

int startPos;
char inChar;
char ssid[] = "799 Seneca";    //  your network SSID (name) 
char pass[] = "welcome123";    // your network password
String currentLine = "";               // string to hold the text from server
char jsonBuff[128];

String parseVal1;
String parseVal2;

char foo[] = "{\"heaterOn\": \"true\", \"setTemp\": \"100\"}";


int status = WL_IDLE_STATUS;

// Initialize the Wifi client library
WiFiClient client;


unsigned long lastConnectionTime = 0;           // last time you connected to the server, in milliseconds
boolean lastConnected = false;                  // state of the connection last time through the main loop
const unsigned long postingInterval = 3*1000;  // delay between updates, in milliseconds


//================================================================================
void setup() {

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

  //Initialize serial and wait for port to open:
  Serial.begin(9600); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    // don't continue:
    while(true);
  } 

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) { 
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(5000);
  } 
  // you're connected now, so print out the status:
  printWifiStatus();
}





//================================================================================
//================================================================================
void loop() {
  
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
  
  
  
  
  // if there's no net connection, but there was one last time
  // through the loop, then stop the client:
  if (!client.connected() && lastConnected) {
    Serial.println();
    Serial.println("disconnecting.");
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    client.stop();
  }

  // if you're not connected, and X seconds have passed since
  // your last connection, then connect again and send data:
  if(!client.connected() && (millis() - lastConnectionTime > postingInterval)) {

    httpRequest();
    // note the time that the connection was made:
    lastConnectionTime = millis();
//    Serial.print("client avail main loop:  ");
//    Serial.println(client.available());
    
    delay(100);
    parseReturnCsv(client, &ht);
    delay(100);
    
    client.flush();  //flush out anything left in buffer for whatever reason

  }

  // store the state of the connection for next time through the loop:
  lastConnected = client.connected();
  
  
  //======================================================                
  //REALTIME CONTROLLER. 10HZ LOOP
  SetHeater(&ht);
  //======================================================
    
  //UPDATE USER INFTERFACE. 10Hz LOOP
  UpdateUserInterface(&ht);  
  
  
}
//================================================================================
//================================================================================





//================================================================================
// this method makes a HTTP connection to the server:
void httpRequest() {
  // if there's a successful connection:
  if (client.connect(server, 80)) {
    Serial.println("connecting...");
    // send the HTTP PUT request:
    client.println("GET /arduino/sync?cur_temp=100 HTTP/1.1");
    client.println("Host: katyakrunktank.herokuapp.com");
    client.println("User-Agent: arduino-wifi");
    client.println("Connection: close");
    client.println();

    
  } 
  else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
    Serial.println("disconnecting.");
    client.stop();
  }
}


//================================================================================
void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

//void parseReturnCsv(HotTub *ht) {
//  
//  if (client.available()) {
//    
//    //read in entire request
//    currentLine = "";
//    while (client.available()) {
//      inChar = client.read();
//      currentLine += inChar; 
//    }
////    Serial.println("String: ====================================================");
////    Serial.println(currentLine);
////    Serial.println("End String: ");
////    Serial.println();
//
//    startPos = currentLine.indexOf("\r\n\r\n");
//    currentLine = currentLine.substring(startPos+4);
//
////    Serial.println("startPos");
////    Serial.println(startPos);
//    Serial.println("Substring: ===========");
//    Serial.println(currentLine);
//    Serial.println("End subtring: ");
//    Serial.println();
//
//    // now begin parsing 
//    startPos = currentLine.indexOf(',');
//    parseVal1 = currentLine.substring(0,startPos);
//    parseVal2 = currentLine.substring(startPos+1);
//
//    Serial.print("parseVal1:   ");
//    Serial.print(parseVal1);
//    Serial.print("    parseVal2:   ");
//    Serial.print(parseVal2);
//    Serial.println();
//    
//    ht->setTemp = parseVal1.toInt();
//    Serial.print("set temp:  ");
//    Serial.println(ht->setTemp);
//    
//    if (parseVal2 == "1")
//    {
//      ht->heaterOn = true;
//    }
//    else {
//      ht->heaterOn = false;
//    }
//      
//    Serial.print("heater on:  ");
//    Serial.println(ht->heaterOn);  
//    
//    Serial.println();
//    Serial.println();
//    Serial.println();
//    Serial.println();
//    Serial.println();
//    Serial.println();
//    Serial.println();
//
//  }
//}














