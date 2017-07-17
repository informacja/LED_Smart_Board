#include "../include/litery.h"

// ----------------------------------------------------------------------------

void lA(int x, int y, int LEDcolor, uint32_t *xRGB, int width)
{
        for(int i = 0; i < 4; i++){
//        xRGB[ x ][ y + i ].R = 255;
//        xRGB[ x + 4 ][ y + i ].R = 255

        xRGB[ x + (y + i) * width ] = LEDcolor;
        xRGB[ (x + 4) + (y + i) * width ] = LEDcolor;
    }
    for(int i = 0; i < 3; i++){
//        xRGB[ x + 1 + i ][ y + 4].R = 255;
//        xRGB[ x + 1 + i ][ y + 2].R = 255;

        xRGB[ (x + 1 + i) + (y + 4) * width ] = LEDcolor;
        xRGB[ (x + 1 + i) + (y + 2) * width ] = LEDcolor;
    }
}

void lB(int x, int y, int LEDcolor, uint32_t *xRGB, int width)
{
//    for(int i = 0; i < 5; i++){
//        [ x + ( y + i  * width )] = LEDcolor;
//    }
//    for(int i = 0; i < 3; i++){
//        xRGB[ x + 1 + i + ( y + 4 * width )] = LEDcolor;
//        xRGB[ x + 1 + i + ( y + 0 * width )] = LEDcolor;
//        xRGB[ x + 4 + 	( y + 1 + i * width )] = LEDcolor;
//    }
//
       for(int i = 0; i < 5; i++){
        xRGB[ x + ( y + i )] = LEDcolor;
        }

    xRGB[ x + 4 + ( y + 3 * width )] = LEDcolor;
    xRGB[ x + 4 + ( y + 1 * width )] = LEDcolor;

    for(int i = 0; i < 3; i++){
        xRGB[ x + 1 + i + ( y + 4 * width )] = LEDcolor;
        xRGB[ x + 1 + i + ( y + 2 * width )] = LEDcolor;
        xRGB[ x + 1 + i + ( y + 0 * width )] = LEDcolor;
    }
}

void lC(int x, int y, int LEDcolor, uint32_t *xRGB, int width)
{
    for(int i = 0; i < 3; i++){
//        xRGB[ x + 1 + ( y + i + 1 * width )] = LEDcolor;  // ??
        xRGB[ x + 1 + i + ( y + 4 * width )] = LEDcolor;
        xRGB[ x + 1 + i + ( y + 0 * width )] = LEDcolor;
    }
    xRGB[ x + 4 + ( y + 1 * width )] = LEDcolor;
    xRGB[ x + 4 + ( y + 2 * width )] = LEDcolor;
//    xRGB[ x + 4 + ( y + 3 * width )] = LEDcolor;
}

void lD(int x, int y, int LEDcolor, uint32_t *xRGB, int width)
{
    for(int i = 0; i < 5; i++){
        xRGB[ x + 1 + ( y + i * width )] = LEDcolor;
    }
    for(int i = 0; i < 3; i++){
        xRGB[ x + 1 + i + ( y + 4 * width )] = LEDcolor;
        xRGB[ x + 1 + i + ( y + 0 * width )] = LEDcolor;
//        xRGB[ x + 4 + ( y + 1 + i * width )] = LEDcolor;
    }
}

void lE(int x, int y, int LEDcolor, uint32_t *xRGB, int width)
{
    for(int i = 0; i < 5; i++){
        xRGB[ x + ( y + i  * width )] = LEDcolor;
    }
    for(int i = 0; i < 4; i++){
        xRGB[ x + 1 + i + ( y + 4 * width )] = LEDcolor;
        xRGB[ x + i +	( y + 2 * width )] = LEDcolor;
        xRGB[ x + 1 + i + ( y + 0 * width )] = LEDcolor;
    }
}

void lF(int x, int y, int LEDcolor, uint32_t *xRGB, int width)
{
    for(int i = 0; i < 5; i++){
        xRGB[ x + (y + i) ] = LEDcolor;
    }
    for(int i = 0; i < 4; i++){
        xRGB[ x + 1 + i + ( y + 4 * width )] = LEDcolor;
        xRGB[ x + i +     ( y + 2 * width )] = LEDcolor;
    }
}

