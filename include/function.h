#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED

#include "controlGPIO.h" // 8 małych LED'ów i 4 przyciski
#include "../src/ws2812b_disp.cpp"  // matryca 16x16 LED#include "include/interaction.h"   // Logo ZST, zegar

void ColorControl( vector<cGPIO*> *GPIO, int fd, uint32_t *xRGB, int refresh, int i );



#endif // FUNCTION_H_INCLUDED
