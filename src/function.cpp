
#include "../include/function.h"  // matryca 16x16 LED#include "include/interaction.h"   // Logo ZST, zegar

void update( int fd, uint32_t * xRGB )
{
//                memset(xRGB+14, (xRGB[2] << 16) + (xRGB[1] << 8) + xRGB[0], 4);
//                memset(xRGB+13*16, 0xFF0000, (xRGB[2] >> 16) % 0x0F );
//                memset(xRGB+14*16, 0x00FF00, (xRGB[1] >>  8) % 0x0F );
////
//uint32_t buff = 0x00010000;
//                memset(xRGB+13*16, 0x00, 16*4 );
//                for( int i = 0; i < (xRGB[2]>>16) / 0xF; i++ )
//                    memset(xRGB+13*16 +i, buff, 1);
////
//buff = 0x00000100;
//                memset(xRGB+14*16, 0x00, 16*4 );
//                for( int i = 0; i < (xRGB[1]>>8) / 0xF; i++ )
////                    memset(xRGB+14*16 , buff, 1);
//                        memcpy(xRGB+15*16+i ,(void*)buff, sizeof(buff));

                memset(xRGB+15*16, 0x00, 16*4 );
                for( int i = 0; i < xRGB[0] / 0x10; i++ )
                    memset(xRGB+15*16 + i, 0x01, 1);

                printf("R:%d\tG:%d\tB:%d\txRGB:%d\n",xRGB[0]>>16,xRGB[1]>>8,xRGB[2],xRGB[0]);
                ws2812b_update( fd, xRGB );
}

void show_direction( vector<cGPIO*> *GPIO, bool direct )
{
    if ( direct )
    {
//        Ustaw_GPIO(GPIO,7,true);
//        Ustaw_GPIO(GPIO,8,false);
    }
    else
    {
//        Ustaw_GPIO(GPIO,8,true);
//        Ustaw_GPIO(GPIO,7,false);
    }
}

void ColorControl( vector<cGPIO*> *GPIO, int fd, uint32_t *xRGB, int refresh, int n )
{
    int w = 0x01;                       // wartość zmiany
    bool make_update = false;
    unsigned time_wait = 10e4 ;
    static bool last_state(false);
    static bool direct(false);          // false  - góra | true - w dół
    static unsigned counter(0);
    static bool  last[3] = {true};

    if ( n == 0 )
    {
////        Ustaw_GPIO(GPIO,8,true);        // zielona dioda przy uruchomieniu
//        Ustaw_GPIO(GPIO,7,false);
    }

    if ( last_state != (*GPIO)[ 3 ]->Get() )
    {
        if ( !last_state )
        {
            direct = !direct;
            show_direction( GPIO, direct );
        }
    }
    else // jeśli stan wcisnięcia bez zmian
        if ( last_state == false)
            counter++;
        else
            counter = 0;

    if ( 100 < counter )
    {
        memset(xRGB,0,PIXEL_COUNT*4);
        update( fd, xRGB );
        counter = 0;
        return;
    }
    last_state = (*GPIO)[ 3 ]->Get();

    for(int i = 0; i < 3; i++)
    {
        bool curr_state = (*GPIO)[ i ]->Get();

        if( false == curr_state )
        {
            if (direct)
            {
                if ( (xRGB[i] + w << 8*i ) <= (255 << 8*i))
                     xRGB[i] += w << 8*i ;
            }
            else if( w <= xRGB[i] >> 8*i )
            {
                 xRGB[i] -= w << 8*i;
            }
            else
            {
                update( fd, xRGB );

                for(int i=0; i<4; i++)
                {
                    for( int i = 0; i < 4; i++)
                    {
//                        Ustaw_GPIO( GPIO, 7 - i, false);
                    }
                    usleep( time_wait );

                    // off <<<< >>>>
                    for( int i = 0; i < 4; i++)
                    {
//                        Ustaw_GPIO( GPIO, 7- i, true);
                    }
                    usleep( time_wait );
                }
                direct = !direct;
                show_direction( GPIO, direct );
            }

                    if ( n % refresh == 0 )
                    {
        //                if (!direct)
        //                    memset(xRGB,0x00,PIXEL_COUNT);
                        update( fd, xRGB );
                    }

        } else if ( last[i] == false ) // on button up
            make_update = true;

        last[i] = curr_state;
    }
    if ( make_update )
        update( fd, xRGB );
}
