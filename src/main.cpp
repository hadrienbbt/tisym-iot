#include <NetworkController.h>
#include <SleepController.h>
#include <ButtonsController.h>

#include "headers.h"

const uint8_t bssid[] = WIFI_BSSID;

NetworkController *p_networkController = new NetworkController(WIFI_SSID, WIFI_PWD, GATEWAY, SUBNET, DNS, IP, bssid, WIFI_CHANNEL, MQTT_SERVER, MQTT_USER, MQTT_PWD, MQTT_PORT);
SleepController *p_sleepController = new SleepController(BUTTON_PIN_BITMASK);
ButtonsController *p_buttonsController = new ButtonsController(BTN_0, BTN_1, BTN_2, BTN_3);

void setup()
{
  Serial.begin(115200);
  p_networkController->setup();
  if (SLEEP)
  {
    p_sleepController->setup(p_networkController);
  }
  p_buttonsController->setup(p_networkController);
}

void loop()
{
  p_networkController->loop();
  p_buttonsController->loop();
}
