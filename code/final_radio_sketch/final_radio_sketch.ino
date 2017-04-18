/* RF24 Audio Library TMRh20 2014

Audio transmission sketch for simple one-to-one audio streaming, credit to TMRh20 for his RF24 Audio Library
-Noah Thurston

Default Pin Selections:
Speaker: pins 9,10 on UNO, Nano,  pins 11,12 on Mega 2560
Input/Microphone: Analog pin A0 on all boards

CE: Pin 7
CS: Pin 8
Transmit button: Pin A1
VolumeUp button: Pin A2
VolumeDn button: Pin A3
Remote Transmission: Pin A4

*/


#include <RF24.h>
#include <SPI.h>
#include <RF24Audio.h>
#include <userConfig.h>

#define SAMPLE_RATE 44000
#define RF_SPEED RF24_2MBPS
#define ANALOG_PIN A0 

RF24 radio(7,8);    // Set radio up using pins 7 (CE) 8 (CS)
RF24Audio rfAudio(radio,0); // Set up the audio using the radio, and set to radio number 0.
                                // Setting the radio number is only important if one-to-one communication is desired
        // in a multi-node radio group. See the privateBroadcast() function.

void setup() {      
  // The only thing to do is initialize the library.
  rfAudio.begin();    
}

void loop() {
  
  // Audio playback and button handling is all managed internally.
  // In this example, the radio is controlled by external buttons, so there is nothing to do here
  
}





/* Documentation and References:

References:
All Library documentation: http://tmrh20.github.io/
New (2014) RF24 Audio Library: https://github.com/TMRh20/RF24Audio
Optimized (2014) RF24 Lib Source Code: https://github.com/TMRh20/RF24 
Optimized (2014) RF24 Network Lib: https://github.com/TMRh20/RF24Network

*/
