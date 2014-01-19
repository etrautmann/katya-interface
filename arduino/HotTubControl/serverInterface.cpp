#include "serverInterface.h"
#include <SPI.h>
#include <WiFi.h>
















//================================================================================
void parseReturnJson(WiFiClient client, HotTub *ht) {
  
  if (client.available()) {
    String currentLine = "";
    while (client.available()) {
      char inChar = client.read();
      currentLine += inChar; 
    }
    Serial.println("================================================================= RETURNED FROM SERVER");
    Serial.println(currentLine);
    Serial.println("End String: ");
    Serial.println();


    int startPos = currentLine.indexOf('{');
    currentLine = currentLine.substring(startPos);

    Serial.println("Substring: ===========");
    Serial.println(currentLine);
    Serial.println("End subtring: ");
    Serial.println();

//
//    currentLine.toCharArray(jsonBuff, currentLine.length()+1);
//
//    Serial.println("char array: ===========");
//    Serial.println(jsonBuff);
//    Serial.println("end char array: ");
//    Serial.println();

//    Serial.println("==============================");
//    delay(500);
//    jsonObject = aJson.parse(jsonBuff);
//    heaterOn = aJson.getObjectItem(jsonObject , "heaterOn");
//    setTemp = aJson.getObjectItem(jsonObject , "setTemp");
//    Serial.println(heaterOn->valuestring);
//    Serial.println(setTemp->valuestring);
//    delay(500);
  }
}