void lG(int x, int y, int LEDcolor, uint32_t *xRGB, int width)
{
    for(int i = 0; i < 3; i++){
        xRGB[ x +		( y + i + 1  * width )] = LEDcolor;
        xRGB[ x + 1 + i + ( y + 0 	 * width )] = LEDcolor;
        xRGB[ x + 2 + i	+ ( y + 2 	 * width )] = LEDcolor;
    }
    for(int i = 0; i < 4; i++){
        xRGB[ x + 1 + i + ( y + 4 * width )] = LEDcolor;
    }
    xRGB[ x + 4 + ( y + 1 * width )] = LEDcolor;
}

void lH(int x, int y, int LEDcolor, uint32_t *xRGB, int width)
{
    for(int i = 0; i < 5; i++){
        xRGB[ x + ( y + i  * width )] = LEDcolor;
        xRGB[ x + 4 + ( y + i  * width )] = LEDcolor;
    }
    for(int i = 0; i < 3; i++){
        xRGB[ x + 1 + i + ( y + 2 * width )] = LEDcolor;
    }
}

void lI(int x, int y, int LEDcolor, uint32_t *xRGB, int width)
{
    for(int i = 0; i < 5; i++){
        xRGB[ x + 2 + ( y + i  * width )] = LEDcolor;
        xRGB[ x + i + ( y 	 * width )] = LEDcolor;
        xRGB[ x + i + ( y + 4  * width )] = LEDcolor;
    }
}

void lJ(int x, int y, int LEDcolor, uint32_t *xRGB, int width)
{
    for(int i = 0; i < 2; i++){
        xRGB[ x + ( y + 1 + i  * width )] = LEDcolor;
    }

    for(int i = 0; i < 3; i++){
        xRGB[ x + 2 + i + ( y + 4	 * width )] = LEDcolor;
        xRGB[ x + 1 + i + ( y + 0	 * width )] = LEDcolor;
        xRGB[ x + 4  +	( y + 1 + i * width )] = LEDcolor;
    }
}

void lK(int x, int y, int LEDcolor, uint32_t *xRGB, int width)
{
    for(int i = 0; i < 5; i++){
        xRGB[ x + ( y + i  * width )] = LEDcolor;
    }
    for(int i = 0; i < 2; i++){
        xRGB[ x + 1 + i + ( y + 2		 * width )] = LEDcolor;
        xRGB[ x + 3 + i + ( y + 3 + i	 * width )] = LEDcolor;
        xRGB[ x + 3 + i + ( y + 1 - i	 * width )] = LEDcolor;

    }
}
void lL(int x, int y, int LEDcolor, uint32_t *xRGB, int width)
{
    for(int i = 0; i < 5; i++){
        xRGB[ x +	( y + i  * width )] = LEDcolor;
        xRGB[ x + i + ( y  * width )] = LEDcolor;
    }
}

void lM(int x, int y, int LEDcolor, uint32_t *xRGB, int width)
{
    for(int i = 0; i < 5; i++){
        xRGB[ x +	( y + i  * width )] = LEDcolor;
        xRGB[ x + 4 + ( y + i  * width )] = LEDcolor;
    }
    xRGB[ x + 1 + ( y + 3 * width )] = LEDcolor;
    xRGB[ x + 2 + ( y + 2 * width )] = LEDcolor;
    xRGB[ x + 3 + ( y + 3 * width )] = LEDcolor;
}
void lN(int x, int y, int LEDcolor, uint32_t *xRGB, int width)
{
    for(int i = 0; i < 5; i++){
        xRGB[ x +	( y + i  * width )] = LEDcolor;
        xRGB[ x + 4 + ( y + i  * width )] = LEDcolor;
    }
    for(int i = 0; i < 3; i++){
        xRGB[ x + 1 + i + ( y + 3 - i  * width )] = LEDcolor;
    }
}

