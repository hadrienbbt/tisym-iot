#ifdef ESP32
#include <WiFi.h>
#endif
#ifdef ESP8266
#include <ESP8266WiFi.h>
#endif
#include <MQTT.h>

#ifndef NETWORK_CONTROLLER_H
#define NETWORK_CONTROLLER_H

class NetworkController
{
  const char *ssid;
  const char *password;
  const char *gateway;
  const char *subnet;
  const char *dns;
  const char *ip;
  const uint8_t *bssid;
  int channel;
  const char *mqtt_broker;
  const char *mqtt_user;
  const char *mqtt_password;
  int mqtt_port;
  uint8_t prog_led;
  uint64_t chip_id;

  MQTTClient mqtt;
  WiFiClient wifi;

  void connectWiFi();
  void connectMQTT();

public:
  NetworkController(const char *ssid, const char *password, const char *gateway, const char *subnet, const char *dns, const char *ip, const uint8_t *bssid, int channel, const char *mqtt_broker, const char *mqtt_user, const char *mqtt_password, int mqtt_port, uint8_t prog_led, uint64_t chip_id);
  void setup();
  void loop();
  void disconnect();

  void publishButtonPressed(int pin);
  void publishButtonLongPressed(int pin);
};

#endif