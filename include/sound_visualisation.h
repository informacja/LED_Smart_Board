#ifndef SOUND_VISUALISATION_H_INCLUDED
#define SOUND_VISUALISATION_H_INCLUDED

#include "library.h"
#include "func_matryca.h"
#include "time_measure.h"

#include "snd_alsa_play.h"

#include "../libsndfile/src/sndfile.h"

#define DR_FLAC_IMPLEMENTATION
#include "dr_flac.h"

#define DR_AUDIO_IMPLEMENTATION
#include "dr_audio.h"

#include <alsa/asoundlib.h>
#include <alsa/control.h>

#define PCM_DEVICE "default"

// ----------------------------------------------------------------------------
using namespace std;
/*
#define DR_FLAC_IMPLEMENTATION
#include "dr_flac.h"

int main()
{
    drflac* pFlac = drflac_open_file("my_song.flac");
    if (pFlac == NULL) {
        return -1;
    }

    int32_t* pSampleData = (int32_t*)malloc((size_t)pFlac->totalSampleCount * sizeof(int32_t));
    drflac_read_s32(pFlac, pFlac->totalSampleCount, pSampleData);

    // At this point pSampleData contains every decoded sample as signed 32-bit PCM.

    drflac_close(pFlac);
    return 0;
}

*/


   // Sometime later you may need to update the data inside the voice's internal buffer... It's your job to handle
   // synchronization - have fun! Hint: use playback events at fixed locations to know when a region of the buffer
   // is available for updating.
////   dr_uint64
//   float* pVoiceData = (float*)dra_voice_get_buffer_ptr_by_sample(pVoice, sampleOffset);
//   if (pVoiceData == NULL) {
//       return -1;
//   }
//
//   memcpy(pVoiceData, pNewVoiceData, sizeof(float) * samplesToCopy);
//
//   ...

//    cout << pVoice->currentReadPos << endl;
//    cout << "sample rate: " << dra_voice__get_sample_rate_factor(pVoice) << endl;
//
//
//    cout << pVoice->linearVolume;
////
//    while(true)
//    {
//        if(pVoice->data)
//        cout << pVoice->currentReadPos << endl;
//    }
//usleep(10000);

//    printf("Press Enter to quit...\n");
//    getchar();

//    dra_voice_delete(pVoice);
//    dra_device_delete(pDevice);

//return 0;
//    getchar();
//    goto end;

//Menu( fd, xRGB );

//    drflac* pFlac = drflac_open_file(music.c_str());
//    if (pFlac == NULL) {
//        cout << "Error can't load audio file" << endl;
//        return 2;
//    }

//    int32_t* pSampleData = (int32_t*)malloc((size_t)pFlac->totalSampleCount * sizeof(int32_t));
//
//    drflac_read_s32(pFlac, pFlac->totalSampleCount, pSampleData);
// play
//{
//    dra_device* pDevice;
//    dra_result result = dra_device_create(NULL, dra_device_type_playback, &pDevice);
//    if (result != DRA_RESULT_SUCCESS) {
//        return -1;
//    }
//
//    dra_sound_world* pWorld = dra_sound_world_create(pDevice);
//
//    dra_sound* psound = dra_sound_create_from_file(pWorld, music.c_str());
//    result = dra_sound_create_from_file(pWorld, "closer.flac");

//    dra_voice_play(pVoice, false);
//    dra_sound_play(psound,0);
//    long volume = 0.9;
//
//}

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

void log( unsigned average, unsigned fps)
{
    cout << "\nAverage =";
    cout.width(3);
    cout << average << " of " << fps << "  ";
        for ( int i = 0; i < average; i++)
            cout << "#";
}

// ----------------------------------------------------------------------------

#define WIN 512

int sound_visualisation( int fd, uint32_t *xRGB, string music  )
{



    alsa_play(fd, xRGB, music );


    return 0;


//    dra_device* pDevice;
//    dra_result result = dra_device_create(NULL, dra_device_type_playback, &pDevice);
//    if (result != DRA_RESULT_SUCCESS) {
//        cout << "Can't create music device" << endl;
//        return -2;
//    }
//
//    dra_voice* pVoice;
//    result = dra_voice_create_from_file(pDevice, music.c_str(), &pVoice);
//    if (result != DRA_RESULT_SUCCESS) {
//        cout << "Can't create voice from file: " << music << endl;
//        return -3;
//    }



//    info_voice( pVoice, music );

//    dra_voice_play(pVoice, false);

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
//    display_tab_labels();


//    sndfile_play




//    while( pVoice->currentReadPos <= pVoice->frameCount )

    {
//        timeNow = system_clock::now();

//        double framedelta =double ( timeNow - timeLast )

//    chrono::duration<double> elapsed_seconds = elapsed_seconds;
//
//    timeLast = timeNow;


//        coutner_global++;
//        static unsigned average;
//        const unsigned fps = 1024;
//
//        maxValue = last;
//
//        float* pOut = 0;
//
//        pOut = (float*)pVoice->pData + (pVoice->currentReadPos );
//
//        if ( *pOut != last )
        {
//            if ( pVoice->currentReadPos % 100 == 0 )
            {
//                coutner_display++;
//                cout.width(9);
//                cout << coutner_global << " ";
//                cout.width(4);
//                cout << coutner_display << " ";
//                cout.width(7);
//                cout << pVoice->currentReadPos << ": " << *pOut;
//
//                cout << "  " << elapsed_seconds.count() << endl;
//                printf("%3.2f\n", elapsed_seconds.count() );
//                last = *pOut;

//                double buff = 0.0;
////                for( int x = 0; x < 16; x++ )
//                {

//                    fft_audio_analyzer( fd, xRGB, pOut, cfg);

//                    buff = (double)*pOut / 32768.0;

//                        if( last < 0.0)
//                        {
//                            last -= last + last;
//                        }
//
//                    int interator = floor( last * 100.0 );
//
//                    if (interator > 16 )
//                    {
//                        interator = 16;
////                        for( int i = 0; i < PIXEL_COUNT; i++ )
////                            xRGB[ i ] = 0x110000;
//                    }
//                    else

//                    average += interator;
//
//                    if ( coutner_global % fps == 0 )
//                    {
//                        interator = average / fps;
////                        color_state( xRGB, interator );
////                        log(interator,fps);
//                        average = 0;
//                    }


//                    for( int s = 0; s < interator; s++)
                    {
//                        color_state( xRGB, interator, s, s );
                    }

//            if( last > maxValue )
//                maxValue = last;
//                    if ( coutner_global % fps == 0 )
//                        ws2812b_update(fd, xRGB);
//                    usleep(10e4/2);

//                    for( int y = 0; y < (int)buff; y++)
//                    {
//                        xRGB[ x + ( y )*16 ] = 0x000011;
//                    }
//                    cout << buff << endl;

                }
        //        usleep( 10e2*5 );
//                ws2812b_update(fd, xRGB);
            }


//        if ( pVoice->currentReadPos >= pVoice->frameCount )
//            return 6;

//        if (!pVoice->isLooping && pVoice->currentReadPos == pVoice->frameCount) {
//            return NULL;    // At the end of a non-looping voice.
//        }
    }
//    cout << "maxVal(*pOut): " << maxValue  << endl;

    memset( xRGB, 0x00, PIXEL_COUNT * 4 );
    ws2812b_update(fd, xRGB);

//    free(cfg);


//    if (!pVoice->isLooping && pVoice->currentReadPos == pVoice->frameCount) {
//        return NULL;    // At the end of a non-looping voice.
//    }
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
