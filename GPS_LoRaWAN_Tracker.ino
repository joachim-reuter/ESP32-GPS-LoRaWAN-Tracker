
#include <WiFi.h>
#include <WebServer.h>
#include "config.h"
#include "display.h"
#include "filesystem.h"
#include "gps.h"
#include "wifi_ap.h"
#include "lorawan.h"


void setup()
{
    Serial.begin(115200); // For debug
    initDisplay();
    initFS();
    loadIntervall();
    initGPS();
    initWiFiAP();

    drawDisp();

    initLoRaWAN();
 

    
    
}

void loop()
{
    gpsLoop();
    wifiLoop();
    displayLoop();
    lorawanLoop();
    
    
}