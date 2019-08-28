#ifndef MQTT_SERVER_H
#define MQTT_SERVER_H

#include <functional>
#include <ArduinoJson.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Bounce2.h>
#include <DHT.h>
#include <string.h>

// MQTT
#define CONFIG_MQTT_HOST "{MQTT-SERVER}"
#define CONFIG_MQTT_PORT 1883 // Usually 1883
#define CONFIG_MQTT_USER "{MQTT-USERNAME}"
#define CONFIG_MQTT_PASS "{MQTT-PASSWORD}"
#define CONFIG_MQTT_CLIENT_ID "ESP_LED" // Must be unique on the MQTT network

#define DHTPIN 2      // what digital pin we're connected to
#define DHTTYPE DHT22 // DHT 22  (AM2302), AM2321

typedef void (*MQTT_Handler)(char *topic, byte *payload, unsigned int length);

class MQTT_Client
{
private:
    static String MQTT_Server;
    static int MQTT_Port;
    static String MQTT_UserName;
    static String MQTT_Password;
    static String MQTT_Client_ID;

    WiFiClient espClient;
    PubSubClient client;
    // Basic Topic
    //topic to subscribe to request for software version (Generic Device, MAC Addr, Filename.ino)
    const char *swVerTopic = "/MQTT_Client_ID/SwVerCommand";
    char swVerThisDeviceTopic[50];
    //topic to publish request for software version
    const char *swVerConfirmTopic = "/MQTT_Client_ID/SwVerConfirm";
    String clientName;
    const char *THIS_GENERIC_DEVICE = "esp8266";
    String swVersion;

    String macToStr(const uint8_t *mac);

public:
    MQTT_Client();
    MQTT_Client(String host);
    MQTT_Client(String host, int port);
    MQTT_Client(String host, int port, String username, String password);

    void SetUp(MQTT_Handler handler);
    void Loop();
    void Connect();
    bool BasicHandler(); // Must be called on callback Handler. Other wise it can fail.
};

#endif

//CPP Part Move to Cpp file

void MQTT_Client::SetUp(MQTT_Handler handler)
{
    client = PubSubClient(espClient);
    client.setServer(CONFIG_MQTT_HOST, CONFIG_MQTT_PORT);

    client.setCallback(handler); // Generate client name based on MAC address and last 8 bits of microsecond counter

    clientName = THIS_GENERIC_DEVICE;
    clientName += '-';
    uint8_t mac[6];
    WiFi.macAddress(mac);
    clientName += macToStr(mac);

    sprintf(swVerThisDeviceTopic, "/WiFiDevice/%s/SwVerCommand", macToStr(mac).c_str());

    swVersion = THIS_GENERIC_DEVICE;
    swVersion += ',';
    swVersion += macToStr(mac);
    swVersion += ',';

    Serial.print("Client Name : ");
    Serial.println(clientName);
    Serial.print("SW Version : ");
    Serial.println(swVersion);

    Connect();

    //wait a bit before starting the main loop
    delay(2000);
}

//client.publish(buttonTopic, "Pressed");

void MQTT_Client::Loop()
{

    //reconnect if connection is lost
    if (!client.connected() && WiFi.status() == 3)
    {
        Connect();
    }

    //maintain MQTT connection
    client.loop();

    //MUST delay to allow ESP8266 WIFI functions to run
    delay(10);

    //monitor the button
    //checkButton();
    //checkTemperatureAndHumidity();
}

void callback(char *topic, byte *payload, unsigned int length)
{
    // callback function need to think over

    //convert topic to string to make it easier to work with
    String topicStr = topic;

    //Print out some debugging info
    Serial.println("Callback update.");
    Serial.print("Topic: ");
    Serial.println(topicStr);

    // if (strcmp(lightTopic, topic) == 0)
    // {
    //     if (payload[0] == '1')
    //     { //turn the light on if the payload is '1' and publish the confirmation
    //         digitalWrite(lightPin, LOW);
    //         client.publish(lightConfirmTopic, "On");
    //     }
    //     else if (payload[0] == '0')
    //     { //turn the light off if the payload is '0' and publish the confirmation
    //         digitalWrite(lightPin, HIGH);
    //         client.publish(lightConfirmTopic, "Off");
    //     }
    //     else
    //     {
    //         client.publish(lightConfirmTopic, "Err");
    //     }
    //     return;
    // }

    // if (strcmp(buttonStatusTopic, topic) == 0)
    // {
    //     if (isOn == true)
    //     {
    //         client.publish(buttonTopic, "Pressed");
    //     }
    //     else
    //     {
    //         client.publish(buttonTopic, "Released");
    //     }
    //     return;
    // }

    // if (strcmp(swVerTopic, topic) == 0)
    // {
    //     client.publish(swVerConfirmTopic, swVersion.c_str());
    //     return;
    // }

    // if (strcmp(swVerThisDeviceTopic, topic) == 0)
    // {
    //     client.publish(swVerConfirmTopic, swVersion.c_str());
    //     return;
    // }
}

