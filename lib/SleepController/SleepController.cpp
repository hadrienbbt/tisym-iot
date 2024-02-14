#include "SleepController.h"

SleepController::SleepController(const uint64_t mask, const uint8_t btn_0, const uint8_t btn_1, const uint8_t btn_2, const uint8_t btn_3, const uint8_t prog_btn)
{
  this->mask = mask;
  this->btn_0 = btn_0;
  this->btn_1 = btn_1;
  this->btn_2 = btn_2;
  this->btn_3 = btn_3;
  this->prog_btn = prog_btn;
}

void SleepController::setup(NetworkController *p_network)
{
  uint64_t GPIO_reason_pow = esp_sleep_get_ext1_wakeup_status();
  double GPIO_reason = log(GPIO_reason_pow) / log(2);
  if (GPIO_reason == btn_0 || GPIO_reason == btn_1 || GPIO_reason == btn_2 || GPIO_reason == btn_3)
  {
    Serial.println("\nGPIO that triggered the wake up: GPIO ");
    Serial.println(GPIO_reason, 0);
    p_network->publishButtonPressed(GPIO_reason);
    sleep();
  }
  if (GPIO_reason == prog_btn)
  {
    Serial.println("\nGPIO 9: starting OTA process...");
    Serial.println("OTA config starting...");
    return;
  }
  Serial.println("Not awake due to GPIO");
  sleep();
}

void SleepController::sleep()
{
  Serial.println("Going to sleep...\n");
#ifdef ESP32
  esp_sleep_enable_ext1_wakeup(mask, ESP_EXT1_WAKEUP_ANY_HIGH);
  esp_deep_sleep_start();
#endif
#ifdef ESP8266
  ESP.deepSleep(0);
#endif
}