#ifndef GPS_H
#define GPS_H

#include <TinyGPS++.h>

extern double latVar;
extern double lonVar;

void initGPS();

void gpsLoop();

bool gpsValid();

#endif