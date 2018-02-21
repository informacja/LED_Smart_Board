#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED

#include <iostream>
#include <vector>
#include <unistd.h>
#include <signal.h>

// bez tego nie dziala to_string();
#include <string>
#include <sstream>

#include <ncurses.h>

using namespace std;

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

//========================
// Do obsługi Ctrl+C
#include <signal.h>
// Nie ma strumieniaIO w oryginalnym programie
#include <time.h>
#include <ncurses.h> //obsługa klawiatury
#include <dirent.h>
#include <random>


// czas bitu H to calkowita wielokrotnosc 300ns
// czas bitu L jest bez wiekszego znaczenia
#define SPI_BIT_TIME 300
// wymagana czestotliwosc: ok. 3,3MHz
#define SPI_CLOCK (1000000000 / SPI_BIT_TIME)
#define SPI_MAX_SIZE 4096

#define WS_B0  0b1000
#define WS_B1  0b1100
#define WS_RST 0b0000
// dla RESET wymagane minimum 50000ns
#define WS_RST_BYTES (1 + 50000 / (8*SPI_BIT_TIME))

#define WS_MK_BYTE(x,y) ((x << 4) | (y))

#define PIXEL_COUNT (16 * 16)

//#define TEXT_SLIDING_VERTICAL

// ----------------------------------------------------------------------------

typedef enum
{
    err_ok = 0,
    err_spi_mode,
    err_spi_bits,
    err_spi_speed,
    err_spi_datacount
} err_t;
//
//typedef enum
//{
//    RED     = ( 255 << 16 ) + ( 0 << 8 ) + ( 0 ),
//    Pink    = 0xE91E63, // do poprawy
//    Purple  = 0x4A148C,
//    Indigo  = 0x311B92,
//    BLUE    = 0x006064, // cyan( 0 << 16 ) + ( 0 << 8 ) + ( 255 ),
//    Light_Blue = 0x01579B,
//    Teal    = 0x004D40,
//    GREEN   = 0x1B5E20,//( 0 << 16 ) + ( 255 << 8 ) + ( 0 ),
//    Light_Green = 0x33691E,
//    Lime    = 0x827717,
//    YELLOW  = 0xFFAB00,
//    Orange  = 0xE65100,
//    Deep_Orange= 0xBF360C,
//    Brown   = 0x3E2723,
//    Grey    = 0x212121,
//    Blue_Grey= 0x263238
//
//} colors_tab1;

//static uint32_t RED = 0x110000;
//static uint32_t BLUE = 0x22;
//static uint32_t



typedef enum
{
    RED     = ( 255 << 16 ) + ( 0 << 8 ) + ( 0 ),
    Pink    = 0xE91E63, // do poprawy
    Purple  = 0x4A148C,
    Indigo  = 0x311B92,
    BLUE    = 0x0000FF, // cyan( 0 << 16 ) + ( 0 << 8 ) + ( 255 ),
    Light_Blue = 0x01579B,
    Teal    = 0x004D40,
    GREEN   = 0x00FF00,//( 0 << 16 ) + ( 255 << 8 ) + ( 0 ),
    Light_Green = 0x33691E,
    Lime    = 0x827717,
    YELLOW  = 0xFFAB00,
    Orange  = 0xE65100,
    Deep_Orange= 0xBF360C,
    Brown   = 0x3E2723,
    Grey    = 0x212121,
    Blue_Grey= 0x263238
} ;



struct config {
    bool play = false;
    bool reset = false;
};

//static uint32_t xRGB [PIXEL_COUNT];


//static uint32_t color = GREEN;
//static uint32_t color = ( 100 << 16 ) + ( 100 << 8 ) + ( 100 );       // RGB
static uint32_t color = Orange;


/*

0 	    #ff0000	rgb(255, 0, 0)	    hsl(0, 100%, 50%)
15 	    #ff4000	rgb(255, 64, 0)	    hsl(15, 100%, 50%)
30 	    #ff8000	rgb(255, 128, 0)	hsl(30, 100%, 50%)
45 	    #ffbf00	rgb(255, 191, 0)	hsl(45, 100%, 50%)
60 	    #ffff00	rgb(255, 255, 0)	hsl(60, 100%, 50%)
75 	    #bfff00	rgb(191, 255, 0)	hsl(75, 100%, 50%)
90 	    #80ff00	rgb(128, 255, 0)	hsl(90, 100%, 50%)
105 	#40ff00	rgb(64, 255, 0)	    hsl(105, 100%, 50%)
120 	#00ff00	rgb(0, 255, 0)	    hsl(120, 100%, 50%)
135 	#00ff40	rgb(0, 255, 64)	    hsl(135, 100%, 50%)
150 	#00ff80	rgb(0, 255, 128)	hsl(150, 100%, 50%)
165 	#00ffbf	rgb(0, 255, 191)	hsl(165, 100%, 50%)
180 	#00ffff	rgb(0, 255, 255)	hsl(180, 100%, 50%)
195 	#00bfff	rgb(0, 191, 255)	hsl(195, 100%, 50%)
210 	#0080ff	rgb(0, 128, 255)	hsl(210, 100%, 50%)
225 	#0040ff	rgb(0, 64, 255)	    hsl(225, 100%, 50%)
240 	#0000ff	rgb(0, 0, 255)	    hsl(240, 100%, 50%)
255 	#4000ff	rgb(64, 0, 255)	    hsl(255, 100%, 50%)
270 	#8000ff	rgb(128, 0, 255)	hsl(270, 100%, 50%)
285 	#bf00ff	rgb(191, 0, 255)	hsl(285, 100%, 50%)
300 	#ff00ff	rgb(255, 0, 255)	hsl(300, 100%, 50%)
315 	#ff00bf	rgb(255, 0, 191)	hsl(315, 100%, 50%)
330 	#ff0080	rgb(255, 0, 128)	hsl(330, 100%, 50%)
345 	#ff0040	rgb(255, 0, 64)	    hsl(345, 100%, 50%)
360 	#ff0000	rgb(255, 0, 0)	    hsl(0, 100%, 50%)

*/

#endif // LIBRARY_H_INCLUDED