void lO(int x, int y, int LEDcolor, uint32_t *xRGB, int width)
{
    for(int i = 0; i < 3; i++){
        xRGB[ x  +	( (y +1 + i)  * width )] = LEDcolor;
        xRGB[ x + 3 +	( (y +1 + i) * width )] = LEDcolor;
    }
    for(int i = 0; i < 2; i++){
        xRGB[ x + i + 1	+ ( (y ) * width )] = LEDcolor;
        xRGB[ x + i + 1	+ ( (y+4 ) * width )] = LEDcolor;
}


//        xRGB[ x + i+1 +	( y + 0 + i  * width )] = LEDcolor;
//        xRGB[ x + i+1 +	( y + 4 + i  * width )] = LEDcolor;
//        xRGB[ x + 1 + i + ( y 		 * width )] = LEDcolor;
//        xRGB[ x + 1 + i + ( y + 4 	 * width )] = LEDcolor;

}

void lP(int x, int y, int LEDcolor, uint32_t *xRGB, int width)
{
    for(int i = 0; i < 5; i++){
        xRGB[ x + ( y + i  * width )] = LEDcolor;
    }
    for(int i = 0; i < 3; i++){
        xRGB[ x + 1 + i + ( y + 2  * width )] = LEDcolor;
        xRGB[ x + 1 + i + ( y + 4  * width )] = LEDcolor;
    }
    xRGB[ x + 4 + ( y + 3  * width )] = LEDcolor;
}

void lQ(int x, int y, int LEDcolor, uint32_t *xRGB, int width)
{
    for(int i = 0; i < 3; i++){
        xRGB[ x +		( y + 1 + i  * width )] = LEDcolor;
        xRGB[ x + 1 + i + ( y + 4 	 * width )] = LEDcolor;
    }
    for(int i = 0; i < 2; i++){
        xRGB[ x + 1 + i + ( y 		 * width )] = LEDcolor;
        xRGB[ x + 4 + 	( y + 2 + i  * width )] = LEDcolor;
        xRGB[ x + 3 + i + ( y + 1 - i)]= LEDcolor;
    }
}

void lR(int x, int y, int LEDcolor, uint32_t *xRGB, int width)
{
    for(int i = 0; i < 5; i++){
        xRGB[ x + ( y + i  * width )] = LEDcolor;
    }
    for(int i = 0; i < 3; i++){
        xRGB[ x + 1 + i + ( y + 2  * width )] = LEDcolor;
        xRGB[ x + 1 + i + ( y + 4  * width )] = LEDcolor;
    }
    xRGB[ x + 4 + ( y + 3  * width )] = LEDcolor;
    for(int i = 0; i < 2; i++){
        xRGB[ x + 4 + ( y + i  * width )] = LEDcolor;
    }
}

void lS(int x, int y, int LEDcolor, uint32_t *xRGB, int width)
{
    for(int i = 0; i < 4; i++){
        xRGB[ x + 1 + i + ( y + 4  * width )] = LEDcolor;
        xRGB[ x + i +	      ( y  * width )] = LEDcolor;
    }
    for(int i = 0; i < 3; i++){
        xRGB[ x + 1 + i + ( y + 2  * width )] = LEDcolor;
    }
    xRGB[ x + ( y + 3  * width )] = LEDcolor;
    xRGB[ x + 4 + ( y + 1  * width )] = LEDcolor;
}

void lT(int x, int y, int LEDcolor, uint32_t *xRGB, int width)
{
    for(int i = 0; i < 5; i++){
        xRGB[ x + i + ( y + 4  * width )] = LEDcolor;
    }
    for(int i = 0; i < 4; i++){
        xRGB[ x + 2 + ( y + i  * width )] = LEDcolor;
    }
}

void lU(int x, int y, int LEDcolor, uint32_t *xRGB, int width)
{
    for(int i = 0; i < 4; i++){
        xRGB[ x +	( y + 1 + i  * width )] = LEDcolor;
        xRGB[ x + 4 + ( y + 1 + i  * width )] = LEDcolor;
    }
    for(int i = 0; i < 3; i++){
        xRGB[ x + 1 + i + ( y  * width )] = LEDcolor;
    }
}

