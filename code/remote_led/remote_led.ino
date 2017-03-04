/*
 * Simple sketch to test the nRF24L01 module, the 5V Arduino Pro Mini, 
 * and tmrh20's fork of the RF24 library. 
 * 
 * Each Arduino has an nRF, a button, and an LED, by clicking the button on one,
 * you can turn the LED on or off on both. This code can also be easily modified to allow
 * the button to trigger something other than an LED, like a buzzer or any remote 
 * arduino functionality. 
 * 
 * 
 * Author: Noah Thurston
 * Date: 3/3/17
 * 
 * Code Reference: http://tmrh20.github.io/RF24/GettingStarted_8ino-example.html
 * Wiring Reference: http://arduino-info.wikispaces.com/Nrf24L01-2.4GHz-HowTo
 */

#include <SPI.h>
#include <RF24.h>

//Output in for LED
const int LEDPin = 9;

//Input pin for button
const int buttonPin = 3;

//integer return from reading the button
int buttonResult = 0;

//bools to control whether the button is pushed, or the LED is on
int buttonRead = LOW;
bool LEDOn = false;

//serves as an ID number, between the two radios, allows easy switching between two address
//MUST be unique 0 or 1 for the two radios so the addresses are different
bool radioNumber = 0;

//name the arduino pins being used as an SPI connection to the nRF
RF24 radio(7,8);

//the two possible addresses for the nodes
byte addresses[][6] = {"1Node", "2Node"};

//reads the from the button pin
//returns 0 for no change, 1 if the LED should now be on, -1 if the LED should now be off
int readFromButton();

//update the LED, argument should be 1 for on or -1 for off
void updateLED(int buttonResult);

void setup() {

  //LED and button pin setup
  pinMode(LEDPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  //start a serial monitor
  Serial.begin(115200);
  Serial.println("Press the button to turn the LED on/off");
  
  //begin operation of the nRF chip
  radio.begin();

  //set the power amplifier level; can be MIN, LOW, HIGH, or MAX
  radio.setPALevel(RF24_PA_MAX);

  //open writing and reading pipe using this nodes address and the other address
  if(radioNumber) {
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1, addresses[0]);
  } else {
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1, addresses[1]);
  }

  //start listening for data on the created reading pipe
  radio.startListening();
}


void loop() {  
  //reads the button
  buttonResult = readFromButton();

  //if the button is pressed, sends a message to the other arduino
  if(buttonResult == 1 || buttonResult == -1) {
    //stop and send
    radio.stopListening();
    radio.write(&buttonResult, sizeof(int));
    Serial.println("\nSent update: ");
    Serial.print(buttonResult);
    radio.startListening();
    delay(200);
  } else {

    //if no button input, stop and listen for the other node
    while(radio.available()) {

      //if it finds some data, read it and update the LED
      radio.read(&buttonResult, sizeof(int));
      Serial.println("\nReceived update: ");
      Serial.print("buttonResult");
      updateLED(buttonResult);
    }
  }

} //end of loop

//reads the from the button pin
//returns 0 for no change, 1 if the LED should now be on, -1 if the LED should now be off
int readFromButton() {
  buttonRead = digitalRead(buttonPin);

  //update the LED state if the button reads high
  if(buttonRead == HIGH) {
    if(LEDOn == false){
      LEDOn = true;
      updateLED(1);
      return 1;
    } else {
      LEDOn = false;
      updateLED(-1);
      return -1;
    } 
  } 
  //else return 0 (button was not pressed)
  else {
    return 0;
  }
}

//update the LED, argument should be 1 for on or -1 for off
void updateLED(int buttonResult) {
  if(buttonResult == 1) {
    digitalWrite(LEDPin, HIGH);
  } else if (buttonResult == -1) {
    digitalWrite(LEDPin, LOW);
  }
  return;
}
