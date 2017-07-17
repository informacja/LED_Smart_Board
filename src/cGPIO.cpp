#include "cGPIO.h"

#include <fstream>

//================================================================

bool bDebug( true );

int cGPIO::nr( 0 );

//================================================================

cGPIO::cGPIO( int _id ) :
    id( _id ),
    bON( false )
{
    nr++;

    if( bDebug )
    {
        cout << nr << ". Stworzono GPIO " << id << endl;
    }
}
//================================================================

cGPIO::~cGPIO()
{
    if( bDebug )
    {
        cout << nr << ". Zniszczono GPIO " << id << endl;
    }

    nr--;
}
//================================================================

int cGPIO::Get_id()
{
    return id;
}
//================================================================

bool cGPIO::Get_bON()
{
    return bON;
}
//================================================================

int cGPIO::Xport( bool bExport )
{
    string xport_gpio;

    xport_gpio  = "/sys/class/gpio/";
    xport_gpio += ( bExport ? "" : "un" );
    xport_gpio += "export";

    fstream xfile;

    xfile.open( xport_gpio.c_str(), ios::out );

    if( xfile.good() == true )
    {
        if( bDebug )
        {
            cout << ( bExport ? "Wy" : "Od" ) << "eksportowano GPIO " <<id << endl;
        }
    }
    else
    {
        cout << "Nie mozna " << ( bExport ? "wy" : "od" ) << "eksportowac GPIO " << id << endl;

        xfile.close();

        return -1;
    }

    xfile << id;

    xfile.close();

    return 0;
}
//================================================================

int cGPIO::Export()
{
    Xport( true );

    return 0;
}
//================================================================

int cGPIO::Unexport()
{
    Xport( false );

    return 0;
}
//================================================================

int cGPIO::Set_direction( const string &direction )
{
    string dir_gpio;

    dir_gpio  = "/sys/class/gpio/gpio";
    dir_gpio += to_string( id );
    dir_gpio += "/direction";

    fstream xfile;

    xfile.open( dir_gpio.c_str(), ios::out );

    if( xfile.good() == true )
    {
        if( bDebug )
        {
            cout << "Ustawiono kierunek GPIO " <<id << " na " << direction << endl;
        }
    }
    else
    {
        cout << "Nie mozna ustawic kierunku GPIO " << id << " na " << direction << endl;

        xfile.close();

        return -1;
    }

    xfile << direction;

    xfile.close();

    return 0;
}
//================================================================

int cGPIO::Set( const bool _bON )
{
    // Nie ma potrzeby ustawiac kolejny raz, jesli jest juz wlasciwy stan na tym porcie
    if( _bON == bON )
    {
        return 0;
    }

    string val_gpio;

    val_gpio  = "/sys/class/gpio/gpio";
    val_gpio += to_string( id );
    val_gpio += "/value";

    fstream xfile;

    xfile.open( val_gpio.c_str(), ios::out );

    if( xfile.good() == true )
    {
        if( bDebug )
        {
            cout << "Ustawiono GPIO " <<id << " na " << ( bON ? "true" : "false" ) << endl;
        }
    }
    else
    {
        cout << "Nie mozna ustawic GPIO " << id << " na " << ( bON ? "true" : "false" ) << endl;

        xfile.close();

        return -1;
    }

    xfile << ( bON ? 1 : 0 ) ;

    xfile.close();

    bON = _bON;

    return 0;
}
//================================================================

bool cGPIO::Get()
{
    string val_gpio;

    val_gpio  = "/sys/class/gpio/gpio";
    val_gpio += to_string( id );
    val_gpio += "/value";

    fstream xfile;

    xfile.open( val_gpio.c_str(), ios::in );

    if( xfile.good() == true )
    {
        if( bDebug )
        {
            // Za czesto wyskakiwal ten komunikat :)
            //cout << "Odczytano GPIO " << id << endl;
        }
    }
    else
    {
        cout << "Nie mozna odczytac GPIO " << id << endl;

        xfile.close();

        return false;
    }

    int wartosc;

    xfile >> wartosc;

    xfile.close();

    bON = ( wartosc != 0 ? true : false );

    return bON;
}

//================================================================

