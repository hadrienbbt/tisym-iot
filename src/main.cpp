#include <NetworkController.h>
#include <SleepController.h>
#include <ButtonsController.h>

#include "headers.h"

const uint8_t bssid[] = WIFI_BSSID;

NetworkController *p_network = new NetworkController(WIFI_SSID, WIFI_PWD, GATEWAY, SUBNET, DNS, STATIC_IP, bssid, WIFI_CHANNEL, MQTT_SERVER, MQTT_USER, MQTT_PWD, MQTT_PORT);
SleepController *p_sleep = new SleepController(BUTTON_PIN_BITMASK);
ButtonsController *p_buttons = new ButtonsController(BTN_0, BTN_1, BTN_2, BTN_3);

void setup()
{
  Serial.begin(115200);
  p_network->setup();
  if (SLEEP)
  {
    p_sleep->setup(p_network);
  }
  p_buttons->setup(p_network);
}

void loop()
{
  p_network->loop();
  p_buttons->loop();
}
