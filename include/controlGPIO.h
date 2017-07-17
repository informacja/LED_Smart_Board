#ifndef CONTROLGPIO_H
#define CONTROLGPIO_H

#include "cGPIO.h"

inline void Awaryjne_zatrzymanie( const int id );
inline void Tworz_GPIO( vector<cGPIO*> *GPIO );
inline void Niszcz_GPIO( vector<cGPIO*> *GPIO );
inline void Eksportuj_GPIO( vector<cGPIO*> *GPIO );
inline void Odeksportuj_GPIO( vector<cGPIO*> *GPIO );
inline void Ustaw_kierunek_GPIO( vector<cGPIO*> *GPIO  );
inline void Ustaw_GPIO( vector<cGPIO*> *GPIO, const int nr, const bool bON );
inline void Prosty_licznik_na_diodach( vector<cGPIO*> *GPIO, const int i );
inline void Ustaw_zolte_od_przyciskow( vector<cGPIO*> *GPIO );


#endif
