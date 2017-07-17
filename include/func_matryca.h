#ifndef FUNC_MATRYCA_H_INCLUDED
#define FUNC_MATRYCA_H_INCLUDED

#include "../src/ws2812b_disp.cpp"  // matryca 16x16 LED#include "include/interaction.h"   // Logo ZST, zegar
#include "litery.h" // Logo ZST, zegar

inline void ZST( int fd, uint32_t *xRGB, int LEDcolor );
void animationRectangle( int fd, uint32_t *xRGB, int LEDcolor );
void animationZST( int fd, uint32_t *xRGB, int LEDcolor );
inline void Numbers( uint32_t *xRGB, int number, int x, int y, int LEDcolor);
inline void Sec( uint32_t *xRGB, int sec, int LEDcolor);
inline void clearNumber( uint32_t *xRGB, int x, int y);
void zegar( int fd, uint32_t *xRGB );

void Menu( int fd, uint32_t *xRGB );

void show_color( int fd, uint32_t *xRGB, uint32_t color );
void police( int fd, uint32_t *xRGB, int licznik, int refresh );
void rainbow( int fd, uint32_t *xRGB );

#endif // FUNC_MATRYCA_H_INCLUDED
