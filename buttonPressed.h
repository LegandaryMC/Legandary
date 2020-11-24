#ifndef buttonPressed.h
#define buttonPressed.h

enum {WAITING = 0, PRESSED, HELD, RELEASED};

#define SECONDS 1000000
#define MILLISECONDS 1000
#define MICROSECONDS 1

#if (ARDUINO >=100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class menuButton {
  public:
    void init();
    bool pressed();
    menuButton(int pin);
    void SetStateAndTime(byte S, unsigned long T);
    void onHold(void (*HOLD)());
    float GetHeldTime(float divisor);
    byte checkButton(byte _buttonPin);

  private:
    unsigned long debounceDelay;
    unsigned long lastDebounceTime;
    int lastButtonState;
    int buttonState;
    int pinNumber;
    bool State, lastState;
    unsigned long onTime, holdTime, heldTime, DBTime, DBInterval, RO_Time;//, DubPTime;
    byte _P;
    byte ButtonState;
    void (*F_on)();
    void (*F_Don)();
    void (*F_hold)();
    void (*F_off)();
};
#endif
