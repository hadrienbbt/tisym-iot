#include "SleepController.h"

SleepController::SleepController(const uint64_t mask)
{
  this->mask = mask;
}

void SleepController::setup(NetworkController *p_networkController)
{
  uint64_t GPIO_reason_pow = esp_sleep_get_ext1_wakeup_status();
  double GPIO_reason = log(GPIO_reason_pow) / log(2);
  if (GPIO_reason > 9)
  {
    Serial.println("\nGPIO that triggered the wake up: GPIO ");
    Serial.println(GPIO_reason, 0);
    p_networkController->publishButtonPressed(GPIO_reason);
  }
  else
  {
    Serial.println("Not awake due to GPIO");
  }
  Serial.println("Going to sleep...\n");
#ifdef ESP32S3
  esp_sleep_enable_ext1_wakeup(mask, ESP_EXT1_WAKEUP_ANY_HIGH);
  esp_deep_sleep_start();
#endif
#ifdef ESP8266
  ESP.deepSleep(0);
#endif
}