#include <ControlsManager.h>

ControlsManager::ControlsManager()
{
  p_networkController = nullptr;
  p_switchBtn = new Button(SWITCH_BTN);
}

void ControlsManager::setup(NetworkController *pNetworkController)
{
  p_networkController = pNetworkController;
  p_switchBtn->setup();
  p_switchBtn->setCallbacks(new SwitchButtonCallbacks(pNetworkController));
  Serial.println("Switch Button ready");
}

void ControlsManager::loop()
{
  p_switchBtn->loop();
}

SwitchButtonCallbacks::SwitchButtonCallbacks(NetworkController *pNetworkController)
{
  p_networkController = pNetworkController;
}

void SwitchButtonCallbacks::onPressed(Button *pButton)
{
  Serial.println("Switch Button pressed");
  p_networkController->publishButtonPressed();
}

void SwitchButtonCallbacks::onLongPressed(Button *pButton)
{
  Serial.println("Switch Button long pressed");
  p_networkController->publishButtonLongPressed();
}
