#include "display.h"
#include "filesystem.h"
#include "gps.h"
#include "lorawan.h"


TFT_eSPI tft;




void initDisplay()
{
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
}

void drawDisp()
{
  /* Bildschirmgröße x0,y0,länge160,höhe128*/
  tft.fillRect(0, 0, 160,  20, TFT_GREY);
  tft.fillRect(0, 20, 160, 40, TFT_ORANGE);
  
  tft.setTextColor(TFT_WHITE);  // Text colour
  tft.drawString("GPS LoRaWAN Tracker", 5, 2, 1);
     
  tft.setTextColor(TFT_BLACK);  // Text colour
  tft.drawString("ESP-LoRaSPOT 192.168.4.1", 2, 25, 1);
  //tft.drawString(intervar, 100, 45, 2);

  tft.setTextColor(TFT_BLACK);  // Text colour
  tft.drawString("LoRa Intervall=", 2, 45, 1);
  tft.setTextColor(TFT_RED);  // Text colour
  tft.drawString(intervar, 95, 45, 1);
}

void displayLoop()
{
    static uint32_t lastUpdate = 0;

    if (millis() - lastUpdate < 500)   // z.B. 2x pro Sekunde
        return;

    lastUpdate = millis();

    String latStr = String(latVar, 6);
    String lonStr = String(lonVar, 6);

    // --- GPS Werte -----------
    tft.fillRect(40, 95, 100, 16, TFT_BLACK);
    tft.fillRect(40, 110, 100, 16, TFT_BLACK);

    tft.setTextColor(TFT_GREY);
    tft.drawString(latStr, 40, 95, 2);
    tft.drawString(lonStr, 40, 110, 2);

    tft.drawString("Lat:", 10, 95, 2);
    tft.drawString("Lon:", 10, 110, 2);

    // --- LoRaWAN Status ----------
    tft.drawString("LoRaWAN :", 10, 75, 2);
    tft.setTextColor(TFT_YELLOW);
    tft.drawString(loVar, 84, 80, 1);
    tft.setTextColor(TFT_GREY);
}


