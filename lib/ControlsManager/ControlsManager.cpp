#include <ControlsManager.h>

ControlsManager::ControlsManager(const uint8_t btn_0, const uint8_t btn_1, const uint8_t btn_2, const uint8_t btn_3)
{
  p_networkController = nullptr;
  p_btn0 = new Button(btn_0);
  p_btn1 = new Button(btn_1);
  p_btn2 = new Button(btn_2);
  p_btn3 = new Button(btn_3);
}

void ControlsManager::setup(NetworkController *pNetworkController)
{
  p_networkController = pNetworkController;
  p_btn0->setup(new SwitchButtonCallbacks(p_networkController));
  p_btn1->setup(new SwitchButtonCallbacks(p_networkController));
  p_btn2->setup(new SwitchButtonCallbacks(p_networkController));
  p_btn3->setup(new SwitchButtonCallbacks(p_networkController));
  Serial.println("Switch Button ready");
}

void ControlsManager::loop()
{
  p_btn0->loop();
  p_btn1->loop();
  p_btn2->loop();
  p_btn3->loop();
}

SwitchButtonCallbacks::SwitchButtonCallbacks(NetworkController *p_networkController)
{
  this->p_networkController = p_networkController;
}

void SwitchButtonCallbacks::onPressed(Button *p_button)
{
  Serial.println("Switch Button pressed");
  p_networkController->publishButtonPressed(p_button->pin);
}

void SwitchButtonCallbacks::onLongPressed(Button *p_button)
{
  Serial.println("Switch Button long pressed");
  p_networkController->publishButtonLongPressed(p_button->pin);
}