void lV(int x, int y, int LEDcolor, uint32_t *xRGB, int width)
{
    for(int i = 0; i < 3; i++){
        xRGB[ x +	( y + 2 + i  * width )] = LEDcolor;
        xRGB[ x + 4 + ( y + 2 + i  * width )] = LEDcolor;
    }
    xRGB[ x + 1 + ( y + 1  * width )] = LEDcolor;
    xRGB[ x + 2 + ( y )]  = LEDcolor;
    xRGB[ x + 3 + ( y + 1	 * width )] = LEDcolor;

}

void lW(int x, int y, int LEDcolor, uint32_t *xRGB, int width)
{
    for(int i = 0; i < 5; i++){
        xRGB[ x +	( y + i  * width )] = LEDcolor;
        xRGB[ x + 4 + ( y + i  * width )] = LEDcolor;
    }
    xRGB[ x + 1 + ( y + 3  * width )] = LEDcolor;
    xRGB[ x + 2 + ( y + 2  * width )] = LEDcolor;
    xRGB[ x + 3 + ( y + 3	 * width )] = LEDcolor;

}

void lX(int x, int y, int LEDcolor, uint32_t *xRGB, int width)
{
    for(int i = 0; i < 5; i++){
       xRGB[ x + 4 - i + ( y + 4 - i  * width )] = LEDcolor;
       xRGB[ x + i +     ( y + 4 - i  * width )] = LEDcolor;
    }
}

void lY(int x, int y, int LEDcolor, uint32_t *xRGB, int width)
{
    for(int i = 0; i < 2; i++){
       xRGB[ x + 4 - i + ( y + 4 - i 	 * width )] = LEDcolor;
       xRGB[ x + i +    	( y + 4 - i  * width )] = LEDcolor;
    }
    for(int i = 0; i < 3; i++){
        xRGB[ x + 2 + ( y + i * width )] = LEDcolor;
    }
}

void lZ(int x, int y, int LEDcolor, uint32_t *xRGB, int width)
{
    for(int i = 0; i < 3; i++){
       xRGB[ x + 3 - i + ( y + 3 - i  * width )] = LEDcolor;
    }
    for(int i = 0; i < 5; i++){
        xRGB[ x + i + ( y  * width )] = LEDcolor;
        xRGB[ x + i + ( y + 4 * width )] = LEDcolor;
    }
}


// ----------------------------------------------------------------------------

void add_letter( char letter, int x, int y, uint32_t * xRGB, uint32_t color, int width )
{
    switch( letter )
    {
        case 'a': case 'A': lA( x, y, color, xRGB, width ); break;
        case 'b': case 'B': lB( x, y, color, xRGB, width ); break;
        case 'c': case 'C': lC( x, y, color, xRGB, width ); break;
        case 'd': case 'D': lD( x, y, color, xRGB, width ); break;
        case 'e': case 'E': lE( x, y, color, xRGB, width ); break;
        case 'f': case 'F': lF( x, y, color, xRGB, width ); break;
        case 'g': case 'G': lG( x, y, color, xRGB, width ); break;
        case 'h': case 'H': lH( x, y, color, xRGB, width ); break;
        case 'i': case 'I': lI( x, y, color, xRGB, width ); break;
        case 'j': case 'J': lJ( x, y, color, xRGB, width ); break;
        case 'k': case 'K': lK( x, y, color, xRGB, width ); break;
        case 'l': case 'L': lL( x, y, color, xRGB, width ); break;
        case 'm': case 'M': lM( x, y, color, xRGB, width ); break;
        case 'n': case 'N': lN( x, y, color, xRGB, width ); break;
        case 'o': case 'O': lO( x, y, color, xRGB, width ); break;
        case 'p': case 'P': lP( x, y, color, xRGB, width ); break;
        case 'r': case 'R': lR( x, y, color, xRGB, width ); break;
        case 'q': case 'Q': lQ( x, y, color, xRGB, width ); break;
        case 's': case 'S': lS( x, y, color, xRGB, width ); break;
        case 't': case 'T': lT( x, y, color, xRGB, width ); break;
        case 'u': case 'U': lU( x, y, color, xRGB, width ); break;
        case 'v': case 'V': lV( x, y, color, xRGB, width ); break;
        case 'w': case 'W': lW( x, y, color, xRGB, width ); break;
        case 'x': case 'X': lX( x, y, color, xRGB, width ); break;
        case 'y': case 'Y': lY( x, y, color, xRGB, width ); break;
        case 'z': case 'Z': lZ( x, y, color, xRGB, width ); break;

        default:
        {
            cout << "add_letter( char ... ); Nie rozpoznano znaku \'" << letter << "\'" << endl;break;
        }
    }
}

