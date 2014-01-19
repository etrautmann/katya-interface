#include "serverInterface.h"
#include <SPI.h>
#include <WiFi.h>

boolean debug = true;

//================================================================================
void parseReturnCsv(WiFiClient client, HotTub *ht) {
//  Serial.println("Parse CSV");
//  Serial.println(client.available()); 
  
  
  if (client.available()) {
    
    //read in entire request
    String currentLine = "";
    while (client.available()) {
      char inChar = client.read();
      currentLine += inChar; 
    }
    
    if (debug) {
      Serial.println("String: ====================================================");
      Serial.println(currentLine);
      Serial.println("============================================End String: ");
      Serial.println();
    }
    
    int startPos = currentLine.indexOf("\r\n\r\n");
    currentLine = currentLine.substring(startPos+4);

    //    Serial.println("startPos");
    //    Serial.println(startPos);
    if (debug) {
      Serial.println("Substring: +++++++++++++++++++++++++++++++++");
      Serial.println(currentLine);
      Serial.println("+++++++++++++++++++++++++++++++++ end subtring: ");
      Serial.println();
    }
    
    // now begin parsing 
    startPos = currentLine.indexOf(',');
    String parseVal1 = currentLine.substring(0,startPos);
    String parseVal2 = currentLine.substring(startPos+1);

    Serial.print("parseVal1:   ");
    Serial.print(parseVal1);
    Serial.print("    parseVal2:   ");
    Serial.print(parseVal2);
    Serial.println();

    ht->setTemp = parseVal1.toInt();
    Serial.print("set temp:  ");
    Serial.println(ht->setTemp);

    if (parseVal2 == "1")
    {
      ht->heaterOn = true;
    }
    else {
      ht->heaterOn = false;
    }

    Serial.print("heater on:  ");
    Serial.println(ht->heaterOn);  
    
    client.flush();
  }
  
  
}


//================================================================================
void parseReturnJson(WiFiClient client, HotTub *ht) {
  
  if (client.available()) {
    String currentLine = "";
    while (client.available()) {
      char inChar = client.read();
      currentLine += inChar; 
    }
    Serial.println("String: ====================================================");
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
