#include <NetworkController.h>
#include <Button.h>

#ifndef CONTROLS_MANAGER_H
#define CONTROLS_MANAGER_H

#define SWITCH_BTN 10

class ControlsManager
{
public:
  NetworkController *p_networkController;
  Button *p_switchBtn;

  ControlsManager();
  void setup(NetworkController *p_networkController);
  void loop();
};

class SwitchButtonCallbacks : public ButtonCallbacks
{
  NetworkController *p_networkController;

public:
  SwitchButtonCallbacks(NetworkController *p_networkController);
  void onPressed(Button *pButton);
  void onLongPressed(Button *pButton);
};

#endif