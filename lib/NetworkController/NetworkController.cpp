#include <NetworkController.h>

NetworkController::NetworkController(const char *ssid, const char *password, const char *gateway, const char *subnet, const char *dns, const char *ip, const uint8_t *bssid, int channel, const char *mqtt_broker, const char *mqtt_user, const char *mqtt_password, int mqtt_port, uint8_t prog_led)
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
  this->prog_led = prog_led;
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
  Serial.println("\n...");

  int count = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    if (!(count % 5))
    {
      digitalWrite(this->prog_led, !digitalRead(this->prog_led));
    }
    delay(100);
    count++;
  }

  Serial.println("WiFi Connected\n");
  Serial.println("IP address: ");
  Serial.print(WiFi.localIP().toString().c_str());
  Serial.println("\nDevice MAC address: ");
  Serial.print(WiFi.macAddress());
  Serial.println("\nRouter MAC address: ");
  Serial.print(WiFi.BSSIDstr());

  Serial.println("\n");
}

void NetworkController::connectMQTT()
{
  Serial.println("Connecting to MQTT Broker...");
  mqtt.begin(this->mqtt_broker, this->mqtt_port, wifi);

  int count = 0;
  while (!mqtt.connect(this->mqtt_broker, this->mqtt_user, this->mqtt_password))
  {
    Serial.println("Connection Failed! Waiting...");
    Serial.print(".");
    if (!(count % 10))
    {
      digitalWrite(this->prog_led, !digitalRead(this->prog_led));
    }
    delay(100);
    count++;
  }

  Serial.println("MQTT Server Connected:");
}

void NetworkController::publishButtonPressed(int pin)
{
  String deviceType = DEVICETYPE;
  String message = "{\"action\":\"press\",\"payload\":{\"deviceType\":\"" + deviceType + "\",\"pin\":" + String(pin) + "}}";
  while (!mqtt.publish("hue", message, true, 1))
  {
    Serial.print(".");
  }
  Serial.println("Press published");
}

void NetworkController::publishButtonLongPressed(int pin)
{
  String deviceType = DEVICETYPE;
  String message = "{\"action\":\"long_press\",\"payload\":{\"deviceType\":\"" + deviceType + "\",\"pin\":" + String(pin) + "}}";
  while (!mqtt.publish("hue", message, true, 1))
  {
    Serial.print(".");
  }
  Serial.println("Long press published");
}

void NetworkController::disconnect()
{
  Serial.println("Disconnecting from MQTT...");
  while (!mqtt.disconnect())
  {
    Serial.print(".");
  }
  Serial.println("Disconnecting from WiFi...");
  while (!WiFi.disconnect())
  {
    Serial.print(".");
  }
  Serial.println("Disconnected");
}
