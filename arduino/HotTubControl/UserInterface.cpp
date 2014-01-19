#include "UserInterface.h"

char displayString[10];
// will store last time LED was updated
long displayInterval = 100;            //10 HZ loop

SoftwareSerial s7s(DISPLAY_RX_PIN, DISPLAY_TX_PIN);

void InitUserInterface()
{
  // serial for comms with 7-segment display

  s7s.begin(9600);
  clearDisplay();

  //Setup the LED
  pinMode(LED_PIN,OUTPUT);
}


void UpdateUserInterface(HotTub *ht)
{
  unsigned long currentMillis = millis();
  static long previousMillis = 0;  

  if(currentMillis - previousMillis > displayInterval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   

    if (ht->tempUpHit == LOW){
      ht->setTemp++;
    }
    else if (ht->tempDownHit == LOW) {
      ht->setTemp--;
    }

    sprintf(displayString, "%4d", ht->setTemp);

    // This will output the tempString to the S7S
    s7s.print(displayString);
    setDecimals(0b00000000);  // Sets digit 3 decimal on
  }

  //========================================================================
  // Turn on or off the LED for debugging buttons/shits and giggles
  //  if (( value1 == LOW) || ( value2 == LOW) || ( value3 == LOW) || ( value4 == LOW))  {
  if (ht->tempUpHit  == LOW)   {
    digitalWrite(LED_PIN, HIGH );
  } 
  else {
    digitalWrite(LED_PIN, LOW );
  }
}
//========================================================================
// 7-segment display functions
// #TODO - move these to library
// Send the clear display command (0x76)
//  This will clear the display and reset the cursor
void clearDisplay()
{
  s7s.write(0x76);  // Clear display command
}

// Set the displays brightness. Should receive byte with the value
//  to set the brightness to
//  dimmest------------->brightest
//     0--------127--------255
void setBrightness(byte value)
{
  s7s.write(0x7A);  // Set brightness command byte
  s7s.write(value);  // brightness data byte
}

// Turn on any, none, or all of the decimals.
//  The six lowest bits in the decimals parameter sets a decimal 
//  (or colon, or apostrophe) on or off. A 1 indicates on, 0 off.
//  [MSB] (X)(X)(Apos)(Colon)(Digit 4)(Digit 3)(Digit2)(Digit1)
void setDecimals(byte decimals)
{
  s7s.write(0x77);
  s7s.write(decimals);
}


