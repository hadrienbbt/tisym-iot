
#ifndef WIFI_SSID
#define WIFI_SSID "SSID"
#endif
#ifndef WIFI_PWD
#define WIFI_PWD "PWD"
#endif
#ifndef GATEWAY
#define GATEWAY "192.168.1.1"
#endif
#ifndef SUBNET
#define SUBNET "255.255.255.0"
#endif
#ifndef DNS
#define DNS "192.168.1.1"
#endif
#ifndef IP
#define IP "192.168.1.100"
#endif
#ifndef WIFI_BSSID
#define WIFI_BSSID "{0x58, 0x1D, 0xD8, 0x05, 0xD5, 0xE8}"
#endif
#ifndef WIFI_CHANNEL
#define WIFI_CHANNEL 1
#endif
#ifndef MQTT_SERVER
#define MQTT_SERVER "MQTT_SERVER"
#endif
#ifndef MQTT_PORT
#define MQTT_PORT 1883
#endif
#ifndef MQTT_USER
#define MQTT_USER "MQTT_USER"
#endif
#ifndef MQTT_PWD
#define MQTT_PWD "MQTT_PWD"
#endif
#ifndef SLEEP
#ifdef ESP32S3
#define SLEEP false
#endif
#ifdef ESP8266
#define SLEEP true
#endif
#endif
#ifndef BUTTON_PIN_BITMASK
#define BUTTON_PIN_BITMASK 0x0000000000000000
#endif
#ifndef BTN_0
#define BTN_0 10
#endif
#ifndef BTN_1
#define BTN_1 11
#endif
#ifndef BTN_2
#define BTN_2 12
#endif
#ifndef BTN_3
#define BTN_3 13
#endif