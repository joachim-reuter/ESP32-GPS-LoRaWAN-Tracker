#include <RadioLib.h>
#include <SPI.h>
#include "config.h"
#include "lorawan.h"
#include "gps.h"
#include "filesystem.h"

/*// ===================== PINOUT ESP32-WROOM =====================
#define LORA_SCK   18
#define LORA_MISO  19
#define LORA_MOSI  23

#define LORA_CS    15
#define LORA_DIO1  33
#define LORA_RST   27
#define LORA_BUSY  32
*/

// =================== Statusvariable für Anzeige ===============
String loVar = "";

// ===================== SPI =====================
SPIClass spil(VSPI);

// ===================== SX1262 =====================
SX1262 radio = new Module(LORA_CS, LORA_DIO1, LORA_RST, LORA_BUSY, spil);

// ===================== TTN KEYS =====================
// DevEUI
uint64_t devEUI  = 0x70B3D57ED0078496ULL;

// JoinEUI (bei dir all zeros)
uint64_t joinEUI = 0x0000000000000000ULL;

// Keys (LoRaWAN 1.0.3 -> identisch)
uint8_t nwkKey[16] = {
  0x34,0xB8,0x16,0xB2,0xEF,0x76,0xFE,0x72,
  0x9F,0x44,0xEA,0xE4,0x37,0x7B,0x6D,0x31
};

uint8_t appKey[16] = {
  0x34,0xB8,0x16,0xB2,0xEF,0x76,0xFE,0x72,
  0x9F,0x44,0xEA,0xE4,0x37,0x7B,0x6D,0x31
};

// ===================== REGION =====================
const LoRaWANBand_t region = EU868;
const uint8_t subBand = 0;

// ===================== NODE =====================
LoRaWANNode node(&radio, &region, subBand);

void initLoRaWAN()
{
  Serial.println("\n===============================");
  Serial.println("TTN SX1262 OTAA TEST START");
  Serial.println("===============================");

  loVar = "LoRa Start...";

  // SPI start
  spil.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);

  // Radio init
  Serial.println("Init radio...");
  ConfigLoRa_t config;
  config.frequency = 868;

  int state = radio.begin(config);

  Serial.print("radio.begin = ");
  Serial.println(state);

  if(state != RADIOLIB_ERR_NONE) {
    Serial.println("❌ Radio init failed!");
    while(true);
  }

  // OTAA join
  Serial.println("Joining TTN...");

  state = node.beginOTAA(joinEUI, devEUI, nwkKey, appKey);

  if(state != RADIOLIB_ERR_NONE) {
    Serial.print("OTAA init failed: ");
    Serial.println(state);
    while(true);
  }

  state = node.activateOTAA();

  if(state != RADIOLIB_LORAWAN_NEW_SESSION) {
    Serial.print("Join failed: ");
    Serial.println(state);
    while(true);
  }
  loVar = "JOIN SUCCESS!";
  Serial.println("✅ JOIN SUCCESS!");
}


void lorawanLoop()
{

  // Senderintervall einstellen
  static uint32_t lastSend = 0;

  // Intervall aus LittleFS/Webinterface
  uint32_t interval = intervar.toInt() * 1000UL;

  // Sicherheit
  if (interval == 0)
      interval = 60000;

  // Noch nicht Zeit zum Senden
  if (millis() - lastSend < interval)
      return;

  lastSend = millis();



  // Nur senden, wenn GPS gültig ist
  if (!gpsValid())
  {
      Serial.println("Kein GPS Fix - kein Uplink");
      delay(1000);
      return;
  }

  Serial.println("Sending uplink...");

  // GPS auf 5 Nachkommastellen skalieren
  int32_t lat = (int32_t)(latVar * 100000.0);
  int32_t lon = (int32_t)(lonVar * 100000.0);

  // 9 Byte:
  // 0-3 = Latitude
  // 4-7 = Longitude
  // 8   = Logging
  uint8_t payload[9];

  payload[0] = (lat >> 24) & 0xFF;
  payload[1] = (lat >> 16) & 0xFF;
  payload[2] = (lat >> 8)  & 0xFF;
  payload[3] = lat & 0xFF;

  payload[4] = (lon >> 24) & 0xFF;
  payload[5] = (lon >> 16) & 0xFF;
  payload[6] = (lon >> 8)  & 0xFF;
  payload[7] = lon & 0xFF;

  // Logging
  payload[8] = 1;

  Serial.print("LAT: ");
  Serial.println(latVar, 8);

  Serial.print("LON: ");
  Serial.println(lonVar, 8);

  Serial.print("Payload HEX: "); 

  for (int i = 0; i < 9; i++)
  {
      if (payload[i] < 0x10)
          Serial.print("0");

      Serial.print(payload[i], HEX);
      Serial.print(" ");
  }

  Serial.println();

  int state = node.sendReceive(payload, sizeof(payload));



  Serial.print("sendReceive returned = ");
  Serial.println(state);


  if(state == RADIOLIB_ERR_NONE) {
    Serial.println("✔ Uplink OK");
  } 
  else
  {
    Serial.print("❌ Uplink Fehler: ");
    Serial.println(state);
  }

 


}