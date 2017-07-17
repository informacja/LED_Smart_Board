#ifndef SOUND_VISUALISATION_H_INCLUDED
#define SOUND_VISUALISATION_H_INCLUDED

#include "library.h"
#include "func_matryca.h"
#include "time_measure.h"


#define DR_FLAC_IMPLEMENTATION
#include "dr_flac.h"

#define DR_AUDIO_IMPLEMENTATION
#include "dr_audio.h"

#include <alsa/asoundlib.h>

#define PCM_DEVICE "default"

// ----------------------------------------------------------------------------

void display_tab_labels()
{
    cout << endl;
    cout.width(9);
    cout << "Global";
    cout.width(5);
    cout << "Nr";
    cout.width(8);
    cout << "CurrFrame";
    cout.width(8);
    cout << " ";
    cout << "Value (*pOut)";
    cout.width(6);
    cout << "FPS" << endl;
}

// ----------------------------------------------------------------------------

void color_state( uint32_t *xRGB, unsigned vol, unsigned column = 0, unsigned power = 1)
{
    for(int i = 0; i <= vol; i++)
    {
        if      ( i <= 10 )
            xRGB[ (15-i) * 16 + column ] = 0x000100 << 1;
        else if ( i <= 14 )
            xRGB[ (16-i) * 16 + column ] = 0x010100 << power;
        else if ( i <= 16 )
            xRGB[ (16-i) * 16 + column ] = 0x010000 << power;
        else
            cout << "\n color_state() error. vol = " << vol << endl;
    }
}

// ----------------------------------------------------------------------------

void info_voice( dra_voice* pVoice, string music = "" )
{
    if ( music != "" )
        cout << "File: " << music << endl;
    cout << "sampleRate: "  << pVoice->sampleRate << endl;
    cout << "sizeInBytes: " << pVoice->sizeInBytes << endl;
    size_t bytesPerSample = dra_get_bytes_per_sample_by_format(pVoice->format);
    cout << "bytesPerSample: " << bytesPerSample << endl;
    cout << "Channels: "    << pVoice->channels << endl;
    cout << "FrameCount: "  << pVoice->frameCount << endl;
}

// ----------------------------------------------------------------------------

int sound_visualisation( int fd, uint32_t *xRGB, string music  )
{
    dra_device* pDevice;
    dra_result result = dra_device_create(NULL, dra_device_type_playback, &pDevice);
    if (result != DRA_RESULT_SUCCESS) {
        cout << "Can't create music device" << endl;
        return -2;
    }

    dra_voice* pVoice;
    result = dra_voice_create_from_file(pDevice, music.c_str(), &pVoice);
    if (result != DRA_RESULT_SUCCESS) {
        cout << "Can't create voice from file: " << music << endl;
        return -3;
    }

    info_voice( pVoice, music );

    dra_voice_play(pVoice, false);

    // raw print
//    for ( int i = 0; i < pVoice->frameCount; i++ )
//    {
//        float* pOut = nullptr;
//        pOut = (float*)pVoice->pData + (i * pVoice->channels);
//
//        cout.width(8);
//        cout << i;
//        cout << left;
//        cout.width(14);
//        cout << *pOut << endl;
//    }
//    return 0;
//    high_resolution_clock::time_point last = high_resolution_clock::now();
    display_tab_labels();
    double maxValue = 0;

    float last = 0;
    unsigned coutner_display = 0, coutner_global = 0;


    time_point<system_clock> timeLast, timeNow;


    while( pVoice->currentReadPos <= pVoice->frameCount )
    {
        timeNow = system_clock::now();

//        double framedelta =double ( timeNow - timeLast )

std::chrono::duration<double> elapsed_seconds = elapsed_seconds;

timeLast = timeNow;


        coutner_global++;

        maxValue = last;

        float* pOut = 0;

        pOut = (float*)pVoice->pData + (pVoice->currentReadPos );

        if ( *pOut != last )
        {
//            if ( pVoice->currentReadPos % 100 == 0 )
            {
                coutner_display++;
                cout.width(9);
                cout << coutner_global << " ";
                cout.width(4);
                cout << coutner_display << " ";
                cout.width(7);
                cout << pVoice->currentReadPos << ": " << *pOut;

                cout << "  " << elapsed_seconds.count() << endl;
                last = *pOut;

                double buff = 0.0;
//                for( int x = 0; x < 16; x++ )
                {
                    memset( xRGB, 0x00, PIXEL_COUNT * 4 );

//                    buff = (double)*pOut / 32768.0;

                        if( last < 0.0)
                        {
                            last -= last + last;
                        }

                    int interator = floor( last * 100.0 );

                    if (interator > 16 )
                    {
                        interator = 16;
//                        for( int i = 0; i < PIXEL_COUNT; i++ )
//                            xRGB[ i ] = 0x110000;
                    }
//                    else
                    color_state( xRGB, interator );

//                    for( int s = 0; s < interator; s++)
                    {
//                        color_state( xRGB, interator, s, s );
                    }

//            if( last > maxValue )
//                maxValue = last;

                    ws2812b_update(fd, xRGB);
//                    for( int y = 0; y < (int)buff; y++)
//                    {
//                        xRGB[ x + ( y )*16 ] = 0x000011;
//                    }
//                    cout << buff << endl;

                }
        //        usleep( 10e2*5 );
//                ws2812b_update(fd, xRGB);
            }
        }

//        if ( pVoice->currentReadPos >= pVoice->frameCount )
//            return 6;

//        if (!pVoice->isLooping && pVoice->currentReadPos == pVoice->frameCount) {
//            return NULL;    // At the end of a non-looping voice.
//        }
    }
    cout << "maxVal(*pOut): " << maxValue  << endl;

    memset( xRGB, 0x00, PIXEL_COUNT * 4 );
    ws2812b_update(fd, xRGB);


    if (!pVoice->isLooping && pVoice->currentReadPos == pVoice->frameCount) {
        return NULL;    // At the end of a non-looping voice.
    }
    return 0;
}




/* old code by WiktorTr */
/*
    for( uint64_t i = 0; i < pFlac->totalSampleCount*sizeof(int32_t); i+=16 )
    {
        for( int x = 0; x < 16; x++ )
        {
            memset( xRGB, 0x00, PIXEL_COUNT * 4 );

            buff = (double)pSampleData[ i + x ] / 32768.0;
            if(buff < 0.0)
                buff *= -1.0;

            buff = ( buff / 600.0 ) * 100.0;
            if(buff > 100.0)
                buff = 100.0;

            buff = (buff/100)*16;

            for( int y = 0; y < (int)buff; y++)
            {
                xRGB[ x + ( y )*16 ] = 0x000011;
            }
            cout << buff << endl;
        }
//        usleep( 10e2*5 );
        ws2812b_update(fd, xRGB);
//        cout <<endl<<  i << endl;
    }
    memset( xRGB, 0x00, PIXEL_COUNT * 4 );
    ws2812b_update(fd, xRGB);
    // At this point pSampleData contains every decoded sample as signed 32-bit PCM.

    drflac_close(pFlac);
    return 4;
*/

#endif // SOUND_VISUALISATION_H_INCLUDED
