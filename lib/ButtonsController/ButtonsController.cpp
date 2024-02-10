#include <ButtonsController.h>

ButtonsController::ButtonsController(const uint8_t btn_0, const uint8_t btn_1, const uint8_t btn_2, const uint8_t btn_3)
{
  p_network = nullptr;
  p_btn0 = new Button(btn_0);
  p_btn1 = new Button(btn_1);
  p_btn2 = new Button(btn_2);
  p_btn3 = new Button(btn_3);
}

void ButtonsController::setup(NetworkController *p_network)
{
  this->p_network = p_network;
  p_btn0->setup(new SwitchButtonCallbacks(p_network));
  p_btn1->setup(new SwitchButtonCallbacks(p_network));
  p_btn2->setup(new SwitchButtonCallbacks(p_network));
  p_btn3->setup(new SwitchButtonCallbacks(p_network));
  Serial.println("Switch Button ready");
}

void ButtonsController::loop()
{
  p_btn0->loop();
  p_btn1->loop();
  p_btn2->loop();
  p_btn3->loop();
}

SwitchButtonCallbacks::SwitchButtonCallbacks(NetworkController *p_network)
{
  this->p_network = p_network;
}

void SwitchButtonCallbacks::onPressed(Button *p_button)
{
  Serial.println("Switch Button pressed");
  p_network->publishButtonPressed(p_button->pin);
}

void SwitchButtonCallbacks::onLongPressed(Button *p_button)
{
  Serial.println("Switch Button long pressed");
  p_network->publishButtonLongPressed(p_button->pin);
}
