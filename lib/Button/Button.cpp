#include <Button.h>

Button::Button(int pin)
{
  this->pin = pin;
  this->m_pButtonCallbacks = nullptr;
  this->isPressed = false;
  this->isReleased = false;
  this->isHeld = false;
  this->lastState = LOW;
  this->state = LOW;
  this->lastDebounceTime = 0;
  this->debounceDelay = 50;
  this->longPressDelay = 1000;
}

void Button::setup(ButtonCallbacks *pCallbacks)
{
  pinMode(this->pin, INPUT_PULLUP);
  this->m_pButtonCallbacks = pCallbacks;
}

// listen for long press and if the press is released before the long press delay, call onPressed method instead. don't call 2 at the same time
void Button::loop()
{
  int reading = digitalRead(this->pin);
  if (reading != this->lastState)
  {
    this->lastDebounceTime = millis();
  }

  if (reading != this->state && (millis() - this->lastDebounceTime) > this->debounceDelay)
  {
    this->state = reading;
    if (this->state == HIGH)
    {
      this->isPressed = true;
      this->pressedAt = millis();
    }
    else
    {
      this->isReleased = true;
      this->releasedAt = millis();
    }
  }

  this->lastState = reading;

  if (this->isPressed)
    this->isPressed = false;

  if (this->isReleased)
  {
    this->isReleased = false;
    if (this->m_pButtonCallbacks == nullptr)
      return;
    if ((millis() - this->pressedAt) > this->longPressDelay)
      this->m_pButtonCallbacks->onLongPressed(this);
    else
      this->m_pButtonCallbacks->onPressed(this);
  }
}

bool Button::getIsPressed()
{
  return this->isPressed;
}

bool Button::getIsReleased()
{
  return this->isReleased;
}

bool Button::getIsHeld()
{
  return this->isHeld;
}

unsigned long Button::getPressedAt()
{
  return this->pressedAt;
}

unsigned long Button::getReleasedAt()
{
  return this->releasedAt;
}

unsigned long Button::getHeldAt()
{
  return this->heldAt;
}

int Button::getState()
{
  return this->state;
}

void ButtonCallbacks::onPressed(Button *pButton)
{
#ifdef ESP32S3
  log_d("ButtonCallbacks", ">> onPressed(): Default");
  log_d("ButtonCallbacks", "Button: %s", Button::pin.c_str());
  log_d("ButtonCallbacks", "<< onPressed()");
#endif
}

void ButtonCallbacks::onLongPressed(Button *pButton)
{
#ifdef ESP32S3
  log_d("ButtonCallbacks", ">> onLongPressed(): Default");
  log_d("ButtonCallbacks", "Button: %s", Button::pin.c_str());
  log_d("ButtonCallbacks", "<< onLongPressed()");
#endif
}