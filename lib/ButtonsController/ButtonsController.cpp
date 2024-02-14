#include <ButtonsController.h>

ButtonsController::ButtonsController(const uint8_t btn_0, const uint8_t btn_1, const uint8_t btn_2, const uint8_t btn_3, const uint8_t prog_btn)
{
  p_network = nullptr;
  p_btn0 = new Button(btn_0);
  p_btn1 = new Button(btn_1);
  p_btn2 = new Button(btn_2);
  p_btn3 = new Button(btn_3);
  p_prog_btn = new Button(prog_btn);
}

void ButtonsController::setup(NetworkController *p_network, SleepController *p_sleep)
{
  this->p_network = p_network;
  SwitchButtonCallbacks *p_switchButtonCallbacks = new SwitchButtonCallbacks(p_network);
  p_btn0->setup(p_switchButtonCallbacks);
  p_btn1->setup(p_switchButtonCallbacks);
  p_btn2->setup(p_switchButtonCallbacks);
  p_btn3->setup(p_switchButtonCallbacks);
  Serial.println("Switch Button ready");
  p_prog_btn->setup(new ProgButtonCallbacks(p_sleep));
}

void ButtonsController::loop()
{
  p_btn0->loop();
  p_btn1->loop();
  p_btn2->loop();
  p_btn3->loop();
  p_prog_btn->loop();
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

ProgButtonCallbacks::ProgButtonCallbacks(SleepController *p_sleep)
{
  this->p_sleep = p_sleep;
}

void ProgButtonCallbacks::onPressed(Button *p_button)
{
  Serial.println("Prog Button pressed again");
  p_sleep->sleep();
}

void ProgButtonCallbacks::onLongPressed(Button *p_button)
{
  Serial.println("Prog Button long pressed");
  p_sleep->sleep();
}