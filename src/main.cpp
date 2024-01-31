#include <NetworkController.h>
#include <ControlsManager.h>

#include "headers.h"

#define SLEEP true

const uint8_t bssid[] = WIFI_BSSID;

NetworkController *p_networkController = new NetworkController(WIFI_SSID, WIFI_PWD, GATEWAY, SUBNET, DNS, IP, bssid, WIFI_CHANNEL, MQTT_SERVER, MQTT_USER, MQTT_PWD, MQTT_PORT);
ControlsManager *p_controlsManager = new ControlsManager();

void setup()
{
  Serial.begin(115200);
  p_networkController->setup(SLEEP);

  p_controlsManager->setup(p_networkController);
}

void loop()
{
  p_networkController->loop();
  p_controlsManager->loop();
}
