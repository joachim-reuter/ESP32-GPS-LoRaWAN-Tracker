/* -----------------------------------------------------------------------------------
GPS LoRaWAN Tracker Projekt
- Display initialisieren
- Wert im LittleFS speichern
- HotSpot mit WEB- Seite zum ändern Intervall
- GPS integriert
--------------------------------------------------------------------------------------

user setup :
#define ST7735_DRIVER
#define ST7735_BLACKTAB   // <<< Wichtig für zentriertes Bild!

#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS   5
#define TFT_DC   2
#define TFT_RST  4
#define TFT_MISO -1

#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define SMOOTH_FONT
#define SPI_FREQUENCY 27000000

*/


// ###########################################################################

#ifndef CONFIG_H
#define CONFIG_H

// TFT
#define TFT_CS      5
#define TFT_DC      2
#define TFT_RST     4

// GPS
#define GPS_RX      16
#define GPS_TX      17



// Batterie
#define BATTERY_PIN 35

// ===================== PINOUT ESP32-WROOM =====================
#define LORA_SCK   18
#define LORA_MISO  19
#define LORA_MOSI  23

#define LORA_CS    15
#define LORA_DIO1  33
#define LORA_RST   27
#define LORA_BUSY  32


#endif