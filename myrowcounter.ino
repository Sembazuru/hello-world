#include <LiquidCrystal.h>

const int button1Pin = A1;  // pushbutton 1 pin
const int button2Pin = A2;  // pushbutton 2 pin
const int ledPin =  13;    // LED pin

voidsetup(){
// Set up the pushbutton pins to be an input:
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);

  // Set up the LED pin to be an output:
  pinMode(ledPin, OUTPUT);      
}

voidloop(){

int button1State, button2State;  // variables to hold the pushbutton states

  // Since a pushbutton has only two states (pushed or not pushed),
  // we've run them into digital inputs. To read an input, we'll
  // use the digitalRead() function. This function takes one
  // parameter, the pin number, and returns either HIGH (5V)
  // or LOW (GND).

  // Here we'll read the current pushbutton states into
  // two variables:

  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
  
  // A == B means "EQUIVALENT". This is true if both sides are the same.
  // A && B means "AND". This is true if both sides are true.
  // A || B means "OR". This is true if either side is true.
  // !A means "NOT". This makes anything after it the opposite (true or false).
  
   if (button1State == LOW)  // if we're pushing button 1

  {
    digitalWrite(ledPin, HIGH);  // turn the LED on
  }
  else
  {
    digitalWrite(ledPin, LOW);  // turn the LED off
  }
  
    if (button2State == LOW)  // if we're pushing button 2

  {
    digitalWrite(ledPin, HIGH);  // turn the LED on
  }
  else
  {
    digitalWrite(ledPin, LOW);  // turn the LED off
}


/**
* Button processing. Ideally button should take care of powering up/down, resetting and increasing the counter value.
*/
void _checkButtonState() {
  byte buttonState = digitalRead(BUTTON_PIN);

  if( buttonState == HIGH ) { // Button is pressed
    if( buttonLastState != buttonState ) { // This is the start of "pressed" condition, store the time of event
      buttonDownTimestamp = millis();
    } else { // Button is pressed for some time now
      if(powerMode == PMODE_NORMAL) {
        buttonDownDuration = millis() - buttonDownTimestamp;
      
        if(buttonDownDuration >= TIME_UNTIL_POWER_CYCLE*1000) { // Super-looooong press, go to stand-by while the button is still pressed
          if(powerState == ON) {
              powerState = OFF;
          } else {
            powerState = ON;
          }
          
          powerMode = PMODE_SWITCHING;
          buttonDownDuration = buttonDownTimestamp = 0;
          return; 
        } else if(powerState == ON && buttonDownDuration >= TIME_UNTIL_RESET*1000) { // Long press, reset the counter
          counter = 0;
          _setValue(counter);
        }
      }
    }
  } else {
    if( buttonLastState != buttonState ) { // Button is released
      buttonDownDuration = millis() - buttonDownTimestamp;
      if( powerState == ON ) {
        if(buttonDownDuration < TIME_UNTIL_RESET*1000) { // Short press, increase counter value
          counter++;
          _setValue(counter);
        }
        
        buttonDownDuration = buttonDownTimestamp = 0;
      }
      powerMode = PMODE_NORMAL;
    }
  }

  buttonLastState = buttonState;
}