// ----------------------------------------------------------------------------

void text( string text, int fd, uint32_t *xRGB)
{
//    cout << "REF:" << color << endl;

// color = 0x111100;

    int x = 0, y = 0;


    if ( text.length() < 4 )
    {
        memset(xRGB, 0x00, PIXEL_COUNT*4);
    //    ws2812b_update(fd, xRGB);

        for( int i = 0; i < text.length(); i++)
        {
             x = i * 5;

            add_letter( text[i], x, y, xRGB, color );
        }
    }
    ws2812b_update(fd, xRGB);
}

// ----------------------------------------------------------------------------

void move_it_rev( int fd, uint32_t *xRGB )
{

// z góry na dół
        uint32_t BUFF[PIXEL_COUNT*4 - 16*4];
        memset(&BUFF, 0x00, PIXEL_COUNT*4);


    for (int y = 0; y < 16; y++)
    {
            memcpy( (void*)&BUFF[ y*15 ], (void*)&xRGB[ y*16 ], 15*4 );         // kopiuj matryce do bufora
    }

    for (int y = 0; y < 16; y++)
    {
            memset( (void*)&xRGB[ y*16 ], 0x00, 4 );                            // clear 1 line
    }

    for (int y = 0; y < 16; y++)
    {
        memcpy( (void*)&xRGB[ y*16 + 1 ], (void*)&BUFF[ y*15 ],15*4 );          // 15
    }

}

void move_it( int fd, uint32_t *xRGB )
{

// z góry na dół
        uint32_t BUFF[PIXEL_COUNT*4 - 16*4];
        memset(&BUFF, 0x00, PIXEL_COUNT*4);
//        memset(&xRGB, 0x00, sizeof(xRGB));


#ifdef TEXT_SLIDING_VERTICAL

        memcpy( BUFF, xRGB, PIXEL_COUNT*4 - 16*4);                              // matryca do bufora
        memcpy( xRGB+16, BUFF, PIXEL_COUNT*4 - 16*4);                           // 15
        memset( xRGB, 0x00, 16*4 );                                             // clear 1 line

#else

    for (int y = 0; y < 16; y++)
    {
            memcpy( (void*)&BUFF[ y*15 ], (void*)&xRGB[ y*16 ], 15*4 );         // kopiuj matryce do bufora
    }

    for (int y = 0; y < 16; y++)
    {
            memset( (void*)&xRGB[ y*16 ], 0x00, 4 );                            // clear 1 line
    }

    for (int y = 0; y < 16; y++)
    {
        memcpy( (void*)&xRGB[ y*16 + 1 ], (void*)&BUFF[ y*15 ],15*4 );          // 15
    }

#endif // TEXT_SLIDING_VERTICAL

}


void move_it_left( int fd, uint32_t *xRGB )
{

// od prawej do lewej
        uint32_t BUFF[PIXEL_COUNT*4 - 16*4];
        memset(&BUFF, 0x00, PIXEL_COUNT*4);
//        memset(&xRGB, 0x00, sizeof(xRGB));

    for (int y = 0; y < 16; y++)
    {
            memcpy( (void*)&BUFF[ y*15 ], (void*)&xRGB[ ( y*16 )+1 ], 15*4 );         // kopiuj matryce do bufora
    }

    for (int y = 0; y < 16; y++)
    {
            memset( (void*)&xRGB[ y*16+15 ], 0x00, 4 );                            // clear 1 line
    }

    for (int y = 0; y < 16; y++)
    {
            memcpy( (void*)&xRGB[ y*16], (void*)&BUFF[ y*15 ],15*4 );          // 15
    }
}

