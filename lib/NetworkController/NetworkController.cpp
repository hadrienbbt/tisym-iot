#include <NetworkController.h>

NetworkController::NetworkController(const char *ssid, const char *password, const char *gateway, const char *subnet, const char *dns, const char *ip, const uint8_t *bssid, int channel, const char *mqtt_broker, const char *mqtt_user, const char *mqtt_password, int mqtt_port)
{
  this->ssid = ssid;
  this->password = password;
  this->gateway = gateway;
  this->subnet = subnet;
  this->dns = dns;
  this->ip = ip;
  this->bssid = bssid;
  this->channel = channel;
  this->mqtt_broker = mqtt_broker;
  this->mqtt_user = mqtt_user;
  this->mqtt_password = mqtt_password;
  this->mqtt_port = mqtt_port;
}

void NetworkController::setup()
{
  connectWiFi();
  connectMQTT();
}

void NetworkController::loop()
{
}

void NetworkController::connectWiFi()
{
  Serial.println("\n");
  Serial.println("Connecting to WiFi...");
  Serial.print("WIFI_SSID: ");
  Serial.println(ssid);
  Serial.print("WIFI_PWD: ");
  Serial.println(password);
  Serial.print("WIFI_CHANNEL: ");
  Serial.println(channel);
  Serial.print("STATIC IP: ");
  Serial.println(ip);
  Serial.print("GATEWAY: ");
  Serial.println(gateway);
  Serial.print("SUBNET: ");
  Serial.println(subnet);
  Serial.print("DNS: ");
  Serial.println(dns);

  WiFi.mode(WIFI_STA);
  IPAddress ip_static;
  IPAddress ip_gateway;
  IPAddress ip_subnet;
  IPAddress ip_dns;
  if (ip_static.fromString(ip) && ip_gateway.fromString(gateway) && ip_subnet.fromString(subnet) && ip_dns.fromString(dns))
  {
    WiFi.config(ip_static, ip_gateway, ip_subnet, ip_dns);
    Serial.println("IP config set");
  }
  WiFi.persistent(true);

  WiFi.begin(ssid, password, WIFI_CHANNEL, bssid, true);

  Serial.println("\n...");
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  Serial.println("WiFi Connected\n");
  Serial.println("IP address: ");
  Serial.print(WiFi.localIP().toString().c_str());
  Serial.println("\nRouter MAC address: ");
  Serial.print(WiFi.BSSIDstr());
  Serial.println("\n");
}

void NetworkController::connectMQTT()
{
  Serial.println("Connecting to MQTT Broker...");
  mqtt.begin(this->mqtt_broker, this->mqtt_port, wifi);

  while (!mqtt.connect(this->mqtt_broker, this->mqtt_user, this->mqtt_password))
  {
    Serial.println("Connection Failed! Waiting...");
    Serial.print(".");
    delay(1000);
  }

  Serial.println("MQTT Server Connected:");
}

void NetworkController::publishButtonPressed(int pin)
{
  String deviceType = DEVICETYPE;
  mqtt.publish("hue", "{\"action\":\"press\",\"payload\":{\"deviceType\":\"" + deviceType + "\",\"pin\":" + String(pin) + "}}");
  Serial.println("Press published");
}

void NetworkController::publishButtonLongPressed(int pin)
{
  String deviceType = DEVICETYPE;
  mqtt.publish("hue", "{\"action\":\"long_press\",\"payload\":{\"deviceType\":\"" + deviceType + "\",\"pin\":" + String(pin) + "}}");
  Serial.println("Long press published");
}
