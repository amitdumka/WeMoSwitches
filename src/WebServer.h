#ifndef WEBSERVER_H
#define WEBSERVER_H
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <Arduino.h>
#include "WeMo.h"
#include "Config.h"

class WebServer
{

private:
  int WebPort = WebServer_HTTP_Port;
  int WebSecurePort =WebServer_HTTPS_Port;
  
  //Check onwards
  String header;
  // Current time
  unsigned long currentTime = millis();
  // Previous time
  unsigned long previousTime = 0;

  // Define timeout time in milliseconds (example: 2000ms = 2s)
  static const long timeoutTime;
  
  void AddButton(String switchName, bool outputState, int index, WiFiClient client);
  void ButtonSelect();
  void EndDoc(WiFiClient client);
  void WebBody(WiFiClient client);

public:
  WiFiServer *server = NULL;
  WebServer();
  WebServer(int port);
  ~WebServer();
  bool StartWebServer();
  void RootDoc(WiFiClient client);
  void IndexPage();
};
#endif
