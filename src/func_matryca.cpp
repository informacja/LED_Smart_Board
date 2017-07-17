#include "../include/func_matryca.h"

inline void ZST( int fd, uint32_t *xRGB, int LEDcolor ) // wyświetla napis ZST litera po literze zaczynajac od lewej strony
{
        memset( xRGB, 0x00, PIXEL_COUNT * 4 );
        printf("ws2812b_update: %d\n", ws2812b_update(fd, xRGB));
        //z
        int i;//, j, k;

        for(i = 0; i < 5; i++)
        {
            xRGB[ 0+i + 5 * 16] = LEDcolor;
            xRGB[ 0+i + 9 * 16] = LEDcolor;
        }
        for(i = 0; i < 3; i++)
        {
            xRGB[ (1+i) + (8-i) * 16] = LEDcolor;
        }

        printf("ws2812b_update: %d\n", ws2812b_update(fd, xRGB));
        sleep(0.5);
        //s
        for(i = 0; i < 3; i++)
        {
            xRGB[ (7+i) + 5 * 16] = LEDcolor;
            xRGB[ (6+i) + 9 * 16] = LEDcolor;
        }
        for(i = 0; i < 2; i++)
        {
            xRGB[ (7+i) + 7 * 16] = LEDcolor;
        }
        xRGB[ 6 + 6 * 16] = LEDcolor;
        xRGB[ 9 + 8 * 16] = LEDcolor;

        printf("ws2812b_update: %d\n", ws2812b_update(fd, xRGB));
        sleep(0.5);
        //t
        for(i = 0; i < 5; i++)
        {
            xRGB[ (11+i) + 5 * 16] = LEDcolor;
        }
        for(i = 0; i < 4; i++)
        {
            xRGB[ 13 + (6+i) * 16] = LEDcolor;
        }

        printf("ws2812b_update: %d\n", ws2812b_update(fd, xRGB));
        sleep(0.5);
       // memset( xRGB, 0x00, PIXEL_COUNT * 4 );

}

void animationRectangle( int fd, uint32_t *xRGB, int LEDcolor ) //wyświetla animowane prostokąty (góra 5 px, dół 6px)
{
        int i, j, k;

        //góra
        for( j = 0; j < 16; j++)
        {
            for(k = 0; k < 5; k++)
            {
                if(k != 4)
                {
                    xRGB[ (0+j) + (0+k) * 16] = LEDcolor;
                }
                xRGB[ (15-j) + (11+k) * 16] = LEDcolor;
                sleep(0.5);
                printf("ws2812b_update: %d\n", ws2812b_update(fd, xRGB));
            }
        }

        for( j = 0; j < 16; j++)
        {
            for(k = 0; k < 5; k++)
            {
                if(k != 4)
                {
                    xRGB[ (0+j) + (0+k) * 16] = 0x000000;
                }
                xRGB[ (15+(j*-1)) + (11+k) * 16] = 0x000000;
                sleep(0.5);
                printf("ws2812b_update: %d\n", ws2812b_update(fd, xRGB));
            }
        }
}

void animationZST( int fd, uint32_t *xRGB, int LEDcolor ) //wyświetla animowany napis ZST
{
    int i, j, k;
    for(i = 0; i < 16; i++)
        {
            for(j = 0; j < 16; j++)
            {
                xRGB[ 0+i + ( 0 + j) * 16] = LEDcolor;
                printf("ws2812b_update: %d\n", ws2812b_update(fd, xRGB));
            }

            for(k = 15; k >= 0; k--)
            {

                xRGB[ 0+i + k * 16] = 0x000000;
                //z
                if( ((i == 0 || i == 1 || i == 2 || i == 3  || i == 4) && (k == 5 || k == 9)) || ( i == 1 && k == 8) || ( i == 2 && k == 7) || ( i == 3 && k == 6))
                {
                    xRGB[ 0+i + k * 16] = LEDcolor;
                }

                //s
                if( (( i == 7 || i == 8) && ( k == 9 || k ==7 || k == 5)) || ( i == 9 && k == 5) || ( i == 6 && k == 9) || ( i == 6 && k == 6) || ( i == 9 && k == 8) )
                {
                    xRGB[ 0+i + k * 16] = LEDcolor;
                }

                //t
                if( (( i == 11 || i == 12 || i == 13 || i == 14 || i == 15) && k == 5) || (( i == 13 ) && ( k == 6 || k == 7 || k == 8 || k == 9)) )
                {
                   xRGB[ 0+i + k * 16] = LEDcolor;
                }
                printf("ws2812b_update: %d\n", ws2812b_update(fd, xRGB));
            }
        }
}

