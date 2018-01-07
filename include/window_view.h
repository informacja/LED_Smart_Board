
#define WIN     BUFFER_LEN/2                // WINDOW size of raw audio data packet per update LED
#define COLUMNS 16                          // Count of frequency posts
#define HEIGHT  16                          // Rows of post

#define SQUARE(a) (a*a)


void magnitude2dB_scale( kiss_fft_cpx *cx_out, unsigned uVolume[COLUMNS], unsigned freq_index[COLUMNS] );
void draw_colors( int fd, uint32_t *xRGB, unsigned vol[COLUMNS]);
void color_state( uint32_t *xRGB, unsigned vol, unsigned column = 0, unsigned power = 1);
void show_top_last_peak( int fd, uint32_t *xRGB, unsigned vol[COLUMNS], unsigned fall_down_speed );
void filtr_average_beside_freq_by_peak( int column_nr, unsigned fft_index, kiss_fft_cpx *cx_out, double &magnitude );

// ----------------------------------------------------------------------------

void calc_frquency_index( unsigned tab_index[COLUMNS], int sampleRate )
{
    unsigned frequencies[COLUMNS] =     // 16 kolumn
    {
           44,
           64,
          128,
          256,
          512,
         1024,
         2048,
         3072,
         4096,
         5000,
         6000,
         7000,
         8000,
         9000,
        12000,
        15000
    };

    // Code below overwrite frequencies in logarithmic scale

    /*

    Code ...

    */


    for( int i = 0; i < COLUMNS; i++ )
    {
        tab_index[i]=(float) BUFFER_LEN*frequencies[i]/sampleRate/2;

        if ( i > 0 )
        {
            if ( tab_index[i-1] == tab_index[i] )
                tab_index[i]++;
        }

//        cout.width(6);
//        cout<<frequencies[i];
//        cout << " [Hz] : (mnoznik) ";
//        cout.width(6);
//        cout << indexes[i]<<endl;
    }
}

// ----------------------------------------------------------------------------

float scaleBetween(float unscaledNum, float minAllowed, float maxAllowed, float fmin, float fmax) {
  return (maxAllowed - minAllowed) * (unscaledNum - fmin) / (fmax - fmin) + minAllowed;
}

float twoPointMovingAverageFilter( float input ) {
   static float lastInput = 0;
   float output = ( input + lastInput ) / 2 ;
   lastInput = input;
   return output;
}

void buildHanWindow( float *window, int size )
{
   for( int i = 0; i < size; i++ )
      window[i] = .5 * ( 1 - cos( 2 * M_PI * i / (size-1.0) ) );
}

void applyWindow( float *window, float *data, int size )
{
   for( int i = 0; i < size; i++ )
      data[i] *= window[i] ;
}

// ----------------------------------------------------------------------------
#include <fstream>
void proces_audio_fft( int fd, uint32_t *xRGB, float *data, kiss_fft_cfg &cfg, unsigned fq_index[COLUMNS] )
{
/*
zakładka 50% ???

    1. window function
    2. aply FFT
    3. magnitude on first FFT output bins ( sqrt(re*re + im*im) )
    4. convert magnitude to db 20 log10( )

    Uwagi:
    Próbka ma 2048 (bajtów)
    FFT jest stosowane na 1024*2
    do spektrum używamy tylko pierwszych 512 B *2
    Czy wszystko się zgadza?
*/

    static float hann_window[WIN];

    kiss_fft_cpx cx_in[WIN];
    kiss_fft_cpx cx_out[WIN];

    memset( &hann_window, 0, sizeof(hann_window));
    memset( &cx_in, 0, sizeof(cx_in));

    buildHanWindow( (float*)hann_window, WIN );
    applyWindow( hann_window, data, WIN );

    for( int i = 0; i < WIN; i++ )
    {
        cx_in[i].r = data[i];
        cx_in[i].i = 0;
    }

    kiss_fft( cfg, cx_in, cx_out );

//
//    ofstream file("debug_file.txt", ios::out | ios::binary );
//
//
////    file<< "start1111";
////    file.write( (char*)&cx_out,  sizeof(cx_out));
////    file<< "break11111";
//file<< "start    \n";
//    for ( int i = 0; i < WIN; i++)
//        file << fixed  << cx_out[i].i << "\t" << cx_out[i].r << endl;
//file<< "stop    ";
//    int i;
//    cout << max_peak;
//    cin >> i;


/* display 15 bins around the frequency of interest */
//    for (long k = 80; k < 110; k += 2) {

//    int e = 2;
//    for (long i = 3; i < WIN; i=pow(2,e)-1) {
//
//        e++;
//    /* real */
//        double re = cx_out[i].r;
//
//    /* imaginary */
//        double im = cx_out[i].i;
//
//    /* get normalized bin magnitude */
//        double normBinMag = 2.* ( SQ(cx_out[i].r) + SQ(cx_out[i].i) ) / WIN;
//
//    /* convert to dB value */
//        double amplitude = 20. * log10( normBinMag );
//
//    /* and display */
//        printf("bin: %4d,   freq: %g [Hz],   mag: %f,   ampl.: %f [dB]\n",
//               i, sampleRate*(double)i/WIN, normBinMag, amplitude);
//    }

//     double ref = 0;
//        for (int i = 0 ; i < WIN; i++)
//            ref += hann_window[i];

        unsigned uVolume[ COLUMNS ] = { 0 };

        magnitude2dB_scale( cx_out, uVolume, fq_index );

        draw_colors( fd, xRGB, uVolume );

        show_top_last_peak( fd, xRGB, uVolume, 7 ); // prefered range: 5 - 15

        ws2812b_update(fd, xRGB);

        static int count_of_update(0);   count_of_update++;  printf( "%d\n", count_of_update );

//    signal( SIGINT, Awaryjne_zatrzymanie );

}

