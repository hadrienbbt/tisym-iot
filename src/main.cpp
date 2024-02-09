#include <NetworkController.h>
#include <ControlsManager.h>

#include "headers.h"

const uint8_t bssid[] = WIFI_BSSID;

NetworkController *p_networkController = new NetworkController(WIFI_SSID, WIFI_PWD, GATEWAY, SUBNET, DNS, IP, bssid, WIFI_CHANNEL, MQTT_SERVER, MQTT_USER, MQTT_PWD, MQTT_PORT);
ControlsManager *p_controlsManager = new ControlsManager(BTN_0, BTN_1, BTN_2, BTN_3);

void setupThenSleep()
{
  uint64_t GPIO_reason_pow = esp_sleep_get_ext1_wakeup_status();
  double GPIO_reason = log(GPIO_reason_pow) / log(2);
  if (GPIO_reason > 9)
  {
    p_networkController->setup();

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
  esp_sleep_enable_ext1_wakeup(BUTTON_PIN_BITMASK, ESP_EXT1_WAKEUP_ANY_HIGH);
  esp_deep_sleep_start();
#endif
#ifdef ESP8266
  ESP.deepSleep(0);
#endif
}

void setup()
{
  Serial.begin(115200);
  if (SLEEP)
  {
    setupThenSleep();
  }
  p_networkController->setup();
  p_controlsManager->setup(p_networkController);
}

void loop()
{
  p_networkController->loop();
  p_controlsManager->loop();
}
