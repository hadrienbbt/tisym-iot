#include <NetworkController.h>
#include <Button.h>

#ifndef CONTROLS_MANAGER_H
#define CONTROLS_MANAGER_H

class ControlsManager
{
public:
  NetworkController *p_networkController;
  Button *p_btn0;
  Button *p_btn1;
  Button *p_btn2;
  Button *p_btn3;

  ControlsManager(const uint8_t btn_0, const uint8_t btn_1, const uint8_t btn_2, const uint8_t btn_3);
  void setup(NetworkController *p_networkController);
  void loop();
};

class SwitchButtonCallbacks : public ButtonCallbacks
{
  NetworkController *p_networkController;

public:
  SwitchButtonCallbacks(NetworkController *p_networkController);
  void onPressed(Button *p_button);
  void onLongPressed(Button *p_button);
};

#endif