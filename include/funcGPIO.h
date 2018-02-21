#ifndef FGPIO_H
#define FGPIO_H

#include "../include/cGPIO.h"
#include "../include/controlGPIO.h"
#include "../src/ws2812b_disp.cpp"


 struct config;

inline void ready_blink(vector<cGPIO*> *GPIO)
{
    unsigned time_wait = 10e4 -10e3;

    for( int i = 4; i < 12; i++ )
        Ustaw_GPIO( GPIO, i, false);
    usleep( time_wait );

    for( int i = 4; i < 12; i++ )
        Ustaw_GPIO( GPIO, i, true);
    usleep( time_wait );

    for( int i = 4; i < 12; i++ )
        Ustaw_GPIO( GPIO, i, false);
    usleep( time_wait );

    for( int i = 4; i < 12; i++ )
        Ustaw_GPIO( GPIO, i, true);
    usleep( time_wait );

    for( int i = 4; i < 12; i++ )
        Ustaw_GPIO( GPIO, i, false);
    usleep( time_wait );

    for( int i = 4; i < 12; i++ )
        Ustaw_GPIO( GPIO, i, true);
    usleep( time_wait );

//    for( int i = 0; i < 4; i++)
//    {
//        static int orange_LED_index = 4;
//        static int  green_LED_index = 11;
//
//        Ustaw_GPIO( GPIO, orange_LED_index, false);
//        Ustaw_GPIO( GPIO, green_LED_index , false);
//
//        orange_LED_index++;
//        green_LED_index--;
//        usleep( time_wait );
//    }
//
//    for( int i = 0; i < 4; i++)
//    {
//        static int orange_LED_index = 8;
//        static int  green_LED_index = 7;
//
//        Ustaw_GPIO( GPIO, orange_LED_index, true);
//        Ustaw_GPIO( GPIO, green_LED_index , true);
//
//        orange_LED_index++;
//        green_LED_index--;
//        usleep( time_wait );
//    }

// off ---< >---
//    for( int i = 0; i < 4; i++)
//    {
//        Ustaw_GPIO( GPIO, 7 - i, true);
//        Ustaw_GPIO( GPIO, 8 + i, true);
//
//    }

//    usleep( time_wait );
    for( int i = 0; i < 2; i++ )
    {
    // on ---< >----
        for( int i = 0; i < 4; i++)
        {
            Ustaw_GPIO( GPIO, 7 - i, false);
            Ustaw_GPIO( GPIO, 8 + i, false);
            usleep( time_wait );
        }
    // off ---< >----
        for( int i = 0; i < 4; i++)
        {
            Ustaw_GPIO( GPIO, 7 - i, true);
            Ustaw_GPIO( GPIO, 8 + i, true);
            usleep( time_wait );
        }
    }
/*
// on ---< >---
// on -<-- -->-

// on --<- ->--
// on <--- --->

    for( int i = 0; i < 4; i++)
    {
        if ( i % 2 == 0 )
        {
            Ustaw_GPIO( GPIO, 7 - i, false);
            Ustaw_GPIO( GPIO, 8 + i, false);
        }
        usleep( time_wait );
    }
          for( int i = 0; i < 4; i++)
    {
        if ( i % 2 == 1 )
            {
                Ustaw_GPIO( GPIO, 7 - i, false);
                Ustaw_GPIO( GPIO, 8 + i, false);
            }
        usleep( time_wait );
    }


    for( int i = 0; i < 4; i++)
    {
        if ( i % 2 == 0 )
        {
            Ustaw_GPIO( GPIO, 7 - i, true);
            Ustaw_GPIO( GPIO, 8 + i, true);
        }
        usleep( time_wait );
    }
          for( int i = 0; i < 4; i++)
    {
        if ( i % 2 == 1 )
            {
                Ustaw_GPIO( GPIO, 7 - i, true);
                Ustaw_GPIO( GPIO, 8 + i, true);
            }
        usleep( time_wait );
    }

*/
// off ---< >----
//    for( int i = 0; i < 4; i++)
//    {
//        Ustaw_GPIO( GPIO, 7 - i % 2, true);
//        Ustaw_GPIO( GPIO, 8 + i % 2, true);
//        usleep( time_wait );
//    }
//
//
//
//// off ---< >----
//    for( int i = 0; i < 4; i++)
//    {
//        Ustaw_GPIO( GPIO, 7 - i % 2 -1, true);
//        Ustaw_GPIO( GPIO, 8 + i % 2 -1, true);
//        usleep( time_wait );
//    }

    usleep( 10e3 );
}

//========================================================================

void show_press_progres( int counter, vector<cGPIO*> *GPIO )
{
    for( int i = 4; i < 12; i++ )
    {
        Ustaw_GPIO( GPIO, i, true);
    }

    if ( counter )
    {
        printf("%d\n",counter);
        double percent = 8 * counter/100.0;


        for( int i = 4; i < (int)percent+4; i++ )
            {
                 Ustaw_GPIO( GPIO, i, false);

            }
//            usleep( 10e4 );
    }

}