//====== Cyfry ======//
inline void Numbers( uint32_t *xRGB, int number, int x, int y, int LEDcolor)
{
    int i;

    switch( number )
    {
        case 1:
        {
            xRGB[ (x + 1) + (y + 1) * 16] = LEDcolor;
            for( i = 0; i < 5; i++)
            {
                xRGB[ (x + 2) + (y + i) * 16] = LEDcolor;
            }
            //printf("ws2812b_update: %d\n", ws2812b_update( fd, xRGB ) );

            break;
        }

        case 2:
        {
            for( i = 1; i < 4; i++)
            {
                xRGB[ (x + i) + y * 16] = LEDcolor;
                xRGB[ (x + i) + (y + 2) * 16] = LEDcolor;
                xRGB[ (x + i) + (y + 4) * 16] = LEDcolor;
            }
            xRGB[ x + y * 16] = LEDcolor;
            xRGB[ x + (y + 3) * 16] = LEDcolor;
            xRGB[ x + (y + 4) * 16] = LEDcolor;
            xRGB[ (x + 4) + (y + 1) * 16] = LEDcolor;
            xRGB[ (x + 4) + (y + 4) * 16] = LEDcolor;
            //printf("ws2812b_update: %d\n", ws2812b_update( fd, xRGB ) );

            break;
        }

        case 3:
        {
            for( i = 0; i < 5; i++)
            {
                xRGB[ (x + i) + y * 16] = LEDcolor;
                xRGB[ (x + i) + (y + 4) * 16] = LEDcolor;
            }
            for( i = 1; i < 4; i++)
            {
                xRGB[ (x + i) + (y + 2) * 16] = LEDcolor;
            }
            for( i = 1; i < 4; i++)
            {
                xRGB[ (x + 4) + (y + i) * 16] = LEDcolor;
            }

            //printf("ws2812b_update: %d\n", ws2812b_update( fd, xRGB ) );
            break;
        }

        case 4:
        {
            for( i = 0; i < 3; i++)
            {
                xRGB[ x + (y + i) * 16] = LEDcolor;
            }
            for( i = 0; i < 5; i++)
            {
                xRGB[ (x + 4) + (y + i) * 16] = LEDcolor;
            }
            for( i = 1; i < 4; i++)
            {
                xRGB[ (x + i) + (y + 2) * 16] = LEDcolor;
            }
            //printf("ws2812b_update: %d\n", ws2812b_update( fd, xRGB ) );
            break;
        }

        case 5:
        {
            for( i = 0; i < 5; i++)
            {
                xRGB[ (x + i) + y * 16] = LEDcolor;
                xRGB[ (x + i) + (y + 2) * 16] = LEDcolor;
                xRGB[ (x + i) + (y + 4) * 16] = LEDcolor;
            }
            xRGB[ x + y * 16] = 0x000000;
            xRGB[ x + (y + 1) * 16] = LEDcolor;
            xRGB[ (x + 4) + (y + 3) * 16] = LEDcolor;

            //printf("ws2812b_update: %d\n", ws2812b_update( fd, xRGB ) );

            break;
        }

        case 6:
        {
            for( i = 0; i < 5; i++)
            {
                xRGB[ (x + i) + y * 16] = LEDcolor;
                xRGB[ (x + i) + (y + 2) * 16] = LEDcolor;
                xRGB[ (x + i) + (y + 4) * 16] = LEDcolor;
            }
            xRGB[ x + (y + 1) * 16] = LEDcolor;
            xRGB[ x + (y + 3) * 16] = LEDcolor;
            xRGB[ (x + 4) + (y + 3) * 16] = LEDcolor;
            //printf("ws2812b_update: %d\n", ws2812b_update( fd, xRGB ) );

            break;
        }

        case 7:
        {
            for( i = 0; i < 5; i++)
            {
                xRGB[ (x + i) + y * 16] = LEDcolor;
            }
            for( i = 0; i < 3; i++)
            {
                xRGB[ (x + 4 - i) + (y + 1 + i) * 16] = LEDcolor;
            }
            xRGB[ (x + 2) + (y + 4) * 16] = LEDcolor;
            //printf("ws2812b_update: %d\n", ws2812b_update( fd, xRGB ) );

            break;
        }

        case 8:
        {
            for( i = 0; i < 5; i++)
            {
                xRGB[ (x + i) + y * 16] = LEDcolor;
                xRGB[ (x + i) + (y + 2) * 16] = LEDcolor;
                xRGB[ (x + i) + (y + 4) * 16] = LEDcolor;
            }
            xRGB[ x + (y + 1) * 16] = LEDcolor;
            xRGB[ x + (y + 3) * 16] = LEDcolor;
            xRGB[ (x + 4) + (y + 1) * 16] = LEDcolor;
            xRGB[ (x + 4) + (y + 3) * 16] = LEDcolor;
            //printf("ws2812b_update: %d\n", ws2812b_update( fd, xRGB ) );

            break;
        }

        case 9:
        {
            for( i = 0; i < 5; i++)
            {
                xRGB[ (x + i) + y * 16] = LEDcolor;
                xRGB[ (x + i) + (y + 2) * 16] = LEDcolor;
                xRGB[ (x + i) + (y + 4) * 16] = LEDcolor;
            }
            xRGB[ x + (y + 1) * 16] = LEDcolor;
            xRGB[ (x + 4) + (y + 1) * 16] = LEDcolor;
            xRGB[ (x + 4) + (y + 3) * 16] = LEDcolor;
            //printf("ws2812b_update: %d\n", ws2812b_update( fd, xRGB ) );

            break;
        }

        case 0:
        {

            for( i = 0; i < 5; i++)
            {
                xRGB[ x  + (y + i) * 16] = LEDcolor;
                xRGB[ (x + 4) + (y + i) * 16] = LEDcolor;
            }

            for( i = 1; i < 4; i++)
            {
                xRGB[ (x + i)  + y * 16] = LEDcolor;
                xRGB[ (x + i)  + (y + 4) * 16] = LEDcolor;
            }
            //printf("ws2812b_update: %d\n", ws2812b_update( fd, xRGB ) );

            break;
    }
}

}

