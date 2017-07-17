#ifndef CONTROLGPIO_CPP
#define CONTROLGPIO_CPP

#include "../include/controlGPIO.h"

extern bool bMain_dziala;

inline void Awaryjne_zatrzymanie( const int id )
{
    string str;

    str  = "\033[31m";
    str += "Nacisnieto Ctrl+C";
    str += "\033[0m";

    cout << str << endl;

    bMain_dziala = false;
}
//========================================================================

inline void Tworz_GPIO( vector<cGPIO*> *GPIO )
{
    if( bDebug )
    {
        cout << endl << "Tworzenie GPIO" << endl;
    }

    // 4 przyciskig
    GPIO->push_back( new cGPIO( 18 ) );
    GPIO->push_back( new cGPIO( 23 ) );
    GPIO->push_back( new cGPIO( 24 ) );
    GPIO->push_back( new cGPIO( 25 ) );

    // 4 LEDy zolte
    GPIO->push_back( new cGPIO(  4 ) );
    GPIO->push_back( new cGPIO( 17 ) );
    GPIO->push_back( new cGPIO( 27 ) );
    GPIO->push_back( new cGPIO( 22 ) );

    // 4 LEDy zielone
    GPIO->push_back( new cGPIO(  5 ) );
    GPIO->push_back( new cGPIO(  6 ) );
    GPIO->push_back( new cGPIO( 13 ) );
    GPIO->push_back( new cGPIO( 19 ) );

}
//========================================================================

inline void Niszcz_GPIO( vector<cGPIO*> *GPIO )
{
    if( bDebug )
    {
        cout << endl << "Niszczenie GPIO" << endl;
    }

    for( int i = GPIO->size() - 1; 0 <= i; i-- )
    {
        delete (*GPIO)[ i ];
        (*GPIO)[ i ] = NULL;
    }
}
//========================================================================

inline void Eksportuj_GPIO( vector<cGPIO*> *GPIO )
{
    if( bDebug )
    {
        cout << endl << "Eksport GPIO" << endl;
    }

    for( int i = 0; i < GPIO->size(); i++ )
    {
        (*GPIO)[ i ]->Export();
    }
}
//========================================================================

inline void Odeksportuj_GPIO( vector<cGPIO*> *GPIO )
{
    if( bDebug )
    {
        cout << endl << "Odeksport GPIO" << endl;
    }

    for( int i = 0; i < GPIO->size(); i++ )
    {
        (*GPIO)[ i ]->Unexport();
    }
}
//========================================================================

inline void Ustaw_kierunek_GPIO( vector<cGPIO*> *GPIO  )
{
    if( bDebug )
    {
        cout << endl << "Ustawianie GPIO" << endl;
    }

    // Przyciski ustawiamy jako wejscie "in" na stan wysoki "high", gdzie stan niski jest 1, a stan wysoki 0 - bo tak lepiej dla procesora
    for( int i = 0; i < 4 && i < GPIO->size(); i++ )
    {
        (*GPIO)[ i ]->Set_direction( "high" );
    }

    // LEDy ustawiomy jako wyjscie "out"
    for( int i = 4; i < GPIO->size(); i++ )
    {
        (*GPIO)[ i ]->Set_direction( "out" );
    }
}
//========================================================================

inline void Ustaw_GPIO( vector<cGPIO*> *GPIO, const int nr, const bool bON )
{
    if( 0 <= nr && nr < GPIO->size() )
    {
        (*GPIO)[ nr ]->Set( bON );
    }
}
//========================================================================

inline void Prosty_licznik_na_diodach( vector<cGPIO*> *GPIO, const int i )
{
    static unsigned licznik( 0 );

    // Co sekunde, bo w main() jest 10ms * 100 = 1s
    if( i % 100 == 0 )
    {
        licznik++;

        int wart = licznik & 0xF;

        int pozycja = 1;

        for( int i = 0; i < 4; i++ )
        {
            bool bLED = ( ( wart & pozycja ) == pozycja ? false : true );

            pozycja <<= 1;

            Ustaw_GPIO( GPIO, 8 + i, bLED );
        }
//        cout << "\nLicznik: " << i << endl; // prawdopodobnie wysypuje się int
    }
}
//========================================================================

inline void Ustaw_zolte_od_przyciskow( vector<cGPIO*> *GPIO )
{
    static bool bInput[ 4 ] = { false };

    for( int i = 0; i < 4; i++ )
    {
        bool bLED = (*GPIO)[ i ]->Get();

        // Zabezpieczenie. Nie trzeba ustawiac stanu, ktory juz jest.
        // Co prawda jest juz zabezpieczenie wewnatrz metody "Set", ale po co niepotrzebnie ja wywolywac? :)
        if( bInput[ i ] != bLED )
        {
            Ustaw_GPIO( GPIO, 4 + i, bLED );

            bInput[ i ] = bLED;
        }
    }
}

#endif // CONTROLGPIO_CPP
