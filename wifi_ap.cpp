#include "wifi_ap.h"
#include "filesystem.h"
#include "display.h"

WebServer server(80);

const char* ap_ssid = "ESP-LoRaSPOT";
const char* ap_pass = "12345678";


// ----------------  HOT- Spot initialisieren ---------------------
void initWiFiAP()
{
  WiFi.softAP(ap_ssid, ap_pass);

  Serial.println("AP gestartet");
  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/save", HTTP_POST, handleSave);

  server.begin();
}

void wifiLoop()
{
    server.handleClient();
}

// --- Homepage -------------------------------
String htmlPage()
{
  String page =
  "<!DOCTYPE html><html><head><meta charset='utf-8'>"
  "<title>ESP32 Intervall</title></head><body>"
  "<h2>Intervall einstellen</h2>"
  "<form action='/save' method='POST'>"
  "<input name='intervall' type='text' value='" + intervar + "'>"
  "<input type='submit' value='Speichern'>"
  "</form>"
  "</body></html>";

  return page;
}

// --------- WEB Aufruf --------------------------
void handleRoot()
{
  server.send(200, "text/html", htmlPage());
}

// ----------- WEB Wert Speichern ----------------
void handleSave()
{
  if (server.hasArg("intervall"))
  {
    intervar = server.arg("intervall");

    saveIntervall(intervar);
  }

  server.sendHeader("Location", "/");
  server.send(303);
  drawDisp();
}