void checkSec( uint32_t *xRGB, int sec, int LEDcolor )
{
   if( sec < 16 )
    {
        for(int i = 1; i < sec; i++)
        xRGB[ ( i - 1 ) + 0 * 16] = LEDcolor;
    }

    if( sec > 15 && sec < 31 )
    {
        for(int i = 1; i < 16; i++)
        xRGB[ ( i - 1 ) + 0 * 16] = LEDcolor;

        sec = sec % 16;

        for(int i = 0; i < sec; i++)
        xRGB[ 15 + i * 16] = LEDcolor;
    }

    if( sec > 30 && sec < 46 )
    {
        for(int i = 1; i < 16; i++)
        xRGB[ ( i - 1 ) + 0 * 16] = LEDcolor;

        int oSec = sec;
        sec = sec % 16;

        for(int i = 0; i < 16; i++)
        xRGB[ 15 + i * 16] = LEDcolor;


        for(int i = 31; i < oSec; i++)
        xRGB[ 286 - i ] = LEDcolor;
    }

    if( sec > 45 && sec < 61 )
    {
        for(int i = 1; i < 16; i++)
        xRGB[ ( i - 1 ) + 0 * 16] = LEDcolor;

        int oSec = sec;
        sec = sec % 16;

        for(int i = 0; i < 16; i++)
        xRGB[ 15 + i * 16] = LEDcolor;

        for(int i = 31; i < 46; i++)
        xRGB[ 286 - i ] = LEDcolor;

        for(int i = 46; i < oSec; i++)
        xRGB[ 0 + ( 61 - i ) * 16 ] = LEDcolor;
    }
}

