#include <Bounce.h>
#include <SoftwareSerial.h>


// #TODO: add button state detection/hystersis


// setup I/O
// define buttons for I/O
#define BUTTON_PIN1 2
#define BUTTON_PIN2 3
#define BUTTON_PIN3 5
#define BUTTON_PIN4 6
#define LED_PIN 13

// Instantiate switch debouncer object
Bounce debouncer1 = Bounce(); 
Bounce debouncer2 = Bounce(); 
Bounce debouncer3 = Bounce(); 
Bounce debouncer4 = Bounce(); 

// serial for comms with 7-segment display
const int softwareTx = 8;
const int softwareRx = 7;
SoftwareSerial s7s(softwareRx, softwareTx);

unsigned int setPointTemp = 100;
char displayString[10];

long previousMillis = 0;        // will store last time LED was updated
long interval = 100;  

void setup() {
  // Setup the button
  pinMode(BUTTON_PIN1,INPUT);
  pinMode(BUTTON_PIN2,INPUT);
  pinMode(BUTTON_PIN3,INPUT);
  pinMode(BUTTON_PIN4,INPUT);

  // Activate internal pull-up
  digitalWrite(BUTTON_PIN1,HIGH);
  digitalWrite(BUTTON_PIN2,HIGH);
  digitalWrite(BUTTON_PIN3,HIGH);
  digitalWrite(BUTTON_PIN4,HIGH);

  // After setting up the button, setup debouncer
  debouncer1.attach(BUTTON_PIN1);
  debouncer2.attach(BUTTON_PIN2);
  debouncer3.attach(BUTTON_PIN3);
  debouncer4.attach(BUTTON_PIN4);

  debouncer1.interval(5);
  debouncer2.interval(5);
  debouncer3.interval(5);
  debouncer4.interval(5);

  s7s.begin(9600);
  clearDisplay();

  //Setup the LED
  pinMode(LED_PIN,OUTPUT);

}

void loop() {

  //========================================================================
  // update button state
  // Update the debouncer
  debouncer1.update();
  debouncer2.update();
  debouncer3.update();
  debouncer4.update();

  // Get the update value
  int value1 = debouncer1.read();
  int value2 = debouncer2.read();
  int value3 = debouncer3.read();
  int value4 = debouncer4.read();


  //========================================================================
  // update 7-segment display

  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   

    if ( value1 == LOW){
      setPointTemp++;
    }
    else if (value2 == LOW) {
      setPointTemp--;
    }

    sprintf(displayString, "%4d", setPointTemp);

    // This will output the tempString to the S7S
    s7s.print(displayString);
    setDecimals(0b00000000);  // Sets digit 3 decimal on

  }






  //========================================================================
  // Turn on or off the LED for debugging buttons/shits and giggles
//  if (( value1 == LOW) || ( value2 == LOW) || ( value3 == LOW) || ( value4 == LOW))  {
    if ( value1 == LOW)   {
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








