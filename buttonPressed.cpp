#include "buttonPressed.h"

unsigned long debounceDelay = 50;
unsigned long lastDebounceTime = 0;

int lastButtonState = LOW;
int buttonState;
int pinNumber;

bool State, lastState;
unsigned long onTime, holdTime, heldTime, DBTime, DBInterval, RO_Time;//, DubPTime;
byte _P;
byte ButtonState;

menuButton::menuButton(int pin) {
  pinNumber = pin;
}

void menuButton::init() {
  pinMode(pinNumber, INPUT);
}

bool menuButton::pressed() {
  int reading = digitalRead(pinNumber);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {    
    if (reading != buttonState) {
      buttonState = reading;
      
      if (buttonState == HIGH) {
        return true;
      }
    }
  }  
  lastButtonState = reading;

  return false;
}

float menuButton::GetHeldTime(float divisor = SECONDS) {
  if (divisor > 0)
    return heldTime / divisor;
  else
    return -1;
}

void menuButton::SetStateAndTime(byte S = HIGH, unsigned long T = 500) {
  State = S; 
  lastState = !State; 
  holdTime = _P ? (T * 1000) : T;
}

byte menuButton::checkButton(byte _buttonPin){
  byte _button;
  ButtonState = WAITING;
  _button = digitalRead(_buttonPin);
  
  if (_button == State && lastState == !State)
  {
    // record time
    DBTime = _P ? micros() : millis();
    onTime = DBTime;
  
    lastState = State;

    // Button was pressed
    ButtonState = PRESSED;
  }

  if ((_P ? micros() : millis()) - DBTime  >= DBInterval)
  {
    heldTime = 0;

    if (_button == State && lastState == State)
    {
      
      RO_Time = (_P ? micros() : millis());
      if (RO_Time < onTime)
        onTime = 0;

      if ( (heldTime = (RO_Time - onTime)) >= (holdTime - DBInterval)) // 1 second is 1,000 milliseconds or 1,000,000 microseconds
      {
        ButtonState = HELD;
      }
    }

    if (_button == !State && lastState == State)
    {
      ButtonState = RELEASED;
      lastState = !State; 
    }
  }
  return ButtonState;
}
