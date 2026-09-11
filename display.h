#ifndef DISPLAY_H
#define DISPLAY_H

#include <TFT_eSPI.h>

#define TFT_GREY        0x5AEB
#define TFT_ORANGE      0xFD20


void initDisplay();

void drawDisp();

void displayLoop();

#endif