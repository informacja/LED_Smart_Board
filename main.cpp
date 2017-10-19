
#include "include/controlGPIO.h"        // 8 małych LED'ów i 4 przyciski
#include "include/funcGPIO.h"           // funkcje do powyższych
#include "include/interaction.h"        // manual set led by buttons(GPIO)
#include "include/litery.h"             // Czcionka 5x4 pixele
#include "include/func_matryca.h"       // Logo ZST, zegar
#include "include/function.h"           // use GPIO & SPI
#include "include/sound_visualisation.h"
#include "include/time_measure.h"

using namespace std;

    /// GPIO
    /// 0 -  3 Przyciski
    /// 4 -  7 LEDy zolte
    /// 8 - 11 LEDy zielone

// ----------------------------------------------------------------------------

// TO DO:
//    - dlaczego Ctrl + C nie działa w sound_visualisation()

bool bMain_dziala;

int main()
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

    string music = "/home/pi/projects/smart_led_board/audio/bach.flac";
    /// data, closer, muse, hero, test, short, seco, moby, bach, talk, MSin44W16-13.WAV


    alsa_play(fd, xRGB, music);                 // include/snd_alsa_play.h


    for( int i = 0; bMain_dziala == true; i++ )
    {
//        zegar(fd, xRGB);
//        interaction( &GPIO, fd, xRGB ); // przy naciśnięciu uruchamia animację
//        ColorControl(&GPIO, fd, xRGB, 20, i);
//        police( fd, xRGB, i, 50);
//        alphabet( i, fd, xRGB );
//        Prosty_licznik_na_diodach( &GPIO, i );
//        text( "d",fd,xRGB );

//        bool direction_left = true;
//        text_sliding("abc", i, fd, xRGB, 15, 0, 0, direction_left );

//        Ustaw_zolte_od_przyciskow_2( &GPIO );

//        blink( &GPIO , 25, 10 );
break;
        if ( exit( &GPIO, true ) )      //  jeśli dwa przyciski są wciśnięte zamyka program
            break;

        ws2812b_update(fd,xRGB);
//        if ( i % 256 == 0 ) cout << "i = " << i << endl;
//        if ( i >= 16000 ) i = 0;
//        usleep( 10e4 );        // PRZEWIJANIE LITEREK Czekamy 100 ms co krok w petli

        usleep( 10e3 );                                                      // Czekamy 10 ms co krok w petli
    }

    Odeksportuj_GPIO( &GPIO );
    Niszcz_GPIO( &GPIO );
    memset( xRGB, 0x0, PIXEL_COUNT * sizeof(uint32_t) );
    printf("ws2812b_last_update: %d\n", ws2812b_update(fd, xRGB));
    close(fd);

    cout << "\nOwocnego kodowania ;)\n";

    return 0;
}
