#ifndef NETWORK_H
#define NETWORK_H

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

extern ESP8266WebServer webServer;
extern WiFiClient client;

extern void InitWifiWebServer();

extern void loopNetwork();
extern void setupNetwork();

#endif