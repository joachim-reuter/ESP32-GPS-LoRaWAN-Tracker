#include "gps.h"
#include "filesystem.h"
#include "display.h"

TinyGPSPlus gps;
HardwareSerial SerialGPS(1);

double latVar = 0;
double lonVar = 0;

void initGPS()
{
    SerialGPS.begin(9600, SERIAL_8N1, 16, 17);
}

void gpsLoop()
{


  while (SerialGPS.available()) gps.encode(SerialGPS.read());
  
  static unsigned long lastPrint = 0;

  if (millis() - lastPrint > 1000)
  {
      lastPrint = millis();

      if (gps.location.isValid())
      {
          Serial.print("Lat: ");
          latVar = gps.location.lat();
          Serial.println(latVar,8);
          

          Serial.print("Lon: ");
          lonVar = gps.location.lng();
          Serial.println(lonVar,8);
          
      }
      else
      {
          Serial.println("Suche Satelliten...");
      }
      
  }

}

bool gpsValid()
 {
    return gps.location.isValid();
 }

 