//===== Sekundy =====//
void Sec( uint32_t *xRGB, int sec, int LEDcolor)
{
    //xRGB[ 0 + 0 * 16] = LEDcolor;

    if( sec > 0 && sec < 16 )
    {
        xRGB[ ( sec - 1 ) + 0 * 16] = LEDcolor;
    }
    if( sec > 15 && sec < 31 )
    {
        sec = sec %  16;
        xRGB[ 15 + sec * 16] = LEDcolor;
        //printf("ws2812b_update: %d\n", ws2812b_update( fd, xRGB ) );
    }
    if( sec > 30 && sec < 46 )
    {
        sec = 286 - sec;
        xRGB[ sec ] = LEDcolor;
        //printf("ws2812b_update: %d\n", ws2812b_update( fd, xRGB ) );
    }
    if( sec > 45 && sec < 61 )
    {
        sec = 61 - sec;
        xRGB[ 0 + sec * 16 ] = LEDcolor;
        //printf("ws2812b_update: %d\n", ws2812b_update( fd, xRGB ) );
    }

}

void clearNumber( uint32_t *xRGB, int x, int y)
{
    int i, j;

    for(i = 0; i < 5; i++)
    {
        for(j = 0; j < 5; j++)
        {
            xRGB[ (x + i) + (y + j) * 16 ] = 0x000000;
        }
    }
}

void zegar( int fd, uint32_t *xRGB )
{
                    time_t t = time(0);
                    struct tm * currentTime = localtime( & t);

                    int firstHour   = currentTime->tm_hour / 10;
                    int secoundHour = currentTime->tm_hour % 10;

                    int firstMin   = currentTime->tm_min / 10;
                    int secoundMin = currentTime->tm_min % 10;

                    //start sekundnika w odpowienim miejscu
                    int inicjacja = 0;
                    if(inicjacja == 0)
                    {
                        checkSec( xRGB, currentTime->tm_sec, 0x002020 );
                        inicjacja++;
                    }

//                    int n = 0;

                    //int firstSec   = currentTime->tm_sec / 10;
                    //int secoundSec = currentTime->tm_sec % 10;

                    cout << currentTime->tm_hour << ":" << currentTime->tm_min << ":" << currentTime->tm_sec << endl;

                    if(currentTime->tm_sec == 00)
                    {
                        Sec( xRGB, 60, 0x002020);
                        clearNumber( xRGB, 2, 2 );
                        clearNumber( xRGB, 9, 2 );
                        clearNumber( xRGB, 2, 9 );
                        clearNumber( xRGB, 9, 9 );

                        Numbers( xRGB, firstHour, 2, 2, 0x002020);
                        Numbers( xRGB, secoundHour, 9, 2, 0x002020);

                        Numbers( xRGB, firstMin, 2, 9, 0x002020);
                        Numbers( xRGB, secoundMin, 9, 9, 0x002020);

                        printf("", ws2812b_update( fd, xRGB ) );


                        //printf("ws2812b_update: %d\n", ws2812b_update( fd, xRGB ) );

                        usleep(960000);
                        memset( xRGB, 0x00, PIXEL_COUNT * 4 );
                        printf("ws2812b_update: %d\n", ws2812b_update( fd, xRGB ) );
                    }

                    Sec( xRGB, currentTime->tm_sec, 0x002020);

                    Numbers( xRGB, firstHour, 2, 2, 0x002020);
                    Numbers( xRGB, secoundHour, 9, 2, 0x002020);

                    Numbers( xRGB, firstMin, 2, 9, 0x002020);
                    Numbers( xRGB, secoundMin, 9, 9, 0x002020);
                    printf("", ws2812b_update( fd, xRGB ) );
                    usleep(30000);

}

unsigned int pixelColor(int R, int G, int B)
{
//    int nR =  255;
//    int nG =  255;
//    int nB =  255;
    int unused_8bit = 0;

    TPixel color;
    //color.dw = 0x000000;
    return ( unused_8bit << 24 ) + ( R << 16 ) + ( G << 8 ) + B;
}


