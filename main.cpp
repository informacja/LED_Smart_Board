
#include "include/controlGPIO.h"        // 8 małych LED'ów i 4 przyciski
#include "include/funcGPIO.h"           // funkcje do powyższych
#include "include/interaction.h"        // manual set led by buttons(GPIO)
#include "include/litery.h"             // Czcionka 5x4 pixele
#include "include/func_matryca.h"       // Logo ZST, zegar
#include "include/function.h"           // use GPIO & SPI
#include "include/sound_visualisation.h"
#include "include/time_measure.h"

using namespace std;

// ----------------------------------------------------------------------------

    /// GPIO
    /// 0 -  3 Przyciski
    /// 4 -  7 LEDy zolte
    /// 8 - 11 LEDy zielone

// TO DO:
//    - printf dla update (losowe mignięcia)
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

//    string music = "/home/pi/smart_led_board/audio/data.flac"; // data, closer, muse, hero, test, short, seco

//    cout << "sound_visualisation returns: " <<
//    sound_visualisation( fd, xRGB, music )
//    << endl;

    for( int i = 0; bMain_dziala == true; i++ )
    {
//        zegar(fd, xRGB);
        interaction( &GPIO, fd, xRGB ); // przy naciśnięciu uruchamia animację
//        ColorControl(&GPIO, fd, xRGB, 20, i);
//        police( fd, xRGB, i, 50);
//        alphabet( i, fd, xRGB );
//        Prosty_licznik_na_diodach( &GPIO, i );
//        text( "d",fd,xRGB );

//        bool direction_left = true;
//        text_sliding("abc", i, fd, xRGB, 15, 0, 0, direction_left );

        Ustaw_zolte_od_przyciskow_2( &GPIO );

//        blink( &GPIO , 25, 10 );

        if ( exit( &GPIO ) ) break;
        ws2812b_update(fd,xRGB);
//        if ( i % 256 == 0 ) cout << "i = " << i << endl;
//        if ( i >= 16000 ) i = 0;
//        usleep( 10e4 );        // PRZEWIJANIE LITEREK Czekamy 100 ms co krok w petli
        usleep( 10e3 );                                                      // Czekamy 10 ms co krok w petli
    }
end:
    Odeksportuj_GPIO( &GPIO );
    Niszcz_GPIO( &GPIO );
    memset( xRGB, 0x0, PIXEL_COUNT * 4 );
    printf("ws2812b_last_update: %d\n", ws2812b_update(fd, xRGB));
    close(fd);

    return 0;
}


/// kody z pliku sławka
/*
int main(int argc, char * argv[])
{
    bMain_dziala = true;

	signal( SIGINT, Awaryjne_zatrzymanie );

	int fd;
    printf("SPI init: %d\n", spi_init("/dev/spidev0.0", &fd));
    int i, j, k;
    j = 0;
    k = 1;

    int nR =  255;
    int nG =  255;
    int nB =  255;
    int unused_8bit = 0;

    TPixel color;
    //color.dw = 0x000000;
    color.dw = ( unused_8bit << 24 ) + ( nR << 16 ) + ( nG << 8 ) + nB;

    //Menu//
    int menuOpc;
    cout << "Menu" << endl;
    cout << "1. Animacja ZST" << endl;
    cout << "2. Zegar" << endl;
    cout << endl;

    cout << "Wybierz jedną z powyższych opcji: ";
    cin >> menuOpc;


        switch( menuOpc )
        {
            case 1:
            {
                while( bMain_dziala == true )
                {
                    animationZST(fd, color.dw );
                    animationRectangle(fd , color.dw );
                    usleep(50000);	// 50 ms*//*
                    memset( xRGB, 0x00, PIXEL_COUNT * 4 );
                    printf("ws2812b_update: %d\n", ws2812b_update( fd, xRGB ) );
                }

                break;
            }

            case 2:
            {
                 while( bMain_dziala == true )
                {


                    time_t t = time(0);
                    struct tm * currentTime = localtime( & t);

                    int firstHour   = currentTime->tm_hour / 10;
                    int secoundHour = currentTime->tm_hour % 10;

                    int firstMin   = currentTime->tm_min / 10;
                    int secoundMin = currentTime->tm_min % 10;

                    int n = 0;

                    //int firstSec   = currentTime->tm_sec / 10;
                    //int secoundSec = currentTime->tm_sec % 10;

                    cout << currentTime->tm_hour << ":" << currentTime->tm_min << ":" << currentTime->tm_sec << endl;

                    if(currentTime->tm_sec == 00)
                    {
                        Sec( 60, 0x002020);
                        clearNumber( 2, 2 );
                        clearNumber( 9, 2 );
                        clearNumber( 2, 9 );
                        clearNumber( 9, 9 );

                        Numbers( firstHour, 2, 2, 0x002020);
                        Numbers( secoundHour, 9, 2, 0x002020);

                        Numbers( firstMin, 2, 9, 0x002020);
                        Numbers( secoundMin, 9, 9, 0x002020);

                        printf("", ws2812b_update( fd, xRGB ) );


                        //printf("ws2812b_update: %d\n", ws2812b_update( fd, xRGB ) );

                        usleep(960000);
                        memset( xRGB, 0x00, PIXEL_COUNT * 4 );
                        printf("ws2812b_update: %d\n", ws2812b_update( fd, xRGB ) );
                    }

                    Sec( currentTime->tm_sec, 0x002020);

                    Numbers( firstHour, 2, 2, 0x002020);
                    Numbers( secoundHour, 9, 2, 0x002020);

                    Numbers( firstMin, 2, 9, 0x002020);
                    Numbers( secoundMin, 9, 9, 0x002020);
                    printf("", ws2812b_update( fd, xRGB ) );
                    usleep(30000);

                }

                break;
            }

            case 3:
            {
                while( bMain_dziala == true )
                {
                    //lA( 0, 0, 255);
                    //printf("", ws2812b_update( fd, xRGB ) );
                }

                break;
            }
        }



    // Jak wszystko poszło dobrze, to Ctrl+C tylko wywali pętlę i program pójdzie w to miejsce
    cout << "Jesli widac ten komunikat to dziala wszystko jak mialo dzialac" << endl;

    memset( xRGB, 0x00, PIXEL_COUNT * 4 );

    printf("ws2812b_update: %d\n", ws2812b_update( fd, xRGB ) );

    close(fd);
}
*/
//========================================================================