//generate unique name from MAC addr
String MQTT_Client::macToStr(const uint8_t *mac)
{

    String result;

    for (int i = 0; i < 6; ++i)
    {
        if ((mac[i] & 0xF0) == 0)
            result += String(0, HEX); // stop suppression of leading zero
        result += String(mac[i], HEX);

        if (i < 5)
        {
            result += ':';
        }
    }

    return result;
}

void checkTemperatureAndHumidity(void)
{
    WiFiClient espClient;
    PubSubClient client(espClient);
    String s1;
    const char *temperatureTopic="";
    const char *humidityTopic="", *heatIndexTopic="";
    unsigned long previousMillis, readInterval; //,currentMillis;
    DHT dht(2, DHT22);
    float humidity_new, temp_c_new, hic_new, temp_c_old, humidity_old, hic_old, heatIndexTopic;
    // Wait at least 2 seconds seconds between measurements.
    // if the difference between the current time and last time you read
    // the sensor is bigger than the interval you set, read the sensor
    // Works better than delay for things happening elsewhere also
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= readInterval)
    {
        // save the last time you read the sensor
        previousMillis = currentMillis;

        // Reading temperature for humidity takes about 250 milliseconds!
        // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
        humidity_new = dht.readHumidity();                               // Read humidity (percent)
        temp_c_new = dht.readTemperature();                              // Read temperature as Centigrade
        hic_new = dht.computeHeatIndex(temp_c_new, humidity_new, false); // Compute heat index in Celsius
        // Check if any reads failed and exit early (to try again).
        if (isnan(humidity_new) || isnan(temp_c_new))
        {
            Serial.println("Failed to read from DHT sensor!");
            return;
        }

        if (temp_c_new != temp_c_old)
        {
            s1 = String(temp_c_new);
            client.publish(temperatureTopic, s1.c_str());
            temp_c_old = temp_c_new;
        }

        if (humidity_new != humidity_old)
        {
            s1 = String(humidity_new);
            client.publish(humidityTopic, s1.c_str());
            humidity_old = humidity_new;
        }

        if (hic_new != hic_old)
        {
            s1 = String(hic_new);
            client.publish(heatIndexTopic, s1.c_str());
            hic_old = hic_new;
        }

        Serial.print("Humidity: ");
        Serial.print(humidity_new);
        Serial.print(" %\t");
        Serial.print("Temperature: ");
        Serial.print(temp_c_new);
        Serial.print(" *C ");
        Serial.print("Heat index: ");
        Serial.print(hic_new);
        Serial.println(" *C");
    }
}

void MQTT_Client::Connect()
{

    //make sure we are connected to WIFI before attemping to reconnect to MQTT
    if (WiFi.status() == WL_CONNECTED)
    {
        // Loop until we're reconnected to the MQTT server
        while (!client.connected())
        {
            Serial.print("Attempting MQTT connection...");

            //if connected, subscribe to the topic(s) we want to be notified about
            if (client.connect((char *)clientName.c_str()))
            {
                Serial.print("\tMTQQ Connected");
                //client.publish(swVerConfirmTopic, "Connected");
                //client.publish(lightConfirmTopic, "Connected");
                client.publish(swVerConfirmTopic, swVersion.c_str());
                //client.publish(buttonTopic, "Connected");
                client.subscribe(swVerThisDeviceTopic);
                client.subscribe(swVerTopic);

                //client.subscribe(buttonStatusTopic);
                //client.subscribe(lightTopic);
                //
                //client.publish(temperatureTopic, "Connected");
                //client.publish(humidityTopic, "Connected");
                //client.publish(heatIndexTopic, "Connected");
            }

            //otherwise print failed for debugging
            else
            {
                Serial.println("\tFailed.");
                abort();
            }
        }
    }
}