void Menu( int fd, uint32_t *xRGB ) // Kody Sławka
{
//    printf("SPI init: %d\n", spi_init("/dev/spidev0.0", &fd));
//    int i, j, k;
//    j = 0;
//    k = 1;

    //Menu//
//    bMain_dziala = true;
    bool bMain_dziala = true;
    int menuOpc;
    cout << "Menu" << endl;
    cout << "1. Animacja ZST" << endl;
    cout << "2. Zegar" << endl;
    cout << "3. Rainbow" << endl;
    cout << "4. Kogut" << endl;
    cout << "5. Tekst [BETA]" << endl;
    cout << endl;

    cout << "Wybierz jedna z powyzszych opcji: ";
    cin >> menuOpc;


        switch( menuOpc )
        {
            case 1:
            {
                int colors[2] = { 0x002020, 0x251800 };
                int color = 0;
                int powtorzenie = 1;

                while( bMain_dziala == true )
                {
                    if( powtorzenie %2 == 0 )
                    color = colors[0];
                    else
                    color = colors[1];

                    powtorzenie++;
                    if(powtorzenie > 5) powtorzenie = 0;

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
                while( bMain_dziala == true )
                {
                    zegar(fd,xRGB);
                }

                break;
            }

            case 3:
            {
                while( bMain_dziala == true )
                {
//                    //lA( 0, 0, 255);
//                    //printf("", ws2812b_update( fd, xRGB ) );
                      rainbow(fd,xRGB);
                }

                break;
            }
            case 4:
            {
                for( int i = 0; bMain_dziala == true; i++ )
                {
                    police(fd,xRGB,i,20);
                    ws2812b_update(fd, xRGB);

                }
                memset(xRGB,0x00,PIXEL_COUNT*4);
                ws2812b_update(fd, xRGB);

            }
            case 5:
            {
                string txt = "";
                cout << "Co wyswietlic? : ";
                cin >> txt;

                for( int i = 0; bMain_dziala == true; i++ )
                {
                    text_sliding(txt, i, fd, xRGB, 15);
//                    text_sliding_rev(txt, i, fd, xRGB, 15);
                    ws2812b_update(fd,xRGB);
                }
                break;
            }
            case 6:
            {

            char ch;
            int x = 8;
            int y = 8;

            int Plansza[255];

            string myMove;
            cbreak();
            noecho();
            initscr();
            refresh();
            xRGB[ (x) + (y) * 16 ] = 0x202000;
            ws2812b_update(fd, xRGB);

            //=======================
            xRGB[ (2) + (4) * 16 ] = 0x002020;
            ws2812b_update(fd, xRGB);

            while( bMain_dziala == true )
            {
                //ch = getchar();

                cin.clear();
                cin.sync();

                cin >> ch;

                if( ch == 'w') {
                    if( y > 0 ) y -= 1;
                    myMove = "-----UP------\r\n";
                }

                if( ch == 's') {
                    if( y < 15 ) y += 1;
                    myMove = "----DOWN-----\r\n";
                }

                if( ch == 'd') {
                    if( x < 15 ) x += 1;
                    myMove = "---------RIGHT\r\n";
                }

                if( ch == 'a') {
                    if( x > 0 ) x -= 1;
                    myMove = "LEFT----------\r\n";
                }

                cout << myMove;
                //memset( xRGB, 0x00, PIXEL_COUNT * 4 );
                xRGB[ (x) + (y) * 16 ] = 0x202000;
                ws2812b_update(fd, xRGB);
            }
            endwin();

            break;
            }

            default:
            {
                cout << "\nNie wybrano programu\n";
            }

        }



    // Jak wszystko poszło dobrze, to Ctrl+C tylko wywali pętlę i program pójdzie w to miejsce
    cout << "Jesli widac ten komunikat to dziala wszystko jak mialo dzialac" << endl;

    memset( xRGB, 0x00, PIXEL_COUNT * 4 );
    printf("ws2812b_update: %d\n", ws2812b_update( fd, xRGB ) );

    Menu(fd,xRGB);

//    close(fd);
}

void show_color( int fd, uint32_t *xRGB, uint32_t color )
{
    memset( xRGB, color, PIXEL_COUNT*4 );
    ws2812b_update(fd,xRGB);
    getchar();
}


void police( int fd, uint32_t *xRGB, int counter, int refresh )
{
    static bool flag(false);

    if( counter % refresh == 0 )
    {
        if ( flag )
        {
            color =  RED;       // RGB
        }
        else
        {
            color = BLUE;
        }

        flag = !flag;

        for ( int i = 0; i < 16; i++ )
        {
//            memcpy( xRGB + i*4, (void*)&color, sizeof(color) ); // from first row, to last row
            for ( int x = 0; x < 16; x++ )
                xRGB[x +i *16] = color;
        }
        ws2812b_update( fd, xRGB );
    }
}

void rainbow( int fd, uint32_t * xRGB)
{
    for( int x = 0; x < 16; x++)
    {
        for( int i = 0; i < 16; i++)
        {
            switch(i)
            {
                case 0 : xRGB[ (0 + x) + ( 0 + i)*16 ] =  RED;          break;
                case 1 : xRGB[ (0 + x) + ( 0 + i)*16 ] =  Pink;         break;
                case 2 : xRGB[ (0 + x) + ( 0 + i)*16 ] =  Purple;       break;
                case 3 : xRGB[ (0 + x) + ( 0 + i)*16 ] =  Indigo;       break;
                case 4 : xRGB[ (0 + x) + ( 0 + i)*16 ] =  BLUE;         break;
                case 5 : xRGB[ (0 + x) + ( 0 + i)*16 ] =  Light_Blue;   break;
                case 6 : xRGB[ (0 + x) + ( 0 + i)*16 ] =  Teal;         break;
                case 7 : xRGB[ (0 + x) + ( 0 + i)*16 ] =  GREEN;        break;
                case 8 : xRGB[ (0 + x) + ( 0 + i)*16 ] =  Light_Green;  break;
                case 9 : xRGB[ (0 + x) + ( 0 + i)*16 ] =  Lime;         break;
                case 10: xRGB[ (0 + x) + ( 0 + i)*16 ] =  YELLOW;       break;
                case 11: xRGB[ (0 + x) + ( 0 + i)*16 ] =  Orange;       break;
                case 12: xRGB[ (0 + x) + ( 0 + i)*16 ] =  Deep_Orange;  break;
                case 13: xRGB[ (0 + x) + ( 0 + i)*16 ] =  Brown;        break;
                case 14: xRGB[ (0 + x) + ( 0 + i)*16 ] =  Grey;         break;
                case 15: xRGB[ (0 + x) + ( 0 + i)*16 ] =  Blue_Grey;    break;
            }
        }
    }



//        for( int i = 0; i < 16; i++)
//            xRGB[ (0 + x)*16 + ( 0 + i) ] = ( 255 << 16 ) + ( 0 << 8 ) + 255;
//        for( int i = 0; i < 16; i++)
//            xRGB[ (0 + 1)*16 + ( 0 + i) ] = ( 255 << 16 ) + ( 0 << 8 ) +  32;
//        for( int i = 0; i < 16; i++)
//            xRGB[ (0 + 2)*16 + ( 0 + i) ] = ( 255 << 16 ) + ( 0 << 8 ) +   2;
//        for( int i = 0; i < 16; i++)
//            xRGB[ (0 + 3)*16 + ( 0 + i) ] = ( 255 << 16 ) + ( 0 << 8 ) +   0;
//        for( int i = 0; i < 16; i++)
//            xRGB[ (0 + 4)*16 + ( 0 + i) ] = ( 255 << 16 ) + ( 255 << 8 ) +255;
//            xRGB[ (0 + 4)*16 + ( 0 + i) ] = color;

//    ws2812b_update(fd, xRGB);

//    for( int i = 0; i < 16*16; i++)
//    {
//        const int jasnosc = 1;
//
//        unsigned char R = ( ( xRGB[ i ] & 0xFF0000 ) >> 16 ) * jasnosc / 100;
//        unsigned char G = ( ( xRGB[ i ] & 0x00F000 ) >>  8 ) * jasnosc / 100;
//        unsigned char B = ( ( xRGB[ i ] & 0x0000FF ) >>  0 ) * jasnosc / 100;
//
//        xRGB[ i ] = ( R << 16 ) + ( G << 8 ) + B;
//    }

    for( int i = 0; i < 16*16; i++)
    {
        uint32_t buff[PIXEL_COUNT];
        memset(buff, 0x00, sizeof(buff));

        memcpy( buff+15*16, xRGB, 4*16 ); // from first row, to last row
        memcpy( buff, xRGB + 16, PIXEL_COUNT*4 - 4*16);
        memcpy( xRGB, buff, PIXEL_COUNT * 4 );

        usleep(10e3);

        ws2812b_update(fd, buff);
//getchar();

    }
}




