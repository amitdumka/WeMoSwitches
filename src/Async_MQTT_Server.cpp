#include "Async_MQTT_Server.h"

//TODO: Impelemetation check
void Async_MQTT::connectToWifi()
{
    Serial.println("Connecting to Wi-Fi...");
    WiFi.begin();
}
//TODO: Impelemetation check
void Async_MQTT::onWifiConnect(const WiFiEventStationModeGotIP &event)
{
    Serial.println("Connected to Wi-Fi.");
    connectToMqtt();
}

//TODO: Impelemetation check
void Async_MQTT::onWifiDisconnect(const WiFiEventStationModeDisconnected &event)
{
    Serial.println("Disconnected from Wi-Fi.");
    mqttReconnectTimer.detach(); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
    float s = 2;
    wifiReconnectTimer.once(s, this->connectToWifi);
}
//TODO: Impelemetation check
void Async_MQTT::connectToMqtt()
{
    Serial.println("Connecting to MQTT...");
    mqttClient.connect();
}//TODO: Impelemetation check
void Async_MQTT::onMqttConnect(bool sessionPresent)
{
    Serial.println("Connected to MQTT.");
    Serial.print("Session present: ");
    Serial.println(sessionPresent);
    uint16_t packetIdSub = mqttClient.subscribe("test/lol", 2);
    Serial.print("Subscribing at QoS 2, packetId: ");
    Serial.println(packetIdSub);
    mqttClient.publish("test/lol", 0, true, "test 1");
    Serial.println("Publishing at QoS 0");
    uint16_t packetIdPub1 = mqttClient.publish("test/lol", 1, true, "test 2");
    Serial.print("Publishing at QoS 1, packetId: ");
    Serial.println(packetIdPub1);
    uint16_t packetIdPub2 = mqttClient.publish("test/lol", 2, true, "test 3");
    Serial.print("Publishing at QoS 2, packetId: ");
    Serial.println(packetIdPub2);
}
//TODO: Impelemetation check
void Async_MQTT::onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
    Serial.println("Disconnected from MQTT.");

    if (WiFi.isConnected())
    {
        mqttReconnectTimer.once(2, this->connectToMqtt);
    }
}
//TODO: Impelemetation check
void Async_MQTT::onMqttSubscribe(uint16_t packetId, uint8_t qos)
{
    Serial.println("Subscribe acknowledged.");
    Serial.print("  packetId: ");
    Serial.println(packetId);
    Serial.print("  qos: ");
    Serial.println(qos);
}
//TODO: Impelemetation check
void Async_MQTT::onMqttUnsubscribe(uint16_t packetId)
{
    Serial.println("Unsubscribe acknowledged.");
    Serial.print("  packetId: ");
    Serial.println(packetId);
}

//TODO:: check use and implementation
void Async_MQTT::onMqttMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
    Serial.println("Publish received.");
    Serial.print("  topic: ");
    Serial.println(topic);
    Serial.print("  qos: ");
    Serial.println(properties.qos);
    Serial.print("  dup: ");
    Serial.println(properties.dup);
    Serial.print("  retain: ");
    Serial.println(properties.retain);
    Serial.print("  len: ");
    Serial.println(len);
    Serial.print("  index: ");
    Serial.println(index);
    Serial.print("  total: ");
    Serial.println(total);
}

//TODO: Impelemetation check
void Async_MQTT::onMqttPublish(uint16_t packetId)
{
    Serial.println("Publish acknowledged.");
    Serial.print("  packetId: ");
    Serial.println(packetId);
}
//TODO: Impelemetation check
void Async_MQTT::mqtt_setup()
{
    Serial.begin(115200);
    Serial.println();
    Serial.println();

    wifiConnectHandler = WiFi.onStationModeGotIP(this->onWifiConnect);
    wifiDisconnectHandler = WiFi.onStationModeDisconnected(this->onWifiDisconnect);

    mqttClient.onConnect(this->onMqttConnect);
    mqttClient.onDisconnect(this->onMqttDisconnect);
    mqttClient.onSubscribe(this->onMqttSubscribe);
    mqttClient.onUnsubscribe(this->onMqttUnsubscribe);
    mqttClient.onMessage(this->onMqttMessage);
    mqttClient.onPublish(this->onMqttPublish);
    mqttClient.setServer(MQTT_HOST, MQTT_PORT);

    connectToWifi();
}

//TODO: Impelemetation check
void Async_MQTT::mqtt_loop()
{
}
