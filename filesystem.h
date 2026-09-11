#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <FS.h>
#include <LittleFS.h>

extern String intervar;

void initFS();

bool loadIntervall();

bool saveIntervall(String value);

#endif