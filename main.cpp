#include <thread>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <functional>

#include <iterator>
#include "include/controlGPIO.h"        // 8 małych LED'ów i 4 przyciski
#include "include/funcGPIO.h"           // funkcje do powyższych
#include "include/interaction.h"        // manual set led by buttons(GPIO)
#include "include/litery.h"             // Czcionka 5x4 pixeli
#include "include/func_matryca.h"       // Logo ZST, zegar
#include "include/function.h"           // use GPIO & SPI
#include "include/snd_alsa_play.h"      // config file
//#include "include/sound_visualisation.h"
#include "include/time_measure.h"
#include "include/random_music.h"

#define update_LED_in_main

using namespace std;

    /// GPIO
    /// 0 -  3 Przyciski
    /// 4 -  7 LEDy zolte
    /// 8 - 11 LEDy zielone

// ----------------------------------------------------------------------------

bool bMain_dziala;

int main( int argc, char *argv[])
{
    bDebug       = false;
    bMain_dziala = true;
    int fd;

    printf("SPI init: %d\n", spi_init("/dev/spidev0.0", &fd));
    uint32_t xRGB[ PIXEL_COUNT ];
    memset( xRGB, 0x00, sizeof(xRGB) );

    signal( SIGINT, Awaryjne_zatrzymanie );

    vector<cGPIO*> GPIO;
    Tworz_GPIO( &GPIO );
    Eksportuj_GPIO( &GPIO );
    Ustaw_kierunek_GPIO( &GPIO );

//    rainbow(fd, xRGB );

    /// data.flac, closer, muse, hero, test, short, seco, moby, bach, talk, story, MSin.wav, 32, 40, 500, 2000, 8100, 13954, 16000,
    string song = random_music("/home/pi/projects/smart_led_board/audio", "flac", "");

    config music;

    thread(alsa_play, &music, song, fd, xRGB).detach();
    thread(wyjdz_z_programu_przez_przyciski, GPIO, true, &music, fd, xRGB).detach();

//    alsa_play(song, fd, xRGB);                 // include/snd_alsa_play.h

    for( int i = 0; true; i++ )
    {
        if( !music.play )
            zegar(fd, xRGB);
//        interaction( &GPIO, fd, xRGB ); // przy naciśnięciu uruchamia animację
//        ColorControl(&GPIO, fd, xRGB, 20, i);
//        police( fd, xRGB, i, 50);
//        alphabet( i, fd, xRGB );
//        text( "d", fd, xRGB );

//        Prosty_licznik_na_diodach( &GPIO, i );
        bool direction_left = true;
//        text_sliding("abc", i, fd, xRGB, 15, 0, 0, direction_left );
//
// 1 play pause
// 2 prew 5s
// 3 next 5s
// 4 new random
    bool last, last1;
    if( GPIO[ 3 ]->Get() != last )
        if ( last == true )
            music.play = !music.play;
    last = GPIO[ 3 ]->Get();

    if( GPIO[ 0 ]->Get() != last )
        if ( last == true )
            music.play = !music.play;
    last1 = GPIO[ 3 ]->Get();
//        Ustaw_zolte_od_przyciskow_2( &GPIO );

//        blink( &GPIO , 10, 1 );
//break;
//        if ( exit( &GPIO, true ) )      //  jeśli dwa przyciski są wciśnięte zamyka program
//            break;

//        ws2812b_update(fd,xRGB);
//        if ( i % 256 == 0 ) cout << "i = " << i << endl;
//        if ( i >= 16000 ) i = 0;
//        usleep( 10e4 );        // PRZEWIJANIE LITEREK Czekamy 100 ms co krok w petli

        usleep( 10e3*2 );                                                      // Czekamy 10 ms co krok w petli
    }

    Odeksportuj_GPIO( &GPIO );
    Niszcz_GPIO( &GPIO );
    memset( xRGB, 0x0, PIXEL_COUNT * sizeof(uint32_t) );
    printf("ws2812b_last_update: %d\n", ws2812b_update(fd, xRGB));
    close(fd);

    return 0;
}