// ----------------------------------------------------------------------------

void magnitude2dB_scale( kiss_fft_cpx *cx_out, unsigned uVolume[COLUMNS], unsigned freq[COLUMNS]  )
{

/*
    ustawia w uVolume 16 słupków głośności danej częstotliwości
*/

//    int e = 1;
//    for (long i = 1; i < WIN/2; i=pow(2,e)-1)
//    {
//        e++;
//
//        double normBinMag = 2.* ( SQ(cx_out[i].r) + SQ(cx_out[i].i) ) / WIN;
//
//        double amplitude = 20. * log10( normBinMag );
////        double amplitude = 10. * log10( SQ(cx_out[i].r) + SQ(cx_out[i].i) );
////        double amplitude = 10. * log10( 4*SQ(cx_out[i].r) + SQ(cx_out[i].i) )/WIN;
//
//        printf("bin: %4d,   freq: %g [Hz],   mag: %f,   ampl.: %f [dB]\n",
//               i, sampleRate*(double)i*2/BUFFER_LEN, normBinMag, amplitude);
//
////    db[i]=10*log10(imaginary[i]*imaginary[i]+real[i]*real[i]);
////dB   =      10*log10(4*(real*real + imag*imag)/(N*N))    ; avoids SQRT()
//    }


    /*
    Należy znormalizować wartość wyjściową FFT np. do 1 . Standardowe algorytmy FFT
    zwracają wartości przemnożone przez rozmiar transformaty (wynika to z samego algorytmu)
    i normalizacja polega na podzieleniu amplitudy każdego słupka przez rozmiar FFT - np. 1024.
    Wtedy max daje 1 czyli 20*log10(1)=0dB. Mniejsze wartości np. 0.5 - 20*log10(0.5) = -6dB itd.
    Reasumując wartości słupków musza być utrzymywane w zakresie 0-1.
    */

//    float bins[WIN/2];
//    bands


    // dB

//    for ( int i = 0; i< 16; i++ )
//    {
//        static float k = 1;
//        cout << 20*log10( k ) << endl;
//        k /= 2;
//    }

//    cin >> max_peak;


//      /* get normalized bin magnitude */
//        double normBinMag = 2.*sqrt(re*re + im*im) / FFT_SIZE;
//
//    /* convert to dB value */
//        double amplitude = 20. * log10( normBinMag );
//
//    /* and display */
//        printf("bin: %d,\tfreq: %f [Hz],\tmag: %f,\t ampl.: %f [dB]\n", \
//               k/2, sampleRate*.5*(double)k/FFT_SIZE, normBinMag, amplitude);
//    }
//}


    // uzyskiwanie zakresu od 0-1 (float)
    // pomijane ze wzglendu na kod ponizej, gdzie jest stosowane wybiorczo, a nie dla kazdego elementu
//    for(int i = 0; i < WIN; i++ )
//    {
//        cx_out[i].i = fabs( cx_out[i].i / WIN);
//        cx_out[i].r = fabs( cx_out[i].r / WIN);
//    }

    for (long i = 0; i < COLUMNS; i++)
    {
        double normBinMag = sqrt(SQUARE(cx_out[freq[i]].r) + SQUARE(cx_out[ freq[i] ].i)) / WIN *8; // do konca nie wiem czemu tu musze mnozyc przec 8

//        double mag = fabs(normBinMag); // wydaje byc nie potrzebne po podnoszeniu do kwadratu powyzej
        double mag = normBinMag;

        filtr_average_beside_freq_by_peak( i, freq[i], cx_out, mag ); // peak number, frequency_index[peak number], fft_out, magnitude to averange

        double amplitude = 20. * log10( mag );

        printf("bin: %4d,   freq: %*.1f [Hz],   mag: %2.4f,   ampl.: %*f [dB]\n",
               (int)freq[i], 12,44100*(double)freq[i]/(WIN), normBinMag, 11, amplitude);

        // ile LED'ow zapalic
        if ( amplitude < 0 )
        {
            int dB = 6, step = 0;

            while( amplitude < 0 && step < HEIGHT-1 )
            {
                amplitude += dB;
                step++;
            }

            if( step == 2 )
                if( amplitude > 3 )         // zapala wszystkie diody dla -3 dB
                    step--;

            uVolume[i]= HEIGHT-1-step;
        }
        else
        {
            uVolume[i]= HEIGHT-1;
            cout << "\n\'amplitude\' = " << amplitude << " should be < 0 \n";
        }
    }

//    cout << amplitude;
//
//    int i;
//    cin >> i;


//    float maxRange = 0, minRange = 0;     // we will find it, keep calm and scroll down
//
//    for( int i = 0; i < COLUMNS; i++ )
//    {
//        float average = 0;
//        average = sqrt(pow(cx_out[0].r, 2) + pow(cx_out[0].i, 2));
//
//        maxRange = minRange = average;  // first value to comparison
//
//        for (int x = 1; x < WIN / COLUMNS; x++)// zaczynamy od 0 ostatni index w tablicy 511
//        {
//            int index = x + i * WIN / COLUMNS;
//
//            float buff = sqrt(pow(cx_out[index].r, 2) + pow(cx_out[index].i, 2));
//
//            average += buff;
//
//            if ( maxRange < buff ) maxRange = buff ;
//            if ( minRange > buff ) minRange = buff ;
//
////            average +=  10* (  log10( sqrt(pow(cx_out[index].r, 2) + pow(cx_out[index].i, 2))));;
//
//        }
//
//        average /= WIN / COLUMNS;
//
////        maxRange = 20;
////        minRange = 3;
////        average = (  sqrt(pow(cx_out[511].r, 2) + pow(cx_out[511].i, 2)));;
//
//        int iMin = 0;
//        int iMax = 15;      // summary 16 LED per column
//
//        uVolume[i] = scaleBetween(average, 00, 30, minRange, maxRange);
//
////        cout << "\nAverage: " << average << endl;
//    }
}