void display_line_of_leter( int fd, uint32_t *xRGB, uint32_t *buff, int column, int y = 0 )
{
//    for( int i = 0; i < FONT_WIDTH; i++)
//    {
//        for( int x = 0; x < 5; x++)
//            cout << " " << (( buff[ 5*i + 4-x ] != 0) ? "\e[45m0\e[49m" : " ");
//        cout << endl;
//    }

#ifdef TEXT_SLIDING_VERTICAL

        memcpy( xRGB, buff + column*5, 5*4 );
        if ( column == 4 )
        move_it(fd,xRGB);

#else

        for( int x = 0; x < 5; x++ )
        {
            xRGB[ x*16 + y ] = buff[ column + 5*x ];
        }

#endif // TEXT_SLIDING_VERTICAL
}

void draw ( string text, int n, int fd, uint32_t *xRGB, int refresh, int x, int y, bool direction_left )
{
//    if( n == 0 )
//    if( n < 14 )
//    {
//        if ( n % 2 )
//            xRGB[ 14-n + ( 1 * 16 ) ] = 0x110011;                                // test moveing pixel
//        else
//            xRGB[ 14-n + ( 1 * 16 ) ] = 0x00;                                    // test moveing pixel
//    }

    if( direction_left )
    {
        move_it_left(fd,xRGB);
    }
    else
    {
        move_it(fd, xRGB);
    }

    static uint32_t buff[ 5 * 5 ] = { 0 };
    static unsigned index =  n/FONT_WIDTH;                                      // litera z zmiannej text
    index %= strlen(text.c_str());
    static int column(0);

    if ( n % 5 == 0 )
    {
        memset( &buff, 0x00, 5*5*4 );
        add_letter( text[ index ], x, y, buff, color, 5 );
#ifndef TEXT_SLIDING_VERTICAL
        rotate_buff( buff, 5 );
#endif
        index++;
    }

    column = n % 5;
//    cout << "column: \e[30;48;5;82m" << column << "\e[0m" << " index: " << index << endl;

    int Y = 0;
    if ( direction_left )
        Y = 15;

    display_line_of_leter( fd, xRGB, buff, column, Y );

    ws2812b_update(fd, xRGB);
    return;

//    getchar();
}


void text_sliding( string text, int i, int fd, uint32_t *xRGB, int refresh, int x, int y, bool direction_left )
{
    static unsigned n(0);                                                      // numer klatki (odświeżeń)
    static int loop( strlen(text.c_str()) * refresh * (5) +1 );

    if ( i % loop == 0 )
    {
        if( direction_left )
        {
            move_it_left(fd,xRGB);
        }
        else
        {
            move_it(fd, xRGB);
        }
        ws2812b_update(fd,xRGB);
        cout << "Przerwa\n";
    }
    else
    {
        if ( i % refresh == 0 ) ;
            draw( text,  n++, fd, xRGB, refresh, x, y, direction_left );
    }
}

// ----------------------------------------------------------------------------

void alphabet( int i, int fd, uint32_t *xRGB, int refresh )
{
    char letter = 'a';
    static int n = 0;

    if ( i % refresh == 0 )
    {
        n++;

        if ( n >= 25 )
        {
            n = 0;
        }
//        char buff = static_cast<char>(letter + n);
//        string c( 1, buff );

        string c( 1, static_cast<char>(letter + n) );                                            // 1 znak z chara

        text( c, fd, xRGB );
    }
}

// ----------------------------------------------------------------------------

void rotate_buff( uint32_t * src, unsigned width )
{
    uint32_t BUFF[width*width] = {0};

    memcpy( BUFF, src, sizeof(BUFF) );

    for( int y = 0; y < width; y++)
        for( int x = 0; x < width; x++ )
            memcpy( &src[ x + y*width ], &BUFF[ (width-x-1) + (width-y-1)*width ], 4 );
}

// ----------------------------------------------------------------------------



