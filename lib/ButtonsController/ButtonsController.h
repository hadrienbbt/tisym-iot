#include <NetworkController.h>
#include <SleepController.h>
#include <Button.h>

#ifndef BUTTONS_CONTROLLER_H
#define BUTTONS_CONTROLLER_H

class ButtonsController
{
public:
  NetworkController *p_network;
  Button *p_btn0;
  Button *p_btn1;
  Button *p_btn2;
  Button *p_btn3;
  Button *p_prog_btn;

  ButtonsController(const uint8_t btn_0, const uint8_t btn_1, const uint8_t btn_2, const uint8_t btn_3, const uint8_t prog_btn);
  void setup(NetworkController *p_network, SleepController *p_sleep);
  void loop();
};

class SwitchButtonCallbacks : public ButtonCallbacks
{
  NetworkController *p_network;

public:
  SwitchButtonCallbacks(NetworkController *p_network);
  void onPressed(Button *p_button);
  void onLongPressed(Button *p_button);
};

class ProgButtonCallbacks : public ButtonCallbacks
{
  SleepController *p_sleep;

public:
  ProgButtonCallbacks(SleepController *p_sleep);
  void onPressed(Button *p_button);
  void onLongPressed(Button *p_button);
};

#endif