// ----------------------------------------------------------------------------

void draw_colors( int fd, uint32_t *xRGB, unsigned vol[COLUMNS])
{
        memset( xRGB, 0x00, PIXEL_COUNT * 4 );

        for ( int i = 0; i < COLUMNS; i++ )
        {
            if ( vol[i] >= HEIGHT )
            {
                 cout << "\nError: vol[" << i << "] = " << vol[i] << " ";
                 vol[i] = HEIGHT-1;
            }
            color_state( xRGB, vol[i], i, 1 );
        }
}

// ----------------------------------------------------------------------------

void color_state( uint32_t *xRGB, unsigned vol, unsigned column, unsigned power )
{

if (vol > 0)        // dolna linia

    for(unsigned i = 0; i <= vol; i++)
    {
        if      ( i < 10 )
            xRGB[ (15-i) * 16 + column ] = 0x000100 << power;
        else if ( i < 14 )
            xRGB[ (15-i) * 16 + column ] = 0x010100 << power;
        else if ( i < 16 )
            xRGB[ (15-i) * 16 + column ] = 0x010000 << power;
        else
            cout << "\n color_state() error. vol = " << vol << endl;
    }

//    xRGB[ (15-vol) * 16 + column ] |= 0x010001 << power;

}

// ----------------------------------------------------------------------------

void filtr_average_beside_freq_by_peak( int n, unsigned n_fq, kiss_fft_cpx *cx_out, double &magnitude )// peak number, frequency_index[peak number], fft_out, magnitude to averange
{
    float averange = 0;
    int step = 0;

    for( int i = 1; i < log2(n); i++ )
    {
        if( n_fq - i > 0 )
        {
            averange += sqrt(SQUARE(cx_out[n_fq - i].r) + SQUARE(cx_out[n_fq - i].i)) / WIN *8;
            step++;
        }
    }

    if ( magnitude != 0 )    // na potrzeby debagowania
    {
//        cout << n << "\t" << n_fq << "\t" << magnitude << " averange = " << averange/step << " steps = " << step << endl;
//        cin >> step;
//        getchar();
    }
}


// ----------------------------------------------------------------------------

void show_top_last_peak( int fd, uint32_t *xRGB, unsigned vol[COLUMNS], unsigned speed)
{

    static unsigned last_vol[COLUMNS];
    static int licznik;
    licznik++;

    for( int i = 0; i < COLUMNS; i++ )
    {
        if ( last_vol[i] < vol[i] )
        {
            last_vol[i] = vol[i];
        }
        else if ( last_vol[i] == vol[i])
        {
            continue;
        }
        else
        {
            if ( last_vol[i] > 0 )
                if ( licznik > speed )
                    last_vol[i]--;
        }

        xRGB[ (15-last_vol[i]-1) * 16 + i ] = 0x010101;
    }
    if ( licznik > speed )
        licznik = 0;
}

// ----------------------------------------------------------------------------