bool exit( vector<cGPIO*> *GPIO, unsigned points, bool two_buttons )
{
    // button pressed = false
    // relased button = true
    static unsigned counter;    // 0-100 in percent
    static bool last_state[ 4 ] = { true, true, true, true };
    static int pressed_buttons(0);
    static int licznik(0);

//    for( int i = 0; i < 4; i++ )
    {
//        if( last_state[i] == (*GPIO)[ i ]->Get() && last_state[i] == false )
        {
            pressed_buttons = 0;
            for ( int i = 0; i < 4; i++ )
            {
                pressed_buttons += ( last_state[i] == false ) ? 1 : 0;
                last_state[i] = (*GPIO)[ i ]->Get();
            }

            if ( pressed_buttons > 0)
            {
                if ( two_buttons )
                {
                    if ( pressed_buttons >= 2)  // przynajmniej dwa przyciski wcisniente
                        counter++;
                    else
                        counter = 0;
                }
                else                            // one button pressed, enough to exit
                {
                    if ( pressed_buttons >= 1)
                        counter++;
                    else
                        counter = 0;
                }
                show_press_progres( counter, GPIO );
            }
            else
            {
                counter = 0;
            }

    // Cześć, poniższe 2 linie to debug, spokojnie możesz je zakomentować, miłego kodowania ;)
//            if ( i == 3 )
//                cout << "time: " << counter << " Buttons_pressed: " << pressed_buttons << endl;

        }

        if ( 100 < counter ) // dluzej niz 1 sekunda
        {
            for( int i = 4; i < 12; i++ )
            {
                Ustaw_GPIO( GPIO, 15-i, true);
                usleep( 10e4-10e3*(i-4)/4 );
            }
            usleep( 10e4 );

//            for( int i = 0; i < 4; i++ )
//            {
//                 Ustaw_GPIO( GPIO, 8-i, false);
//                 Ustaw_GPIO( GPIO, 8+i, false);
//                 usleep( 10e4 - 10e3*(i+1)*2 );
//            }
//            usleep( 10e4  );
//
//            for( int i = 0; i < 4; i++ )
//            {
//                 Ustaw_GPIO( GPIO, 8-i, true);
//                 Ustaw_GPIO( GPIO, 8+i, true);
//                 usleep( 10e4 );
//            }

            return true;
        }

        licznik ++;

        if ( points <= licznik )
        {
            cout <<                "[" << (*GPIO)[ 3 ]->Get() << "]" <<
                                  " [" << (*GPIO)[ 2 ]->Get() << "]" <<
                                  " [" << (*GPIO)[ 1 ]->Get() << "]" <<
                                  " [" << (*GPIO)[ 0 ]->Get() << "]" << endl;
            licznik = 0;
        }
    }

    usleep(10e3);

    return false;
}

void wyjdz_z_programu_przez_przyciski(vector<cGPIO*> GPIO, bool two_buttons, config* music, int fd, uint32_t *xRGB)
{
    (*music).play = false;

    bool dziala = true;

    while ( dziala )
    {
        if ( exit( &GPIO, 10, true) )
            dziala = false;
    }
    memset( xRGB, 0x0, PIXEL_COUNT * sizeof(uint32_t) );
    ws2812b_update(fd, xRGB);// dwa razy dla pewnosci, ze zgasnie
    Odeksportuj_GPIO( &GPIO );
    Niszcz_GPIO( &GPIO );
    usleep(10e4*4);
    memset( xRGB, 0x0, PIXEL_COUNT * sizeof(uint32_t) );
    printf("ws2812b_last_update_from_buttons: %d\n", ws2812b_update(fd, xRGB));
    close(fd);
    exit(0);
}

//========================================================================

inline void Ustaw_zolte_od_przyciskow_2( vector<cGPIO*> *GPIO )
{
    static bool stan_popr_przyc[ 4 ] = { false };
//    static bool last_LED[ 4 ] = { false };

    static int licznik[ 4 ] = { 0 };

    for( int i = 0; i < 4; i++ )
    {
        bool bLED = (*GPIO)[ i ]->Get();

        if( stan_popr_przyc[ i ] != bLED)
        {
            if( !bLED )
            {
                licznik[ i ]++;
            }

            Ustaw_GPIO( GPIO, 4 + i,  licznik[ i ]%2 == 0);
 //          cout << "\nJeden na zero (on_press_button)\n";

            stan_popr_przyc[ i ] = bLED;
        }

        unsigned pressed = ! (*GPIO)[ 0 ]->Get();

        static int pressed_counter(0);

        int speed = 100; // w milisekundach

        if ( pressed )
        {
            pressed_counter++;

            cout << "wcisniento " << pressed_counter<< endl;

            bool flaga = true;

            if( (pressed_counter % speed) > speed/2 )
            {
                flaga = true;
            }
            else
            {
                flaga = false;
            }

             Ustaw_GPIO( GPIO, 8, flaga);
        }
        else
        {
            pressed_counter = 0;
            Ustaw_GPIO( GPIO, 8, true);
        }
    }
}

//=======================================================================

inline void blink( vector<cGPIO*> *GPIO, unsigned miliseconds_100 = 100, int led_index_8 = 8 )
{
    static unsigned counter(0);
    static bool display(true);

    counter++;

    if ( led_index_8 != 8 )
    {
        if ( 0 == (counter) % unsigned( miliseconds_100) )
            display = !display;

        if ( display )
        {
            //cout << "licznik: " << counter << endl;
              // All_LED_on
            for( int i = 4; i < 8; i++ )
                Ustaw_GPIO( GPIO, i, false);

            //usleep( 10e2 * miliseconds_100 );
        }
        else
        {
              // All_LED_off
            for( int i = 4; i < 8; i++ )
                Ustaw_GPIO( GPIO, i, true);
        }
    }
    else
    {
        if ( display )
            Ustaw_GPIO( GPIO, led_index_8, false);
        else
            Ustaw_GPIO( GPIO, led_index_8, true);
    }
}



//=======================================================================

//class safe_close  // nie bangla przy zamknięciu okna krzyżykiem, nie wnosi nic nowego do projektu
//{
//public:
//
//    ~safe_close(  )
//    {
//        Odeksportuj_GPIO( &GPIO );
//
//        Niszcz_GPIO( &GPIO );
//    }
//};
#endif
