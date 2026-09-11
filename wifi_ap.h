#ifndef WIFI_AP_H
#define WIFI_AP_H

#include <WiFi.h>
#include <WebServer.h>

extern WebServer server;

extern const char* ap_ssid;
extern const char* ap_pass;

void initWiFiAP();

void wifiLoop();

String htmlPage();

void handleRoot();

void handleSave();

#endif