#include <LittleFS.h>

void setup() {
  Serial.begin(115200);
  LittleFS.begin(true);

  File g = LittleFS.open("/intervall.txt", "w");  
  g.println("intervall=30");  
  g.close();

  Serial.println("OK geschrieben");
}

void loop() {}

