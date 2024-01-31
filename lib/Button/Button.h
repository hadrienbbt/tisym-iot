#include <Arduino.h>

#ifndef BUTTON_H
#define BUTTON_H

class ButtonCallbacks;

class Button
{
  int pin;
  ButtonCallbacks *m_pButtonCallbacks;
  bool isPressed;
  bool isReleased;
  bool isHeld;
  unsigned long pressedAt;
  unsigned long releasedAt;
  unsigned long heldAt;
  int lastState;
  int state;
  unsigned long lastDebounceTime;
  unsigned long debounceDelay;
  unsigned long longPressDelay;

public:
  Button(int pin);
  void setup();
  void loop();
  void setCallbacks(ButtonCallbacks *pCallbacks);
  bool getIsPressed();
  bool getIsReleased();
  bool getIsHeld();
  unsigned long getPressedAt();
  unsigned long getReleasedAt();
  unsigned long getHeldAt();
  int getState();
};

class ButtonCallbacks
{
public:
  virtual void onPressed(Button *pButton);
  virtual void onLongPressed(Button *pButton);
};

#endif