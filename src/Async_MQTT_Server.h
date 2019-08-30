#ifndef ASYNC_MQTT_SERVER_H
#define ASYNC_MQTT_SERVER_H

#include "config.h"
#include <AsyncMqttClient.h>
#include <Ticker.h>

#ifdef NODEMCU
#include <ESP8266WiFi.h>
#endif

#ifdef ESP32
#include <WiFi.h>
extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
}
#endif

#define MQTT_HOST IPAddress(192, 168, 1, 10)
#define MQTT_PORT 1883

class Async_MQTT
{
    AsyncMqttClient mqttClient;
    WiFiEventHandler wifiConnectHandler;
    WiFiEventHandler wifiDisconnectHandler;

#ifdef NODEMCU
    Ticker mqttReconnectTimer;
    Ticker wifiReconnectTimer;

#endif

#ifdef ESP32
    TimerHandle_t mqttReconnectTimer;
    TimerHandle_t wifiReconnectTimer;
#endif

public:
void mqtt_loop();
void mqtt_setup();

void onWifiConnect(const WiFiEventStationModeGotIP &event);
void onWifiDisconnect(const WiFiEventStationModeDisconnected &event);

void connectToMqtt();

void connectToWifi();
void onMqttPublish(uint16_t packetId);
void onMqttConnect(bool sessionPresent);
void onMqttDisconnect(AsyncMqttClientDisconnectReason reason);
void onMqttSubscribe(uint16_t packetId, uint8_t qos);
void onMqttUnsubscribe(uint16_t packetId);
void onMqttMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total);


};


#endif
