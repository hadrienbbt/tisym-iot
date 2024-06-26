#include <NetworkController.h>
#include <SleepController.h>
#include <OTAController.h>
#include <ButtonsController.h>
#ifdef CAMERA
#include <CameraController.h>
#endif

#include "headers.h"

const uint8_t bssid[] = WIFI_BSSID;

NetworkController *p_network = new NetworkController(WIFI_SSID, WIFI_PWD, GATEWAY, SUBNET, DNS, STATIC_IP, bssid, WIFI_CHANNEL, MQTT_SERVER, MQTT_USER, MQTT_PWD, MQTT_PORT, PROG_LED, CHIP_ID);
SleepController *p_sleep = new SleepController(BUTTON_PIN_BITMASK, BTN_0, BTN_1, BTN_2, BTN_3, PROG_BTN);
ButtonsController *p_buttons = new ButtonsController(BTN_0, BTN_1, BTN_2, BTN_3, PROG_BTN);
OTAController *p_ota = new OTAController();

#ifdef CAMERA
CameraController *p_camera = new CameraController();
#endif

void setup()
{
  Serial.begin(115200);
  pinMode(PROG_LED, OUTPUT);
  digitalWrite(PROG_LED, LOW);

  p_network->setup();
  if (SLEEP)
  {
    p_sleep->setup(p_network);
  }
  p_ota->setup();
  p_buttons->setup(p_network, p_sleep);
  digitalWrite(PROG_LED, HIGH);

#ifdef CAMERA
  p_camera->setup(p_network);
#endif
}

void loop()
{
  p_network->loop();
  p_ota->loop();
  p_buttons->loop();
#ifdef CAMERA
  p_camera->loop();
#endif
}
