#ifndef INTERACTION_H_INCLUDED
#define INTERACTION_H_INCLUDED

#include "func_matryca.h"               // Logo ZST, zegar
#include "../src/controlGPIO.cpp"       // 8 małych LED'ów i 4 przyciski
#include "funcGPIO.h"          // funkcje do powyższych

inline int interaction( vector<cGPIO*> *GPIO,int fd, uint32_t *xRGB );


void run_animation( int fd, uint32_t *xRGB, int i )
{
    switch( i )
    {

        case 1:
            {
//                while( bMain_dziala == true )
                {
                    animationZST(fd, xRGB, color );
                    animationRectangle(fd, xRGB, color );
                    usleep(50000);	// 50 ms*//*
                    memset( xRGB, 0x00, PIXEL_COUNT * 4 );
                    printf("ws2812b_update: %d\n", ws2812b_update( fd, xRGB ) );
                }
                break;
            }
        case 2:
        {
            zegar( fd, xRGB );

        }

    }
}


inline int interaction( vector<cGPIO*> *GPIO, int fd, uint32_t *xRGB )
{
    static bool clear = false;
    static bool last_state[ 4 ] = { false };

    static int counter[ 4 ] = { 0 };

    for( int i = 0; i < 4; i++ )
    {
        bool bLED = (*GPIO)[ i ]->Get();

        if( last_state[ i ] != bLED)
        {
            if( !bLED )
            {
                counter[ i ]++;
            }

            Ustaw_GPIO( GPIO, 4 + i,  counter[ i ] %2 == 0);

 //          cout << "\nJeden na zero (on_press_button)\n";

            last_state[ i ] = bLED;
        }
    }

    for( int i = 0; i < 4; i++ )
    {
        if( counter[i] > 0 )
        cout << "[ " << i << " ] = " << counter[i] << endl;

    }


    bool b = (*GPIO)[ 3 ]->Get();
    static bool b_last(0);
    if (!b)
    {
        memset( xRGB, 0x00000001, PIXEL_COUNT * 4 );
        ws2812b_update(fd, xRGB); // to zamuje dużo
    }

    if ( b && b_last == false ) // wygaszanie ekranu po podniesieniu porzycisku
    {
        memset( xRGB, 0x010000, PIXEL_COUNT * 4 );

        uint32_t color = 0x1100;
//        lB(3,3,color,xRGB);
//        lA(8,3,color,xRGB);

//        Text("c");

        ws2812b_update(fd, xRGB);
        clear = false;
    }


    b_last = b;

    int i = 1;


//    run_animation(fd, xRGB, i);
//    usleep( 10e4 );

//      unsigned pressed = ! (*GPIO)[ 0 ]->Get();
//
//        static int pressed_counter(0);
//
//        int speed = 100; // w milisekundach
//
//        if ( pressed )
//        {
//            pressed_counter++;
//
//            cout << "wcisniento " << pressed_counter<< endl;
//
//            bool flaga = true;
//
//            if( (pressed_counter % speed) > speed/2 )
//            {
//                flaga = true;
//            }
//            else
//            {
//                flaga = false;
//            }
//
//             Ustaw_GPIO( GPIO, 8, flaga);
//        }
//        else
//        {
//            pressed_counter = 0;
//            Ustaw_GPIO( GPIO, 8, true);
//        }

    return 1;
}

#endif // INTERACTION_H_INCLUDED
