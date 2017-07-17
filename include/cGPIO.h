#ifndef CGPIO_H
#define CGPIO_H

#include "library.h"

extern bool bDebug;

//================================================================

template<typename T>
std::string to_string(const T& obj)
{
    std::stringstream ss;
    ss << obj;
    return ss.str();
}

//================================================================

class cGPIO
{
    private:
        static int nr;
        int  id;
        bool bON;

        int Xport( bool bExport );

    public:
         int  Get_id();
         bool Get_bON();

         cGPIO( int _id );
        ~cGPIO();

        int  Export();
        int  Unexport();
        int  Set_direction( const string& );
        int  Set( const bool _bON );
        bool Get();
};
//================================================================

#endif // CGPIO_H
