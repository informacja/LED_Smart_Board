#ifndef LITERY_H_INCLUDED
#define LITERY_H_INCLUDED

#define FONT_WIDTH 5

#include "../src/ws2812b_disp.cpp"

void lA(int x, int y, int LEDcolor, uint32_t *xRGB, int width = 16 );
void lB(int x, int y, int LEDcolor, uint32_t *xRGB, int width = 16 );
void lC(int x, int y, int LEDcolor, uint32_t *xRGB, int width = 16 );
void lD(int x, int y, int LEDcolor, uint32_t *xRGB, int width = 16 );
void lE(int x, int y, int LEDcolor, uint32_t *xRGB, int width = 16 );
void lF(int x, int y, int LEDcolor, uint32_t *xRGB, int width = 16 );
void lG(int x, int y, int LEDcolor, uint32_t *xRGB, int width = 16 );
void lH(int x, int y, int LEDcolor, uint32_t *xRGB, int width = 16 );
void lI(int x, int y, int LEDcolor, uint32_t *xRGB, int width = 16 );
void lJ(int x, int y, int LEDcolor, uint32_t *xRGB, int width = 16 );
void lK(int x, int y, int LEDcolor, uint32_t *xRGB, int width = 16 );
void lL(int x, int y, int LEDcolor, uint32_t *xRGB, int width = 16 );
void lM(int x, int y, int LEDcolor, uint32_t *xRGB, int width = 16 );
void lN(int x, int y, int LEDcolor, uint32_t *xRGB, int width = 16 );
void lO(int x, int y, int LEDcolor, uint32_t *xRGB, int width = 16 );
void lP(int x, int y, int LEDcolor, uint32_t *xRGB, int width = 16 );
void lR(int x, int y, int LEDcolor, uint32_t *xRGB, int width = 16 );
void lQ(int x, int y, int LEDcolor, uint32_t *xRGB, int width = 16 );
void lS(int x, int y, int LEDcolor, uint32_t *xRGB, int width = 16 );
void lT(int x, int y, int LEDcolor, uint32_t *xRGB, int width = 16 );
void lU(int x, int y, int LEDcolor, uint32_t *xRGB, int width = 16 );
void lV(int x, int y, int LEDcolor, uint32_t *xRGB, int width = 16 );
void lW(int x, int y, int LEDcolor, uint32_t *xRGB, int width = 16 );
void lX(int x, int y, int LEDcolor, uint32_t *xRGB, int width = 16 );
void lY(int x, int y, int LEDcolor, uint32_t *xRGB, int width = 16 );
void lZ(int x, int y, int LEDcolor, uint32_t *xRGB, int width = 16 );

void add_letter( char letter, int x, int y, uint32_t *xRGB, uint32_t color, int width = 16); // width to rozmiar matrycy (a*a)
void text( string text, int fd,  uint32_t *xRGB );
void text_sliding(  string text, int i_as_iterator, int fd, uint32_t *xRGB, int refresh, int x = 0, int y = 0, bool direction_left = true );
void alphabet( int i, int fd, uint32_t *xRGB, int refresh_per_i_100 = 100 );
void rotate_buff( uint32_t * buff, unsigned width_of_tab );

#endif // LITERY_H_INCLUDED
