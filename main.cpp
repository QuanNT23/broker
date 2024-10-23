#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

const char* ssid = "KTX B10 506";
const char* password = "02346722";
const char* mqttServer = "192.168.1.130";  // IP của broker
const int mqttPort = 1883;
int number = 0;

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
    String incommingMessage = "";
    for (int i = 0; i < length; i++) incommingMessage += (char)payload[i];
    Serial0.println("Message received on topic [" + String(topic) + "]: " + incommingMessage);
}

void setup() {
  Serial0.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial0.println("Connecting to WiFi...");
  }
  
  Serial0.println("Connected to WiFi");
  client.setServer(mqttServer, mqttPort);
  String clientId = "ESP32Client_" + String(random(0xffff), HEX);

  while (!client.connected()) {
    Serial0.println("Connecting to MQTT...");
    if (client.connect(clientId.c_str())) {
      Serial0.println("Connected to MQTT broker");
      client.subscribe("home/test");
    } else {
      Serial0.print("Failed, rc=");
      Serial0.print(client.state());
      delay(2000);
    }
  }
  client.setCallback(callback);
}

void loop() {
  client.loop();
  String s_number = String(number);
  client.publish("home/temperature", s_number.c_str());
  number++;
  delay(1000);
}
