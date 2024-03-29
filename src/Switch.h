#ifndef SWITCH_H
#define SWITCH_H

#include "Config.h"
#include <Arduino.h>
#ifdef NODEMCU
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#endif
#include <WiFiUDP.h>
#include "CallbackFunction.h"

class Switch
{
private:
        ESP8266WebServer *server = NULL;
        WiFiUDP UDP;

        String serial;
        String persistent_uuid;
        String device_name;
        
        unsigned int localPort;
        
        CallbackFunction onCallback;
        CallbackFunction offCallback;
        
        CallbackFunctionIn onCallbackIn;
        CallbackFunctionIn offCallbackIn;

        int SwitchIndex=-1;
        bool switchStatus;

        void startWebServer();
        
        void handleEventservice();
        void handleUpnpControl();
        void handleRoot();
        void handleSetupXml();

public:
        Switch();
        Switch(String alexaInvokeName, unsigned int port, CallbackFunction onCallback, CallbackFunction offCallback);
        Switch(String alexaInvokeName, unsigned int port, CallbackFunctionIn onCallback, CallbackFunctionIn offCallback, int index);
        
        ~Switch();
        
        String getAlexaInvokeName();
        void serverLoop();
        void respondToSearch(IPAddress &senderIP, unsigned int senderPort);
        void sendRelayState();
};

#endif
