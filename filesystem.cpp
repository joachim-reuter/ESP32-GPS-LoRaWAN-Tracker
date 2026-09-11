#include "filesystem.h"

String intervar = "";

void initFS()
{
    if (!LittleFS.begin(true))
    {
        Serial.println("LittleFS Mount fehlgeschlagen");
        return;
    }

    Serial.println("LittleFS OK");
}

bool loadIntervall()
{
    fs::File f = LittleFS.open("/intervall.txt", "r");

    if (!f)
    {
        Serial.println("intervall.txt fehlt");
        return false;
    }

    while (f.available())
    {
        String line = f.readStringUntil('\n');
        line.trim();

        if (line.startsWith("intervall="))
            intervar = line.substring(10);
            Serial.println(intervar);
    }

    f.close();

    return true;
}

bool saveIntervall(String value)
{
    fs::File f = LittleFS.open("/intervall.txt", "w");

    if (!f)
        return false;

    f.println("intervall=" + value);
    f.close();

    return true;
}